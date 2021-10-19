#include <esp-logger-spiffs.h>

const String filepath = "/myTH.log";
unsigned int logcount = 0;

typedef unsigned long int UNIX_TIME;
typedef char TEMPERATURE[6], HUMIDITY[6];
typedef union
{
  unsigned char Array[sizeof(UNIX_TIME) + sizeof(TEMPERATURE) + sizeof(HUMIDITY)];
  struct
  {
    UNIX_TIME logDT;
    TEMPERATURE logTemp;
    HUMIDITY logHum;
  };
} TRANSACTION;

TRANSACTION trans;

EspLoggerSPIFFS myLog(filepath, sizeof(TRANSACTION), 50000);

// in millisecond
int period = 30000;

unsigned int nextTime = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  if (!myLog.begin())
  {
    Serial.println("file system need to format...");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (millis() > nextTime) {
    nextTime += period;

    
    if ( myLog.push(trans.Array))
    {
      Serial.println("log pushed");
    }
    else
    {
      Serial.println("log push error");
    }
  }


  if (Serial.available())
  {
    char ch = Serial.read();
    switch (ch)
    {
    
      case '3': //read and delete first log
        if ( myLog.pop(trans.Array))
        {
          Serial.println("log poped");
          Serial.print(trans.logDT);
          Serial.print(',');
          Serial.print(trans.logTemp);
          Serial.print(',');
          Serial.print(trans.logHum);
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
}
