#include <SPI.h>
#include <WiFiNINA.h>

char ssid[] = "XXXX";
char pass[] = "*********";
int status = WL_IDLE_STATUS;

void setup(){
  Serial.begin(9600);
  
  while (status != WL_CONNECTED){
    status = WiFi.begin(ssid, pass);
    Serial.print("Connecting to WiFi");
    delay(5*1000);
  }
  if (status = WL_CONNECTED){
    Serial.print("Connected");
    
  }
}

void loop(){
  
}
