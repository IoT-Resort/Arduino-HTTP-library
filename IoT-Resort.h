/*
  IoT-Resort.h - Arduino library for IoT-Resort platform.
  Created by IoT-Resort, November 23, 2017. Ver. 1.0
  Released into the public domain.
*/


#include <ESP8266WiFi.h>

#ifndef IoT_Resort_h
#define IoT_Resort_h
 
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#define PROTOCOL_HTTP 1
#define PROTOCOL_HTTPS 2
#define PROTOCOL_MQTT 3

// Uncomment to enable printing out nice debug messages.
#define DEBUG_IOTRESORT
// Define where debug output will be printed.
#define DEBUG_SCREEN Serial
// Setup debug printing macros.
#ifdef DEBUG_IOTRESORT
  #define DEBUG_PRINT(...) { DEBUG_SCREEN.print(__VA_ARGS__); }
  #define DEBUG_PRINTLN(...) { DEBUG_SCREEN.println(__VA_ARGS__); }
#else
  #define DEBUG_PRINT(...) {}
  #define DEBUG_PRINTLN(...) {}
#endif

class Thing
{
  public:
    Thing(String IoTServer, int Port, String IoTThingSerial, int Protocol,WiFiClient* Client);
    boolean SetIoTValue(String IoTValueName,String IoTValue );
    String GetIoTControlParameter(String IoTControlParameter );
  private:
    char _IoTServer[64];
    int _Port;
    String _IoTThingSerial;
    int _Protocol;
    WiFiClient* _client;
    String HttpRequest(String GetContent );
    String GetTagValue(String text, String tag);
    String GetMidString(String str, String start, String finish);

};
 
#endif
