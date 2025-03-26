#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MPU6050.h>

Adafruit_SSD1306 display(128, 32, &Wire, -1);
Adafruit_MPU6050 mpu;

// Display center coordinates and radius
const int centerX = 64;
const int centerY = 16;
const int circleRadius = 15;

void setup() {
  Serial.begin(9600);
  
  // Initialize OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  // Initialize MPU6050
  if (!mpu.begin()) {
    Serial.println("MPU6050 not found!");
    while(1);
  }
  
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  
  // Draw static elements
  display.clearDisplay();
  // Draw circle
  display.drawCircle(centerX, centerY, circleRadius, SSD1306_WHITE);
  // Draw center crosshair
  display.drawLine(centerX-5, centerY, centerX+5, centerY, SSD1306_WHITE);
  display.drawLine(centerX, centerY-5, centerX, centerY+5, SSD1306_WHITE);
  display.display();
  delay(1000);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Convert to G-forces
  float x_g = a.acceleration.x / 9.81;
  float y_g = a.acceleration.y / 9.81;

  // Map acceleration to screen coordinates
  int dotX = centerX + (x_g * circleRadius / 2); // 2G max range
  int dotY = centerY - (y_g * circleRadius / 2); // Invert Y axis

  // Constrain dot to circle boundaries
  dotX = constrain(dotX, centerX - circleRadius, centerX + circleRadius);
  dotY = constrain(dotY, centerY - circleRadius, centerY + circleRadius);

  // Update display
  display.clearDisplay();
  
  // Redraw static elements
  display.drawCircle(centerX, centerY, circleRadius, SSD1306_WHITE);
  display.drawLine(centerX-5, centerY, centerX+5, centerY, SSD1306_WHITE);
  display.drawLine(centerX, centerY-5, centerX, centerY+5, SSD1306_WHITE);
  
  // Draw acceleration dot
  display.fillCircle(dotX, dotY, 2, SSD1306_WHITE);
  
  // Add text labels
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 16);
  display.print("X:"); display.print(x_g, 1);
  display.print(" Y:"); display.print(y_g, 1);
  
  display.display();
  delay(50);
}
