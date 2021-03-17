#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#include <SPI.h>
#include <MFRC522.h>
#define buzzer 2
#define SS_PIN 10
#define RST_PIN 9
#define ACCESS_DELAY 7000
#define led 5
MFRC522 mfrc522(SS_PIN, RST_PIN);   

void setup() 
{ 
  pinMode(buzzer,OUTPUT);
  pinMode(led,OUTPUT);
  lcd.begin();
  lcd.backlight();
  Serial.begin(9600);   
  SPI.begin();          
  mfrc522.PCD_Init(); 
  lcd.print("Put your card...");
  Serial.println("Put your card...");
  Serial.println();

}
void loop() 
{
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "B7 30 EB 11") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    digitalWrite(led,HIGH);
    delay(5000);
    digitalWrite(led,LOW);
    lcd.setCursor(0,1);
    lcd.print("Authorized access");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Put your card...");
    
  }
 
 else   { 

    lcd.setCursor(0,1);
    Serial.println(" Access denied");
    lcd.print(" Access denied");
    digitalWrite(buzzer,HIGH);
    delay(5000);
    digitalWrite(buzzer,LOW);
    lcd.clear();
     lcd.setCursor(0,0);
    lcd.print("Put your card...");
  }
}
