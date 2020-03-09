#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display


float cas;
float best;
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
  while (analogRead(laserStart) > mejaStart){ //če ne prekineš zarka za stopanje gre v stanje pripravljenosti
      digitalWrite(ledrdeca, HIGH);
      lcd.setCursor(0,0);
      lcd.print("Get set!         ");
      while (analogRead(laserPrep) < mejaPrep){ //če prekineš žarek za pripravljenost se prižge rumena
        lcd.setCursor(0,0);
        lcd.print("Wait for it...    "); //dodaj delay in prilagodi timer
        delay(500);
        digitalWrite(ledrumena,HIGH);
        timePrep = millis();
        waitPeriod = random(1500,2000);  //to set
        while(millis() < timePrep + waitPeriod){    //konstantno preverjam if pogoj
          if (analogRead(laserPrep) > mejaPrep || analogRead(laserStart) < mejaStart){
            /*
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Too fast!        ");
            digitalWrite(ledrumena, LOW);
            delay(1500); //Počakam da se tekmovalec vrne na start
            break;
            */
          } //else if (analogRead(laserPrep) > mejaPrep || analogRead(laserStart) > mejaStart){
            /*
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Return to start!    ");
            digitalWrite(ledrumena, LOW);
            delay(500); //Počakam da se tekmovalec vrne na start
            break;
             */
          else {
            continue;
            /*
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Something else!    ");
            */
          }
        }
        digitalWrite(ledzelena, HIGH);
        digitalWrite(ledrumena, LOW);
        digitalWrite(ledrdeca, LOW);
        delay(1000);
        digitalWrite(ledzelena, LOW);
      } 
  }
}
