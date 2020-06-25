#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display


float cas;
int mejaPrep = 0;
int mejaStart = 0;
unsigned long timePrep = 0;
int waitPeriod = 0;
String MyString;
int ledrdeca = 2;
int ledrumena = 3;
int ledzelena = 4;
int laserPrep = A3;
int laserStart = A2;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledrdeca,OUTPUT);
  pinMode(ledrumena,OUTPUT);
  pinMode(ledzelena,OUTPUT);
 
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Ready"); // LCD je pripravljen (ang.Ready)
  mejaPrep = analogRead(laserPrep) - 200; // postavi mejo, ko zarek sveti na senzor
  mejaStart = analogRead(laserStart) - 200;
  digitalWrite(ledrdeca,HIGH);
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("Ready");
  delay(1000);
  while (analogRead(laserStart) > mejaStart){ //če ne prekineš zarka za stopanje gre v stanje pripravljenosti
      digitalWrite(ledrdeca, HIGH);
      lcd.setCursor(0,0);
      lcd.print("Postavi se        ");
    while(analogRead(laserPrep) < mejaPrep){ //če prekineš žarek za pripravljenost se prižge rumena
      repeatStart:
      lcd.setCursor(0,0);
      lcd.print("Wait for it...   ");
      timePrep = millis();
      waitPeriod = 5000 + random(500,5000);
      digitalWrite(ledrumena,HIGH);
      while(millis() < timePrep + waitPeriod){
        if (analogRead(laserPrep) > mejaPrep || analogRead(laserStart) < mejaStart){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Prehiter start!");
          digitalWrite(ledrumena, LOW);
          delay(3000); //Počakam da se tekmovalec vrne na start
          goto repeatStart;
        }
      }
      
      digitalWrite(ledrumena, LOW);
      digitalWrite(ledrdeca, LOW);
      digitalWrite(ledzelena, HIGH);
      if(analogRead(A0) < mejaStart){
        break;
      }
      // delay(10000);
      // digitalWrite(ledzelena, LOW);
    }
  }

  //Stopanje časa
  cas = millis();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Counting...");
  while(analogRead(A0) > mejaStart){
    continue;
  }
  cas = millis() - cas;
  lcd.setCursor(0,0);
  lcd.print("Finished in :");
  lcd.setCursor(0,1);
  cas = cas/1000;
  MyString = String(cas,3) + " s";
  lcd.print(MyString);

}
