// Current code works for MKR1000 with two Adafruit MAX31856 Thermocouple Amplifiers (SPI) and one LCD display (i2c)
// Target: moniter the temperature of two identical furnaces with Type R thermocouples, show the temperature on LCD screen or Serial Moniter

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_MAX31856.h>

// SPI: CS1-SS1, DI-MOSI, DO-MISO, CLK-SCK;
Adafruit_MAX31856 left = Adafruit_MAX31856(7, 8, 10, 9);
// SPI: CS1-SS1, DI-MOSI, DO-MISO, CLK-SCK;
Adafruit_MAX31856 right = Adafruit_MAX31856(6, 8, 10, 9);
LiquidCrystal_I2C lcd(0x27,20,4);

void setup() {
  
  //Initialize the LCD display
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  
  delay(1000);
  Serial.print("Initialize Sensor");
  lcd.setCursor(0,0);
  lcd.print("Initialize Sensor");
  
  //Initialize the amplifier
  left.begin();
  left.setThermocoupleType(MAX31856_TCTYPE_R);
  
  right.begin();
  right.setThermocoupleType(MAX31856_TCTYPE_R);
  
  delay(1000);
  Serial.print("Initialized");
  lcd.setCursor(0,1);
  lcd.print("Initializd");
    
}

void loop() {
  
  //Diaplay Cold Junction Temperature at 1st line
  lcd.setCursor(0,0);
  lcd.print("CJ-L Temp: ");
  lcd.println(left.readCJTemperature());
  
  //Display Thermocouple Temperature at 2nd line
  lcd.setCursor(0,1);
  lcd.print("TC-L Temp: ");
  lcd.println(left.readThermocoupleTemperature());
  Serial.print("TC-L Temp: ");
  Serial.println(left.readThermocoupleTemperature());
  
  lcd.setCursor(0,2);
  lcd.print("CJ-R Temp: ");
  lcd.println(right.readCJTemperature());
  
  lcd.setCursor(0,3);
  lcd.print("TC-R Temp: ");
  lcd.println(right.readThermocoupleTemperature());
  Serial.print("TC-R Temp: ");
  Serial.println(right.readThermocoupleTemperature());
    
  delay(1000); //refresh every 1 second
    
}
