
#include "esp-logger-spiffs.h"

const String filepath = "/mylog.log";
unsigned int logcount = 0;

EspLoggerSPIFFS myLog(filepath, 10, 100);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  if(!myLog.begin())
  {
    Serial.println("file system need to format...");
  }
  
  //  myLog.getCount(&logcount);
  //  Serial.println(logcount);

}

// in millisecond
int period = 3000;

unsigned int nextTime = 0;

typedef unsigned long int UNIX_TIME;
typedef char PARAMCODE, PARAMVALUE[12];

typedef union
{
  unsigned char Array[sizeof(UNIX_TIME) + sizeof(PARAMCODE) + sizeof(PARAMVALUE)];
  struct
  {
    UNIX_TIME logDT;
    PARAMCODE logPC;
    PARAMVALUE logPV;
  };
} TRANSACTION;

TRANSACTION trans;
unsigned int numLog = 0;

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available())
  {
    char ch = Serial.read();
    switch (ch)
    {
      case '1' :  //create a log
        trans.logDT = ++numLog;
        trans.logPC = 'T';
        strcpy(trans.logPV , "22.5");
        if ( myLog.push(trans.Array))
        {
          Serial.println("log pushed");
        }
        else
        {
          Serial.println("log push error");
        }
        break;

      case '2': //read a specific log
        while (!Serial.available());
        if (Serial.available())
        {
          ch = Serial.read();
        }
        if ( myLog.get(trans.Array, ch - '0' ))
        {
          Serial.println("log read");
          Serial.print(trans.logDT);
          Serial.print(',');
          Serial.print(trans.logPC);
          Serial.print(',');
          Serial.print(trans.logPV);
          Serial.print('\n');
        }
        else
        {
          Serial.println("log read error");
        }
        break;

      case '3': //read and delete first log
        if ( myLog.pop(trans.Array))
        {
          Serial.println("log poped");
          Serial.print(trans.logDT);
          Serial.print(',');
          Serial.print(trans.logPC);
          Serial.print(',');
          Serial.print(trans.logPV);
          Serial.print('\n');
        }
        else
        {
          Serial.println("log pop error");
        }
        break;

      case '4': //clear all logs
        if ( myLog.clear())
        {
          Serial.println("log clear");
        }
        else
        {
          Serial.println("log clear error");
        }
        break;

      case '5': //get number of logs
        myLog.getCount(&logcount);
        Serial.print("log Num:");
        Serial.println(logcount);
        break;
    }
  }

  if (millis() > nextTime) {
    nextTime += period;
    //myLog.push();
  }
}
