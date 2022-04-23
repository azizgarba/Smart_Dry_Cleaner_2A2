#include <LiquidCrystal.h>

#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
String UID = "A5 55 4B E7";
byte lock = 0;
int val;
Servo servo;
LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 rfid(SS_PIN, RST_PIN);
int buzzer=8 ;
int LED_R=4 ;


void setup() {
  Serial.begin(9600);
//  Serial.println("Listo!!");
  servo.write(70);


pinMode (buzzer,OUTPUT);
pinMode(LED_R, OUTPUT);
  lcd.init();
  lcd.backlight();
  servo.attach(3);
  SPI.begin();
  rfid.PCD_Init();
}

void loop() {
    lcd.backlight();
   lcd.setCursor(4,0);
  lcd.print("Welcome!");
  
    
    
  lcd.setCursor(1, 1);
  lcd.print("Put your card");

  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  
   
      lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scanning");
  Serial.print("NUID tag is :");
  String ID = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    lcd.print(".");
    ID.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    ID.concat(String(rfid.uid.uidByte[i], HEX));
    delay(300);
  }
  ID.toUpperCase();

  if (ID.substring(1) == "A5 55 4B E7" ) {
    servo.write(70);
    lcd.clear();
    lcd.setCursor(0,0);
     if(Serial.available()){
    val = Serial.parseInt();
    if(val==1){
    lcd.print("Access Approved!");
    delay(1500);
    lcd.clear();
    
  } 
     }
  }
   else {
    lcd.clear();
    lcd.setCursor(0, 0);
      if(Serial.available()){
    val = Serial.parseInt();
    if(val==0){
    lcd.print("Access Denied!");
    delay(1500);
    lcd.clear();
        digitalWrite(LED_R, HIGH);
  digitalWrite(buzzer,HIGH);
  delay (1000);
 digitalWrite(buzzer,LOW);
      digitalWrite(LED_R, LOW);
   delay (1000);
  }
      }}
}
