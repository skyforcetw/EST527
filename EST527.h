#ifndef EST527_h
#define EST527_h

#include "Arduino.h"
#include <SoftwareSerial.h>

#define EST_DEBUG

#define EST_TIMEOUT 3000
#define EST_BUFFER_LENGTH 100

#define ATROFF "ATROFF+OK."
#define ATPIDON "OBD PID MODEL NOW."
#define ATPIDOFF "ATPIDOFF+OK."
#define EST_CONNECTING "EST527,Connect"

/**
 * Return code when communication with the ELM device returned succesfully
 */
#define EST_SUCCESS 0


/**
 * Return code when communication with the ELM device failed as there was 
 *  no response.
 */
#define EST_NO_RESPONSE 1

/**
 * Return code when the ELM device returned more data than the given buffer
 * was able to hold. 
 */
#define EST_BUFFER_OVERFLOW 2


/**
 *  Return code when the ELM device returns unexpected data.  This is 
 *  usually when the response does not contain byte values, or contains
 *  unexpected output.
 */
#define EST_GARBAGE 3


/**
 *  Return code when the ELM device is unable to connect to the vehicle 
 *  The EST527 has tried all of the available protocols, and could not
 *  detect a compatible one. This could be because your vehicle uses an
 *  unsupported protocol, or could be as simple as forgetting to turn the
 *  ignition key on. Check all of your connections, and the ignition,
 *  then try the command again.
 */
#define EST_UNABLE_TO_CONNECT 4


/**
 *  Return code when the ELM device returns NO DATA.  The IC waited for 
 *  the period of time that was set by AT ST, and detected no response
 *  from the vehicle. It may be that the vehicle had no data to offer
 *  for that particular PID, that the mode requested was not supported,
 *  that the vehicle was attending to higher priority issues, or in the
 *  case of the CAN systems, the filter may have been set so that the
 *  response was ignored, even though one was sent. If you are certain
 *  that there should have been a response, try increasing the ST time
 *  (to be sure that you have allowed enough time for the ECU to
 *  respond), or restoring the CAN filter to its default setting.
 */
#define EST_NO_DATA 5

#define EST_UNKNOW 6

#define EST_FAIL 7

#define EST_STOPPED 8

#define EST_CAN_ERROR 9

#define EST_RT_MODE 10

class EST527
{
private:
  char buffer[EST_BUFFER_LENGTH];
  SoftwareSerial *serial;
  SoftwareSerial *seriald;
  bool bySoftSerial;
  bool inPIDMode;
  void (*callback)();
  bool debugEnable;
  
  byte runCommand(const char *cmd, char *data, unsigned int dataLength,bool doflush=false);
  byte getATCommand( const char *mode);
  byte getATCommand(const char * command, const char * check);
  String getTokenN(char *str, int n);
  
  bool available();
  byte read();
  void d(char *fmt, ... );
  byte getPIDBytes( const char *mode, const char *chkMode, const char *pid, byte *values, unsigned int numValues);

public:
  EST527(SoftwareSerial& softserial);
  EST527();
  byte begin(bool pidMode=false); 
  void flush();
  String getBuffer();
  void setCallback(void (*callback)());
  void setDebugSerial(SoftwareSerial& serial);
  void setDebugEnable(bool enable);
  
  byte getVoltage(float &voltage);
  byte engineLoad(byte &load);
  byte coolantTemperature(int &temp);
  byte engineRPM(int &rpm);
  byte vehicleSpeed(byte &speed);
  byte intakeAirTemperature(int &temperature);
  byte relativeThrottlePosition(byte &position);
  
  String getStatusString(byte status);
  void reset();
   
};
#endif