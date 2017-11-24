/*
  IoT-Resort.cpp - Arduino library for IoT-Resort platform.
  Created by IoT-Resort, November 23, 2017. Ver. 1.0
  Released into the public domain.
*/
#include "IoT-Resort.h"

Thing::Thing(String IoTServer, int Port, String IoTThingSerial, int Protocol,WiFiClient* Client ){
    IoTServer.toCharArray(_IoTServer, 64);	
    _Port = Port;    
    _IoTThingSerial = IoTThingSerial;
    _Protocol = Protocol;
    _client = Client;
}

boolean Thing::SetIoTValue(String IoTValueName,String IoTValue ){
    String response;
    response = HttpRequest("/SetReportParameter.php?Thing="+_IoTThingSerial+"&Parameter="+IoTValueName+"&Value="+IoTValue);
 
    if (response=="ConnectionError"){
       DEBUG_PRINTLN("Connection error");
       return false;
    }; 
    
    if (GetTagValue(response, "Value")==IoTValue)
    {
        return true;
    };

    return false;
 
}
String Thing::GetIoTControlParameter(String IoTControlParameter ){
    String response;
    response = HttpRequest("/GetControlParameter.php?Thing="+_IoTThingSerial+"&Parameter="+IoTControlParameter);
    if (response=="ConnectionError"){
       DEBUG_PRINTLN("Connection error");
       return "";
    }; 

    return GetTagValue(response, "ControlParameter");    

}
String Thing::HttpRequest(String GetContent ){
    long int time;
    String response;
    GetContent.replace(" ","%20");
    if (_client->connect(_IoTServer, _Port)) {
        _client->print("GET " + GetContent + " HTTP/1.1\r\n" +
                 "Host: " + String(_IoTServer) + "\r\n" + 
                 "Connection: close\r\n\r\n");
        unsigned long timeout = millis();
        while (_client->available() == 0) {
            if (millis() - timeout > 5000) {
                _client->stop();
                return "ClientTimeoutError";
            }
        }  
    }
    else {
        _client->stop(); 
        return "ConnectionError";
    } 

    while(_client->available()){
        String line = _client->readStringUntil('\r');
        response+=line;
    }   
    _client->stop(); 
    return response; 

}
String Thing::GetTagValue(String text, String tag){

    String value;
    value = GetMidString(text,"<ErrorMessage>","</ErrorMessage>");
    if (value=="NoError")
    {   
        return GetMidString(text,"<"+tag+">","</"+tag+">");
    };
    //some error. show it and return empty value
    DEBUG_PRINTLN("Error getting value : "+value+" for tag :" +tag+".Error : "+value);
    return "";   

}
String Thing::GetMidString(String str, String start, String finish){
    int locStart = str.indexOf(start);
    if (locStart==-1) return "";
    locStart += start.length();
    int locFinish = str.indexOf(finish, locStart);
    if (locFinish==-1) return "";
    return str.substring(locStart, locFinish);
}