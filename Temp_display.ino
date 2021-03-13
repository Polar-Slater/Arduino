#include <Wire.h> 
#include <Adafruit_MAX31856.h>
#include <LiquidCrystal_I2C.h>

// SET SPI pin (CS-SS, SDI-MOSI, SDO-MISO, CLK-SCK)
// CS pin for two SPI device is different
Adafruit_MAX31856 maxthermo1 = Adafruit_MAX31856(7, 8, 10, 9);
Adafruit_MAX31856 maxthermo2 = Adafruit_MAX31856(6, 8, 10, 9);

// set the LCD address to 0x27 for a 16 chars and 2 line display
// TO check address, use i2c address.ino file
LiquidCrystal_I2C lcd1(0x27,16,2); 

void setup()
{
  //initialize the sencor and set the thermocouple type
  maxthermo1.begin();
  maxthermo1.setThermocoupleType (MAX31856_TCTYPE_K);
  maxthermo2.begin();
  maxthermo2.setThermocoupleType (MAX31856_TCTYPE_K);
  
  lcd1.init();                      // initialize the lcd 
  lcd1.backlight();
  
  lcd1.setCursor(2,0);
  lcd1.print("TC test");
  lcd1.setCursor(5,1);
  lcd1.print("BEGIN");

  delay(5000);

}


void loop()
{
  lcd1.setCursor(1,0);
  lcd1.print("CJ1 Temp: ");
  lcd1.println(maxthermo1.readCJTemperature());     // temperature detected inside the chip (ambient temp)
                                                   // to read the thermocouple temp: maxthermo.readThermocoupleTemperature()
  lcd1.setCursor(1,1);
  lcd1.print("CJ2 Temp: ");
  lcd1.println(maxthermo2.readCJTemperature());

  uint8_t fault = maxthermo1.readFault();
  if (fault) {
    if (fault & MAX31856_FAULT_CJRANGE) lcd1.println("CJRange");
    if (fault & MAX31856_FAULT_TCRANGE) lcd1.println("TCRange");
    if (fault & MAX31856_FAULT_CJHIGH)  lcd1.println("CJHIigh");
    if (fault & MAX31856_FAULT_CJLOW)   lcd1.println("CJLow");
    if (fault & MAX31856_FAULT_TCHIGH)  lcd1.println("TCHigh");
    if (fault & MAX31856_FAULT_TCLOW)   lcd1.println("TCLow");
    if (fault & MAX31856_FAULT_OVUV)    lcd1.println("OVUV");
    if (fault & MAX31856_FAULT_OPEN)    lcd1.println("Open");
  }

  delay(1000);
  
}
