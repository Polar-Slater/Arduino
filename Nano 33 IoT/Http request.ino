#include <SPI.h>
#include <WiFiNINA.h>

int HTTP_PORT = 80;
String uid = "123";
String HTTP_METHOD = "GET";
char HOST_NAME[] = "api.bilibili.com";
String PATH_NAME = "/x/relation/stat";
String queryString = "?vmid=" + uid;

WiFiClient client;

void setup(){
  Serial.begin(9600);
  
  client.connect(HOST_NAME, HOST_PORT)
    if (client.connect()){
      Serial.print("Connected");
      
  
