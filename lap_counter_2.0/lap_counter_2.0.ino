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

void setup() {
  // put your setup code here, to run once:
  pinMode(ledrdeca,OUTPUT);
  pinMode(ledrumena,OUTPUT);
  pinMode(ledzelena,OUTPUT);
 
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Ready"); // LCD je pripravljen (ang.Ready)
  mejaPrep = analogRead(A3) - 200; // postavi mejo, ko zarek sveti na senzor
  mejaStart = analogRead(A2) - 200;
  digitalWrite(ledrdeca,HIGH);
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("Ready");
  delay(1000);
  while (analogRead(A2) > mejaStart){ //če ne prekineš zarka za stopanje gre v stanje pripravljenosti
      digitalWrite(ledrdeca, HIGH);
      lcd.setCursor(0,0);
      lcd.print("Postavi se          ");
    while(analogRead(A3) < mejaPrep){ //če prekineš žarek za pripravljenost se prižge rumena
      repeatStart:
      lcd.setCursor(0,0);
      lcd.print("Pocakaj zeleno     ");
      timePrep = millis();
      waitPeriod = 5000 + random(500,5000);
      digitalWrite(ledrumena,HIGH);
      while(millis() < timePrep + waitPeriod){
        if (analogRead(A3) > mejaPrep || analogRead(A2) < mejaStart){
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
      if(analogRead(A2) < mejaStart){
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
  while(analogRead(A2) > mejaStart){
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
