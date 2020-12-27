/* ATtiny85 as an I2C Master   Ex2        BroHogan                           1/21/11
 * Modified for Digistump - Digispark LCD Shield by Erik Kettenburg 11/2012
 * SETUP:
 * ATtiny Pin 1 = (RESET) N/U                      ATtiny Pin 2 = (D3) N/U
 * ATtiny Pin 3 = (D4) to LED1                     ATtiny Pin 4 = GND
 * ATtiny Pin 5 = SDA on DS1621  & GPIO            ATtiny Pin 6 = (D1) to LED2
 * ATtiny Pin 7 = SCK on DS1621  & GPIO            ATtiny Pin 8 = VCC (2.7-5.5V)
 * NOTE! - It's very important to use pullups on the SDA & SCL lines!
 * PCA8574A GPIO was used wired per instructions in "info" folder in the LiquidCrystal_I2C lib.
 * This ex assumes A0-A2 are set HIGH for an addeess of 0x3F
 * LiquidCrystal_I2C lib was modified for ATtiny - on Playground with TinyWireM lib.
 * TinyWireM USAGE & CREDITS: - see TinyWireM.h
 */

//#define DEBUG
#include <TinyWireM.h>                  // I2C Master lib for ATTinys which use USI - comment this out to use with standard arduinos
#include <LiquidCrystal_attiny.h>
#include <DallasTemperature.h>

#define GPIO_ADDR     0x27
LiquidCrystal_I2C lcd(0x3F, 16, 2); // set address & 16 chars / 2 lines
#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);


void setup(){
  pinMode(3, OUTPUT);
  sensors.begin();
  lcd.init();                           // initialize the lcd 
  lcd.backlight();                      // Print a message to the LCD.
  lcd.setCursor(0,0); 
  lcd.print("LCD & I2C");
  delay(500);
  lcd.setCursor(0,1); 
  lcd.print("**********");
  delay(500);
}


void loop(){
sensors.requestTemperatures();
double temp = sensors.getTempCByIndex(0);
lcd.clear();
lcd.setCursor(0,0);
lcd.print(temp);
delay(1000);
if (temp>25) {
  lcd.backlight();
  digitalWrite(3, HIGH);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("przekroczona temp.");
  delay(1000);
  digitalWrite(3, LOW);
  lcd.noBacklight();
}

}

