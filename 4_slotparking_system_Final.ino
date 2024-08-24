#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo myservo;

#define ir_car1 5
#define ir_car2 6
#define ir_car3 7
#define ir_car4 8

int S1 = 0, S2 = 0, S3 = 0, S4 = 0;

int slot = 4;

void setup() {
  Serial.begin(9600);

  pinMode(ir_car1, INPUT);
  pinMode(ir_car2, INPUT);
  pinMode(ir_car3, INPUT);
  pinMode(ir_car4, INPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("  Car  Parking  ");
  lcd.setCursor(0, 1);
  lcd.print("     System     ");
  delay(3000);
  lcd.clear();

  Read_Sensor();

}

void loop() {

  Read_Sensor();

  lcd.setCursor(0, 0);
  if (S1 == 1) {
    lcd.print("1:Full ");
  } else {
    lcd.print("1:Empty");
  }

  lcd.setCursor(9, 0);
  if (S2 == 1) {
    lcd.print("2:Full ");
  } else {
    lcd.print("2:Empty");
  }

  lcd.setCursor(0, 1);
  if (S3 == 1) {
    lcd.print("3:Full ");
  } else {
    lcd.print("3:Empty");
  }

  lcd.setCursor(9, 1);
  if (S4 == 1) {
    lcd.print("4:Full ");
  } else {
    lcd.print("4:Empty");
  }
}

void Read_Sensor() {
  S1 = 0, S2 = 0, S3 = 0, S4 = 0;

  if (digitalRead(ir_car1) == 0) {
    S1 = 1;
  }
  if (digitalRead(ir_car2) == 0) {
    S2 = 1;
  }
  if (digitalRead(ir_car3) == 0) {
    S3 = 1;
  }
  if (digitalRead(ir_car4) == 0) {
    S4 = 1;
  }
}
