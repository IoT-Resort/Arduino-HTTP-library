class IoTResortHTTP
{
  public:
    IoTResortHTTP(char* IoTServer, int httpPort, String IoTThingSerial,);
    boolean SetIoTValue(String IoTValueName,String IoTValue );
    String GetIoTControlParameter(String IoTControlParameter );
  private:    
    String HttpRequest(String GetContent );
    String GetTagValue(String text, String tag);
    String GetMidString(String str, String start, String finish);
};
