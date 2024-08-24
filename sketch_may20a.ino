#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
Servo servo1;
Servo servo2;

#define IR_SENSOR_1 A0 // Pin for IR Sensor 1 (inside the gate)
#define IR_SENSOR_2 A1 // Pin for IR Sensor 2 (outside the gate)
#define buzzer 7

// Define threshold values for IR sensors
const int IR_THRESHOLD = 500; // Adjust this value based on your IR sensor sensitivity

#define RST_PIN 8
#define SS_PIN 10

int card1Balance = 1000; // Initial balance for card 1
int card2Balance = 400;  // Initial balance for card 2
int card3Balance = 1500;  // Initial balance for card 3
int card4Balance = 3000;  // Initial balance for card 4

MFRC522 mfrc522(SS_PIN, RST_PIN);

int servo1state = 0;
//int servo2state = 0;
int slot = 4;

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);

  servo1.attach(4);
  servo1.write(180);

  servo2.attach(5);
  servo2.write(0);

  pinMode(IR_SENSOR_1, INPUT);
  pinMode(IR_SENSOR_2, INPUT);
  pinMode(buzzer, OUTPUT);

  SPI.begin();
  mfrc522.PCD_Init();

  lcd.setCursor(6, 0);
  lcd.print("Welcome");
  Serial.print("Welcome");
  delay(3000);
  lcd.clear();
}

void loop() {
  // Read IR sensor values
  int ir1Value = analogRead(IR_SENSOR_1);
  int ir2Value = analogRead(IR_SENSOR_2);
  Serial.print("ir1Value");
  Serial.print(ir1Value);
  Serial.print("\n");
  Serial.print("ir2Value");
  Serial.print(ir2Value);
  Serial.print("\n");
  
  lcd.setCursor(0, 0);
  lcd.print("Available Slots: ");
  lcd.print(slot);

  
  if (slot == 0) {
    lcd.setCursor(0, 2);
    lcd.print("No available slots");
    delay(2000);
    lcd.clear();
//    servo1Down();
    servo1state == 0;
    lcd.print("Welcome");
  }

  rfid();

  if (servo1state == 1) {
    servo1Up();
    lcd.clear();
    lcd.setCursor(6, 1);
    lcd.print("Gate open");
    delay(3000);
    lcd.clear();
    servo1Down(); 
    servo1state = 0;
    slot--; // Decrease available slot by 1
  }


  // Check if car is approaching the gate
  if (ir1Value < IR_THRESHOLD) {
    // Car detected by IR1, open the gate
    openGate();
  }else if (ir2Value < IR_THRESHOLD) {
    // Car detected by IR2, close the gate
    closeGate();
  }
}

void servo1Down() {
  servo1.attach(4);
  for (int servo1Pos = 90; servo1Pos <= 180; servo1Pos += 1) {
    servo1.write(servo1Pos);
    delay(5);
  }
}

void servo1Up() {
  servo1.attach(4);
  for (int servo1Pos = 180; servo1Pos >= 90; servo1Pos -= 1) {
    servo1.write(servo1Pos);
    delay(5);
  }
}


void openGate() {
  servo2.attach(5);
  Serial.println("Closing gate");
  servo2.write(90);
  delay(1000); // Adjust delay time as needed for gate to fully open
}

void closeGate() {
  servo2.attach(5);
  Serial.println("Opening gate");
  servo2.write(0);
  if (slot == 4) {
    slot = slot;
  }
  else{
     slot++;
    }
  delay(1000); // Adjust delay time as needed for gate to fully close
}

void rfid() {
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();

  int fee = 0; // Default fee

  if (content.substring(1) == "A3 41 16 03") { // Card 1
    fee = 100; // Fee for card 1
  }
  else if (content.substring(1) == "F3 56 6A 19") { // Card 2
    fee = 200; // Fee for card 2
  }
  else if (content.substring(1) == "23 24 0B FE") { // Card 3
    fee = 300; // Fee for card 3
  }
  else if (content.substring(1) == "63 A9 12 FE") { // Card 4
    fee = 500; // Fee for card 4
  }
  else {
    tone(buzzer, 1000);
    lcd.setCursor(0, 1);
    lcd.print("Unknown Vehicle");
    lcd.setCursor(0, 2);
    lcd.print("Access denied");
    delay(1500);
    lcd.clear();
    noTone(buzzer); 
  }

  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Fee: ");
  lcd.print(fee);
  lcd.print(" Tk");

  // Check if card balance is sufficient
  if (content.substring(1) == "A3 41 16 03" && card1Balance > fee) { // Card 1
    if (slot == 0) {
      servo1state = 0;
    }
    else{
    card1Balance -= fee; // Deduct fee from card 1 balance
    lcd.setCursor(0, 2);
    lcd.print("Balance: ");
    lcd.print(card1Balance);
    lcd.print(" Tk");
    delay(2000); // Display balance for 2 seconds
    servo1state = 1;
    }
  }
  else if (content.substring(1) == "F3 56 6A 19" && card2Balance > fee) { // Card 2
    if (slot == 0) {
      servo1state = 0;
    }
    else{
    card2Balance -= fee; // Deduct fee from card 2 balance
    lcd.setCursor(0, 2);
    lcd.print("Balance: ");
    lcd.print(card2Balance);
    lcd.print(" Tk");
    delay(2000); // Display balance for 2 seconds
    servo1state = 1;
    }
  }
  else if (content.substring(1) == "23 37 19 FE" && card3Balance > fee) { // Card 3
    if (slot == 0) {
      servo1state = 0;
    }
    else{
    card3Balance -= fee; // Deduct fee from card 3 balance
    lcd.setCursor(0, 2);
    lcd.print("Balance: ");
    lcd.print(card3Balance);
    lcd.print(" Tk");
    delay(2000); // Display balance for 2 seconds
    servo1state = 1;
    }
  }
  else if (content.substring(1) == "63 A9 12 FE" && card4Balance > fee) { // Card 4
    if (slot == 0) {
      servo1state = 0;
    }
    else{
    card4Balance -= fee; // Deduct fee from card 4 balance
    lcd.setCursor(0, 2);
    lcd.print("Balance: ");
    lcd.print(card4Balance);
    lcd.print(" Tk");
    delay(2000); // Display balance for 2 seconds
    servo1state = 1;
    }
  }
  else {
    lcd.setCursor(0, 2);
    tone(buzzer, 1000);
    lcd.print("Insufficient Balance");
    delay(1000); // Display error for 2 seconds
    lcd.clear();
    servo1state = 0;
    noTone(buzzer);
  }
}
