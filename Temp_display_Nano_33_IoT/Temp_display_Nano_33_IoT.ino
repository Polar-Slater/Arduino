// Current code works for Nano 33 IoT with two Adafruit MAX31856 Thermocouple Amplifiers (SPI) and one LCD display (i2c)
// Target: moniter the temperature of two identical furnaces with Type R thermocouples, show the temperature on LCD screen or Serial Moniter

#include <Wire.h> 
#include <Adafruit_MAX31856.h>
#include <LiquidCrystal_I2C.h>

// SET SPI pin (CS-SS, SDI-MOSI, SDO-MISO, CLK-SCK)
// CS pin for two SPI device is different
Adafruit_MAX31856 leftthermo = Adafruit_MAX31856(7, 8, 10, 9);
Adafruit_MAX31856 rightthermo = Adafruit_MAX31856(6, 8, 10, 9);

// set the LCD address to 0x27 for a 20 chars and 4 line display
// TO check address, use i2c address.ino file
LiquidCrystal_I2C lcd(0x27,20,4); 

void setup()
{
  //initialize the sencor and set the thermocouple type
  leftthermo.begin();
  leftthermo.setThermocoupleType (MAX31856_TCTYPE_K);
  rightthermo.begin();
  rightthermo.setThermocoupleType (MAX31856_TCTYPE_K);
  
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  
  lcd.setCursor(2,0);
  lcd.print("Cell Temp");
  lcd.setCursor(5,1);
  lcd.print("BEGIN");

  delay(5000);

}


void loop()
{
  lcd.setCursor(1,0);
  lcd.print("CJ_L Temp: ");
  lcd.println(leftthermo.readCJTemperature());     // temperature detected inside the chip (ambient temp)
                                                   // to read the thermocouple temp: maxthermo.readThermocoupleTemperature()
  
   uint8_t fault = leftthermo.readFault();         // Check fault for the first amplifier
  if (fault) {
    if (fault & MAX31856_FAULT_CJRANGE) lcd.println("CJRange");
    if (fault & MAX31856_FAULT_TCRANGE) lcd.println("TCRange");
    if (fault & MAX31856_FAULT_CJHIGH)  lcd.println("CJHIigh");
    if (fault & MAX31856_FAULT_CJLOW)   lcd.println("CJLow");
    if (fault & MAX31856_FAULT_TCHIGH)  lcd.println("TCHigh");
    if (fault & MAX31856_FAULT_TCLOW)   lcd.println("TCLow");
    if (fault & MAX31856_FAULT_OVUV)    lcd.println("OVUV");
    if (fault & MAX31856_FAULT_OPEN)    lcd.println("Open");
  }
  
  lcd.setCursor(1,1);
  lcd.print("CJ-R Temp: ");
  lcd.println(rightthermo.readCJTemperature());

  uint8_t fault = rightthermo.readFault();         // Check fault for the second amplifier
  if (fault) {
    if (fault & MAX31856_FAULT_CJRANGE) lcd.println("CJRange");
    if (fault & MAX31856_FAULT_TCRANGE) lcd.println("TCRange");
    if (fault & MAX31856_FAULT_CJHIGH)  lcd.println("CJHIigh");
    if (fault & MAX31856_FAULT_CJLOW)   lcd.println("CJLow");
    if (fault & MAX31856_FAULT_TCHIGH)  lcd.println("TCHigh");
    if (fault & MAX31856_FAULT_TCLOW)   lcd.println("TCLow");
    if (fault & MAX31856_FAULT_OVUV)    lcd.println("OVUV");
    if (fault & MAX31856_FAULT_OPEN)    lcd.println("Open");
  }

  delay(1000);
  
}
