/* Copyright 2011 David Irvine
 *
 * This file is part of Loguino
 *
 * Loguino is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Loguino is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with Loguino.  If not, see <http://www.gnu.org/licenses/>.

 * $Rev$
 * $Author$
 * $Date$

*/

#include <Arduino.h>
#define EST_TIMEOUT 9000
#define EST_BAUD_RATE 9600
#define EST_PORT Serial

#include <SoftwareSerial.h>

#include <EST527.h>
void printStatus(byte status) {
  switch (status)
  {
    case EST_TIMEOUT:
      Serial.println("EST_TIMEOUT");
      break;
    case EST_SUCCESS:
      Serial.println("EST_SUCCESS");
      break;
    case EST_NO_RESPONSE:
      Serial.println("EST_NO_RESPONSE");
      break;
    case EST_BUFFER_OVERFLOW:
      Serial.println("EST_BUFFER_OVERFLOW");
      break;
    case EST_GARBAGE:
      Serial.println("EST_GARBAGE");
      break;
    case EST_UNABLE_TO_CONNECT:
      Serial.println("EST_UNABLE_TO_CONNECT");
      break;
    case EST_NO_DATA:
      Serial.println("EST_NO_DATA");
      break;
    default:
      Serial.print("UNKNOWN: ");
      Serial.println(status);
  }
}



void setup() {

  float f;
  bool b;
  byte by;
  int i;
  unsigned int ui;

  byte status;
  String s;
  EST527 est;

  Serial.begin(115200);
  Serial.print("EST527 Begin: ");
  printStatus(est.begin());

  Serial.print("est Voltage: ");
  status = est.getVoltage(f);
  if (status == EST_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(f);
  } else {
    printStatus(status);
  }

  Serial.print("est Ignition: ");
  status = est.getIgnMon(b);
  if (status  == EST_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(b);
  } else {
    printStatus(status);
  }

  Serial.print("est Version: ");
  status = est.getVersion(s) ;
  if (status == EST_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(s);
  } else {
    printStatus(status);
  }

  Serial.print("OBD2 Engine Load: ");
  status = est.engineLoad(by);
  if (status  == EST_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(by);
  } else {
    printStatus(status);
  }

  Serial.print("OBD2 Coolant Temperature: ");
  status = est.coolantTemperature(i);
  if (status  == EST_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(i);
  } else {
    printStatus(status);
  }

  Serial.print("OBD2 Fuel Trim, Bank 1, Short Term: ");
  status = est.fuelTrimBank1ShortTerm(i);
  if (status  == EST_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(i);
  } else {
    printStatus(status);
  }


  Serial.print("OBD2 Fuel Trim, Bank 2, Short Term: ");
  status = est.fuelTrimBank2ShortTerm(i);
  if (status  == EST_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(i);
  } else {
    printStatus(status);
  }

  Serial.print("OBD2 Fuel Trim, Bank 1, Long Term: ");
  status = est.fuelTrimBank1LongTerm(i) ;
  if (status  == EST_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(i);
  } else {
    printStatus(status);
  }

  Serial.print("OBD2 Fuel Trim, Bank 2, Long Term: ");
  status = est.fuelTrimBank2LongTerm(i);
  if (status  == EST_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(i);
  } else {
    printStatus(status);
  }

  Serial.print("OBD2 Fuel Pressure: ");
  status = est.fuelPressure(i) ;
  if (status  == EST_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(i);
  } else {
    printStatus(status);
  }

  Serial.print("OBD2 Intake Manifold Absolute Pressure: ");
  status = est.intakeManifoldAbsolutePressure(by) ;
  if (status  == EST_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(by);
  } else {
    printStatus(status);
  }

  Serial.print("OBD2 Engine RPM: ");
  status = est.engineRPM(i) ;
  if (status  == EST_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(i);
  } else {
    printStatus(status);
  }

  Serial.print("OBD2 Vehicle Speed: ");
  status = est.vehicleSpeed(by);
  if (status  == EST_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(b);
  } else {
    printStatus(status);
  }

//  Serial.print("OBD2 Timing Advance: ");
//  status = est.timingAdvance(i);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value: ");
//    Serial.println(i);
//  } else {
//    printStatus(status);
//  }
//
//  Serial.print("OBD2 Intake Air Temperature: ");
//  status = est.intakeAirTemperature(i);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value: ");
//    Serial.println(i);
//  } else {
//    printStatus(status);
//  }
//
//  Serial.print("OBD2 MAF Air Flow Rate: ");
//  status = est.MAFAirFlowRate(ui);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value: ");
//    Serial.println(ui);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("OBD2 Throttle Position: ");
//  status = est.throttlePosition(by);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value: ");
//    Serial.println(by);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("OBD2 O2 Sensor: Bank1 - Sensor 1: ");
//  byte vo;
//  byte trim;
//  status = est.o2SensorBank1Sensor1(vo, trim);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Voltage: ");
//    Serial.println(vo, DEC);
//    Serial.print(" Trim: ");
//    Serial.println(trim, DEC);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("OBD2 O2 Sensor: Bank1 - Sensor 2: ");
//  status = est.o2SensorBank1Sensor2(vo, trim);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Voltage: ");
//    Serial.println(vo, DEC);
//    Serial.print(" Trim: ");
//    Serial.println(trim, DEC);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("OBD2 O2 Sensor: Bank1 - Sensor 3: ");
//  status = est.o2SensorBank1Sensor3(vo, trim);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Voltage: ");
//    Serial.println(vo, DEC);
//    Serial.print(" Trim: ");
//    Serial.println(trim, DEC);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("OBD2 O2 Sensor: Bank1 - Sensor 4: ");
//  status = est.o2SensorBank1Sensor4(vo, trim);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Voltage: ");
//    Serial.println(vo, DEC);
//    Serial.print(" Trim: ");
//    Serial.println(trim, DEC);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("OBD2 O2 Sensor: Bank2 - Sensor 1: ");
//  status = est.o2SensorBank2Sensor1(vo, trim);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Voltage: ");
//    Serial.println(vo, DEC);
//    Serial.print(" Trim: ");
//    Serial.println(trim, DEC);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("OBD2 O2 Sensor: Bank2 - Sensor 2: ");
//  status = est.o2SensorBank2Sensor2(vo, trim);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Voltage: ");
//    Serial.println(vo, DEC);
//    Serial.print(" Trim: ");
//    Serial.println(trim, DEC);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("OBD2 O2 Sensor: Bank2 - Sensor 3: ");
//  status = est.o2SensorBank2Sensor3(vo, trim);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Voltage: ");
//    Serial.println(vo, DEC);
//    Serial.print(" Trim: ");
//    Serial.println(trim, DEC);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("OBD2 O2 Sensor: Bank2 - Sensor 4: ");
//  status = est.o2SensorBank2Sensor4(vo, trim);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Voltage: ");
//    Serial.println(vo, DEC);
//    Serial.print(" Trim: ");
//    Serial.println(trim, DEC);
//  } else {
//    printStatus(status);
//  }
//
//  Serial.print("OBD2 Auxiliary Input Status: ");
//  status = est.auxiliaryInputStatus(b);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value: ");
//    Serial.println(b);
//  } else {
//    printStatus(status);
//  }
//
//  Serial.print("OBD2 Engine Run Time: ");
//  status = est.engineRunTime(ui);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value: ");
//    Serial.println(ui);
//  } else {
//    printStatus(status);
//  }
//
//  Serial.print("OBD2 Distance since MIL active: ");
//  status = est.distanceMIL(ui);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value: ");
//    Serial.println(ui);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("OBD2 Relative Fuel Rail Pressure: ");
//  status = est.relativeFuelRailPressure(ui);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value: ");
//    Serial.println(ui);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("OBD2 Absolute Fuel Rail Pressure: ");
//  status = est.absoluteFuelRailPressure(ui);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value: ");
//    Serial.println(ui);
//  } else {
//    printStatus(status);
//  }
//  unsigned int equiv;
//  unsigned int voltage;
//  Serial.print("OBD2 O2 Sensor 1, Equivilance Ratio and Voltage: ");
//  status = est.o2S1WRVoltage(equiv, voltage);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value Equiv: ");
//    Serial.println(equiv);
//    Serial.print(" Value Voltage: ");
//    Serial.println(voltage);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("OBD2 O2 Sensor 2, Equivilance Ratio and Voltage: ");
//  status = est.o2S2WRVoltage(equiv, voltage);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value Equiv: ");
//    Serial.println(equiv);
//    Serial.print(" Value Voltage: ");
//    Serial.println(voltage);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("OBD2 O2 Sensor 3, Equivilance Ratio and Voltage: ");
//  status = est.o2S3WRVoltage(equiv, voltage);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value Equiv: ");
//    Serial.println(equiv);
//    Serial.print(" Value Voltage: ");
//    Serial.println(voltage);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("OBD2 O2 Sensor 4, Equivilance Ratio and Voltage: ");
//  status = est.o2S4WRVoltage(equiv, voltage);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value Equiv: ");
//    Serial.println(equiv);
//    Serial.print(" Value Voltage: ");
//    Serial.println(voltage);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("OBD2 O2 Sensor 5, Equivilance Ratio and Voltage: ");
//  status = est.o2S5WRVoltage(equiv, voltage);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value Equiv: ");
//    Serial.println(equiv);
//    Serial.print(" Value Voltage: ");
//    Serial.println(voltage);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("OBD2 O2 Sensor 6, Equivilance Ratio and Voltage: ");
//  status = est.o2S6WRVoltage(equiv, voltage);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value Equiv: ");
//    Serial.println(equiv);
//    Serial.print(" Value Voltage: ");
//    Serial.println(voltage);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("OBD2 O2 Sensor 7, Equivilance Ratio and Voltage: ");
//  status = est.o2S7WRVoltage(equiv, voltage);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value Equiv: ");
//    Serial.println(equiv);
//    Serial.print(" Value Voltage: ");
//    Serial.println(voltage);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("OBD2 O2 Sensor 8, Equivilance Ratio and Voltage: ");
//  status = est.o2S8WRVoltage(equiv, voltage);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value Equiv: ");
//    Serial.println(equiv);
//    Serial.print(" Value Voltage: ");
//    Serial.println(voltage);
//  } else {
//    printStatus(status);
//  }
//
//  Serial.print("OBD2 Commanded EGR: ");
//  status = est.commandedEGR(by);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value: ");
//    Serial.println(by);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("OBD2 EGR Error: ");
//  status = est.EGRError(i);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value: ");
//    Serial.println(i);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("OBD2 Commanded Evaporative Purge: ");
//  status = est.commandedEvaporativePurge(by);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value: ");
//    Serial.println(by);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("Fuel Level: ");
//  status = est.fuelLevel(by);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value: ");
//    Serial.println(by);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("Warmups since MIL last cleared: ");
//  status = est.warmUpsSinceLastCleared(by);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value: ");
//    Serial.println(by);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("Distance since MIL last cleared: ");
//  status = est.distanceSinceLastCleared(ui);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value: ");
//    Serial.println(ui);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("Evap Pressure: ");
//  status = est.evapPressure(i);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value: ");
//    Serial.println(i);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("Barometric Pressure: ");
//  status = est.barometricPressure(by);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value: ");
//    Serial.println(by);
//  } else {
//    printStatus(status);
//  }
//  int current;
//
//  Serial.print("O2 Sensor 1 Current and Equiv Ratio: ");
//  status = est.o2S1WRCurrent(equiv, current);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value Current: ");
//    Serial.println(current);
//    Serial.print(" Value Equiv: ");
//    Serial.println(equiv);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("O2 Sensor 2 Current and Equiv Ratio: ");
//  status = est.o2S2WRCurrent(equiv, current);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value Current: ");
//    Serial.println(current);
//    Serial.print(" Value Equiv: ");
//    Serial.println(equiv);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("O2 Sensor 3 Current and Equiv Ratio: ");
//  status = est.o2S3WRCurrent(equiv, current);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value Current: ");
//    Serial.println(current);
//    Serial.print(" Value Equiv: ");
//    Serial.println(equiv);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("O2 Sensor 4 Current and Equiv Ratio: ");
//  status = est.o2S4WRCurrent(equiv, current);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value Current: ");
//    Serial.println(current);
//    Serial.print(" Value Equiv: ");
//    Serial.println(equiv);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("O2 Sensor 5 Current and Equiv Ratio: ");
//  status = est.o2S5WRCurrent(equiv, current);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value Current: ");
//    Serial.println(current);
//    Serial.print(" Value Equiv: ");
//    Serial.println(equiv);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("O2 Sensor 6 Current and Equiv Ratio: ");
//  status = est.o2S6WRCurrent(equiv, current);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value Current: ");
//    Serial.println(current);
//    Serial.print(" Value Equiv: ");
//    Serial.println(equiv);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("O2 Sensor 7 Current and Equiv Ratio: ");
//  status = est.o2S7WRCurrent(equiv, current);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value Current: ");
//    Serial.println(current);
//    Serial.print(" Value Equiv: ");
//    Serial.println(equiv);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("O2 Sensor 8 Current and Equiv Ratio: ");
//  status = est.o2S8WRCurrent(equiv, current);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value Current: ");
//    Serial.println(current);
//    Serial.print(" Value Equiv: ");
//    Serial.println(equiv);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("Catalyst Temperature Bank1 Sensor 1: ");
//  status = est.catalystTemperatureBank1Sensor1(i);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value: ");
//    Serial.println(i);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("Catalyst Temperature Bank2 Sensor 1: ");
//  status = est.catalystTemperatureBank2Sensor1(i);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value: ");
//    Serial.println(i);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("Catalyst Temperature Bank1 Sensor 2: ");
//  status = est.catalystTemperatureBank1Sensor2(i);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value: ");
//    Serial.println(i);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("Catalyst Temperature Bank2 Sensor 2: ");
//  status = est.catalystTemperatureBank2Sensor2(i);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value: ");
//    Serial.println(i);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("Control Module Voltage: ");
//  status = est.controlModuleVoltage(ui);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value: ");
//    Serial.println(ui);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("Absolute Load Value: ");
//  status = est.absoluteLoadValue(ui);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value: ");
//    Serial.println(ui);
//  } else {
//    printStatus(status);
//  }
//
//  Serial.print("Command equivalence ratio: ");
//  status = est.commandEquivalenceRatio(f );
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value: ");
//    Serial.println(f);
//  } else {
//    printStatus(status);
//  }
//
//  Serial.print("Relative throttle position: ");
//  status = est.relativeThrottlePosition(by);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value: ");
//    Serial.println(by);
//  } else {
//    printStatus(status);
//  }
//
//
//  Serial.print("Ambient Air Temperature: ");
//  status = est.ambientAirTemperature(i );
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value: ");
//    Serial.println(i);
//  } else {
//    printStatus(status);
//  }
//
//  Serial.print("Absolute throttle position B: ");
//  status = est.absoluteThrottlePositionB(by);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value: ");
//    Serial.println(by);
//  } else {
//    printStatus(status);
//  }
//  Serial.print("Absolute throttle position C: ");
//  status = est.absoluteThrottlePositionC(by);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value: ");
//    Serial.println(by);
//  } else {
//    printStatus(status);
//  }
//
//  Serial.print("Accelerator pedal position D: ");
//  status = est.acceleratorPedalPositionD(by);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value: ");
//    Serial.println(by);
//  } else {
//    printStatus(status);
//  }
//
//  Serial.print("Accelerator pedal position E: ");
//  status = est.acceleratorPedalPositionE(by);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value: ");
//    Serial.println(by);
//  } else {
//    printStatus(status);
//  }
//
//  Serial.print("Accelerator pedal position F: ");
//  status = est.acceleratorPedalPositionF(by);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value: ");
//    Serial.println(by);
//  } else {
//    printStatus(status);
//  }
//
//  Serial.print("Commanded Throttle Actuator: ");
//  status = est.commandedThrottleActuator(by);
//  if (status  == EST_SUCCESS)
//  {
//    Serial.println ("Pass");
//    Serial.print(" Value: ");
//    Serial.println(by);
//  } else {
//    printStatus(status);
//  }

}
void loop() {}
