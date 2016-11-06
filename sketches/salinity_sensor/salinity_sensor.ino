#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void lcd_print(String s, int line){
  lcd.setCursor(0, line);
  lcd.print(s);
}

void clear_lcd(int line){
  lcd_print("                ", line);
}

void clear_entire_lcd(){
  clear_lcd(0);
  clear_lcd(1);
}

int salinity_pin = 3;
int first_resistance = 1000; // ohms
int voltage_readout;
float voltage_drop;
float measured_resistance;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init(); 
  lcd.begin(16, 2);
  lcd.backlight();
  lcd_print("fuck you", 0);
  delay(500);
  clear_entire_lcd();
  lcd_print("Ohms", 1);
}

void loop() {
  // put your main code here, to run repeatedly:
  voltage_readout = analogRead(salinity_pin);

  voltage_drop = float(voltage_readout) / 1023;
  measured_resistance = voltage_drop*first_resistance/(1 - voltage_drop);

  clear_lcd(0);
  lcd_print(String(measured_resistance), 0);

  delay(500);
}


