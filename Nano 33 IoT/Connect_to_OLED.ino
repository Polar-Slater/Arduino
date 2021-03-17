#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET -1 // "4" for reset pin on OLED or "-1" if using Arduino reset pin
#define SCREEN_ADDRESS 0x3c //scan i2c address before enter the address

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup(){
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);  //generate display voltage from 3.3V internally
  
  display.clearDisplay(); //clear the buffer
  display.setTextSize(1); //set text size to 1
  display.setTextColor(SSD1306_WHITE);  //set the color to white
  display.setCursor(0,0); //set the start point
  display.print("This is a test message.");
  
  display.display();  //tell the screen to display every time you change the content
  delay(1000);
}

void loop(){
  int i;
  int j;
  display.clearDisplay();
  
  for(i=0; i<display.width(); i+=10){
    for(j=0; j<display.height(); j+=8){
      display.setCursor(i,j);
      display.print("|A|");
      display.display();
      delay(1000);
    }
    
  }
}
