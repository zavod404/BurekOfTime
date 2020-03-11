#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display


float vse_OK = 0;
float cas;
int lightSensor;
int meja = 0;
String MyString;
int rdeca = 2;
int rumena = 3;
int zelena = 4;
int buzzer = 5;
float bestTime = 404.404;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Ready");
  meja = analogRead(A3) - 200;
  pinMode(rdeca, OUTPUT);
  pinMode(rumena, OUTPUT);
  pinMode(zelena, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("Start when ready");
  digitalWrite(zelena, HIGH);
  while(1){
    lightSensor=analogRead(A3);
    if (lightSensor < meja && vse_OK == 0 ) { //Prične s štopanjem časa
      cas = millis();
      lcd.clear();
      lcd.setCursor(0,0);
      digitalWrite(zelena, LOW);
      lcd.print("Timing...");
      digitalWrite(rumena, HIGH);
      lcd.setCursor(0,1);
  MyString = "  Best: " + String(bestTime,3) + "s";
      lcd.print(MyString);
      tone(buzzer, 1000); // Send 1KHz sound signal...
      delay(100);        // ...for 0,1 sec
      noTone(buzzer);     // Stop sound...
      vse_OK = 1;
      delay (5000);
    }
    else if (lightSensor < meja && vse_OK == 1){ // konča štopanje, ko presekaš žarek ta drugič
      cas = millis() - cas-121;
      lcd.setCursor(0,0);
      digitalWrite(rumena, LOW);
      lcd.clear();
      lcd.print("Last lap:");
      digitalWrite(rdeca, HIGH);
      lcd.setCursor(0,1);
      cas = cas/1000;
      
      if (cas < bestTime){
        bestTime=cas;
      }
      
      MyString = String(cas,3) + "s";
      lcd.print(MyString);
      tone(buzzer, 1000); // Send 1KHz sound signal...
      delay(100);        // ...for 1 sec
      noTone(buzzer);     // Stop sound...
      
      vse_OK = 0;
      delay(10000);
      digitalWrite(rdeca, LOW);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Start when ready");
      digitalWrite(zelena, HIGH);
      lcd.setCursor(0,1);
  MyString = "  Best: " + String(bestTime,3) + "s";
      lcd.print(MyString);
    }
}
}
