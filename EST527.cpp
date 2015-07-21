#include "EST527.h"
 

#ifdef EST_DEBUG
#include <stdarg.h>
void EST527::d(char *fmt, ... ) {
	if(!debugEnable) return;
	
	char tmp[128]; // resulting string limited to 128 chars
	va_list args;
	va_start (args, fmt );
	vsnprintf(tmp, 128, fmt, args);
	va_end (args);

	if ( NULL != seriald) {
		seriald->print(tmp);
	}

}

String EST527::getStatusString(byte status) {
	if(!debugEnable) return "";
	switch (status)
	{
	case EST_SUCCESS:
	  return "SUCCESS";
	case EST_NO_RESPONSE:
	  return "NO_RESPONSE";
	case EST_BUFFER_OVERFLOW:
	  return "BUFFER_OVERFLOW";
	  break;
	case EST_GARBAGE:
	  return "GARBAGE";
	  break;
	case EST_UNABLE_TO_CONNECT:
	  return "UNABLE_TO_CONNECT";
	case EST_NO_DATA:
	  return "NO_DATA";
	case EST_UNKNOW:
	  return "UNKNOW";
	case EST_FAIL:
	  return "FAIL";
	case EST_STOPPED:
	  return "STOPPED";
	case EST_CAN_ERROR:
	  return "CAN_ERROR";	 
	case EST_RT_MODE:
	  return "RT_MODE";	
	default:
	  return "Unknow Status: "+String(status);
	}
}

#else
void EST527::d(char *fmt, ... ){}

String EST527::getStatusString(byte status) {
	return "";
}
#endif

EST527::EST527(SoftwareSerial& softserial) {
	bySoftSerial = true;
	serial = &softserial;
	callback = NULL;
	seriald = NULL;
	inPIDMode = false;
	debugEnable = false;
}

EST527::EST527() {
	bySoftSerial = false;
	callback = NULL;
	seriald = NULL;
	inPIDMode = false;
	debugEnable = false;
}

byte EST527::begin(bool pidMode) {
	byte status;
	status = runCommand("ATROFF",buffer,EST_BUFFER_LENGTH,true);
	delay(500);

	if( EST_UNKNOW == status) { //可能落在ATPIDON
		inPIDMode = true;
	}
	
	if(pidMode) {
		status = getATCommand("ATPIDON",ATPIDON);
	}else {
		status = getATCommand("ATPIDOFF",ATPIDOFF);
	}
	inPIDMode = pidMode;
	return status;
}

bool EST527::available() {
  return bySoftSerial ? serial->available() : Serial.available();
}
byte EST527::read() {
  return bySoftSerial ? serial->read() : Serial.read();
}



byte EST527::runCommand(const char *cmd, char *buffer, unsigned int bufferLength, bool doflush) {	
	if(doflush) {
		flush();
	}
	d("command: %s\n",cmd);
	if(bySoftSerial) {
		serial->print(cmd);
		serial->print("\r\n");
	} else {
		Serial.print(cmd);
		Serial.print("\r\n");
	}
	
	unsigned long timeOut = millis()+EST_TIMEOUT;
	bool end = false;
	bool start = inPIDMode ? true : false;
	int counter = 0;
	char c;
	
	/*
	$開頭, 正常回傳
	?開頭, 無法解析指令, 直接結束
	*/
	
	while (!end && counter<( bufferLength ) && millis() < timeOut)
    {
		if( NULL != callback) {
			callback();
		}

		if ( available() ){
			c = buffer[counter] = read();
			
			if( '?' == c ) {
				flush();
				return EST_UNKNOW;
			}
			else if( '$' == c && !inPIDMode) {
				start = true; //開始, 可以先略過此字元
				continue;
			}
			else if( 13 == c  ) {
				if(inPIDMode) {
					end = true; //結束
					//flush();
					if( available()) read();
					continue;
				}else {
					continue;
				}
			}
			else if( 10 == c ) {
				end = true; //結束
				flush();
				continue;
			}
			counter++;
				
		}
    }
	buffer[counter] ='\0';
	d("return: %d %s\n",counter,buffer);
	
	if (!end  && counter >= bufferLength)
	{
		delay(300);
		return EST_BUFFER_OVERFLOW;
	}
	
    if (!start && counter < bufferLength){
		delay(300);
		return EST_NO_RESPONSE;
    }
	
	char *match;
	match=strstr(buffer,"STOPPED");
	if (match != NULL){
		return EST_STOPPED;
	}	
	match=strstr(buffer,"CAN ERROR");
	if (match != NULL){
		return EST_CAN_ERROR;
	}	
	
	return EST_SUCCESS;
}

void EST527::flush(){
	if( bySoftSerial ) {
		// serial.flush();
		while (  serial->available()) {
			serial->read();
		}
	}
	else {
		Serial.flush();
	}
}

String EST527::getBuffer() {
	return String(buffer);
}

void EST527::setCallback(void (*_callback)()) {
	callback = _callback;
}

void EST527::setDebugSerial(SoftwareSerial& serial) {
	seriald = &serial;
}

void EST527::setDebugEnable(bool enable) {
	debugEnable = enable;
}

byte EST527::getVoltage(float &voltage) {
  
}
byte EST527::engineLoad(byte &load) {
  
}
byte EST527::coolantTemperature(int &temp) {
  
}
byte EST527::engineRPM(int &rpm) {
	if(inPIDMode) {
		byte status;
		byte values[2];
		status=getPIDBytes("01","41","0C",values,2);
		if (status != EST_SUCCESS){
			return status;
		}
		rpm=((values[0]*256)+values[1])/4;
		return EST_SUCCESS;
	}else {		
		byte status = getATCommand("012");
		String token = getTokenN(buffer,1);
		rpm = atoi(token.c_str());
		return status;
	}
}
byte EST527::vehicleSpeed(byte &speed) {
	if(inPIDMode) {
		byte status;
		byte values[1];
		status=getPIDBytes("01","41","0D",values,1);
		if (status != EST_SUCCESS){
			return status;
		}
		speed=values[0];
		return EST_SUCCESS;
	}else {
		byte status = getATCommand("013");
		if(EST_SUCCESS == status) {
			String token = getTokenN(buffer,1);
			speed = atoi(token.c_str());
		}
		return status;
	}
}

byte EST527::intakeAirTemperature(int &temperature) {
  
}

byte EST527::relativeThrottlePosition(byte &position){

	if(inPIDMode) {
		byte status;
		byte values[1];
		status=getPIDBytes("01","41","45",values,1);
		if (status != EST_SUCCESS){
			return status;
		}
		position=(100*values[0])/255;
		return EST_SUCCESS;
	}else {
		// byte status = getATCommand("013");
		// if(EST_SUCCESS == status) {
			// String token = getTokenN(buffer,1);
			// speed = atoi(token.c_str());
		// }
		// return status;
	}	
}

byte EST527::getATCommand( const char *mode) {
	char atcommand[]="AT000";
	atcommand[2]=mode[0];
	atcommand[3]=mode[1];
	atcommand[4]=mode[2];
	
	byte status = runCommand(atcommand,buffer,EST_BUFFER_LENGTH);
	// int modesize = strlen(mode);
	// if( EST_SUCCESS == status && strncmp(buffer,mode,modesize) != 0 ) {
		// return EST_FAIL;
	// }		
	return status;
}

byte EST527::getATCommand(const char * command, const char * check) {
	byte status = runCommand(command,buffer,EST_BUFFER_LENGTH);
	if( EST_SUCCESS == status && strstr(buffer,check) == NULL ) {
		return EST_FAIL;
	}
	return status;
}

String EST527::getTokenN(char *str, int n) {
	char * pch;
#define DELIMITERS ",="
	pch = strtok (str,DELIMITERS);
	//pch = strtok (NULL, DELIMITERS); //bypass AT command
	for(int x=0;pch != NULL && x<n;x++) {
		pch = strtok (NULL, DELIMITERS);
	}
	if( pch != NULL ) {
		return String(pch);
	}
	else {
		return String();
	}
}

/*
pid mode
*/
byte EST527::getPIDBytes( const char *mode, const char *chkMode, const char *pid, byte *values, unsigned int numValues){
	// char data[64];
	byte status;
	char hexVal[]="0x00";
	char cmd[6];
	cmd[0]=mode[0];
	cmd[1]=mode[1];
	cmd[2]=' ';
	cmd[3]=pid[0];
	cmd[4]=pid[1];
	cmd[5]='\0';
	// cmd[6]=10;

	status=runCommand(cmd,buffer,EST_BUFFER_LENGTH);
	if ( status != EST_SUCCESS )
	{
		 // _s(getStatusString(status));
		return status;
	};
	
	// Check the mode returned was the one we sent
	if ( buffer[0]!=chkMode[0] 
	  or buffer[1]!=chkMode[1]
	  or buffer[3]!=pid[0]
	  or buffer[4]!=pid[1] ){
		  
		char *match;
		match=strstr(buffer,"$OBD-RT");
		if (match != NULL){		
			return EST_RT_MODE;
		}
		  
		return EST_GARBAGE;
	}
	
	// For each byte expected, package it up
	int i=0;
	for (int i=0; i<numValues; i++){
		hexVal[2]=buffer[6+(3*i)];
		hexVal[3]=buffer[7+(3*i)];
		values[i]=strtol(hexVal,NULL,16);
	}
	return EST_SUCCESS;
}

void EST527::reset() {
	getATCommand("WST");
	flush();
}

