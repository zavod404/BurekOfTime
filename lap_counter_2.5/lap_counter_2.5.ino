#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display


float cas;
int mejaPrep = 0; //treba stestirat katere vrednosti so, ko laser gor sveti
int mejaStart = 0;
unsigned long timePrep = 0;
int waitPeriod = 0;
String MyString;
int ledrdeca = 2;
int ledrumena = 3;
int ledzelena = 4;
int Buzzer = 5;
int najboljsiCas = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledrdeca,OUTPUT);
  pinMode(ledrumena,OUTPUT);
  pinMode(ledzelena,OUTPUT);
  pinMode(Buzzer,OUTPUT);
 
  lcd.init();
  lcd.backlight();
  lcd.clear();
  while(1){
  if (analogRead(A3) < mejaPrep){
    if(analogRead(A2)< mejaStart){
      lcd.setCursor(0,0);
      lcd.print("/__");
      lcd.setCursor(0,1);
      lcd.print("\\  ");
      lcd.setCursor(12,0);
      lcd.print("__\\");
      lcd.setCursor(14,1);
      lcd.print("/");
      delay(100);
    }else{
      lcd.setCursor(0,0);
      lcd.print("/__");
      lcd.setCursor(0,1);
      lcd.print("\\  ");
      delay(100);
    }
  }else if(analogRead(A2)< mejaStart){
    lcd.setCursor(12,0);
    lcd.print("__\\");
    lcd.setCursor(14,1);
    lcd.print("/");
    delay(100);
  }
  cas = millis();
  if((analogRead(A3) > mejaPrep) & (analogRead(A2)> mejaStart) & ((millis()-cas) > 5000)){
    break;
  }
  }
  lcd.clear();
  digitalWrite(ledrdeca,HIGH);
  lcd.setCursor(0,0);
  lcd.print("Ready!");
}

void loop() {
  while (analogRead(A2) > mejaStart){ //če ne prekineš zarka za stopanje gre v stanje pripravljenosti
    while(analogRead(A3) < mejaPrep){ //če prekineš žarek za pripravljenost se prižge rumena
      repeatStart:
      lcd.setCursor(0,0);
      lcd.print("Wait for it...");
      timePrep = millis();
      waitPeriod = 3000 + random(300,3000);
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
      break;
      // delay(10000);
      // digitalWrite(ledzelena, LOW);
    }
  }
  //Stopanje časa
  cas = millis();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("GO!");
  digitalWrite(Buzzer,HIGH);
  delay(2000);
  digitalWrite(Buzzer,LOW);
  while(analogRead(A2) > mejaStart){
    lcd.setCursor(0,1);
    lcd.print(cas);
    continue;
  }
  cas = millis() - cas;
  lcd.setCursor(0,0);
  lcd.print("Finished in :");
  lcd.setCursor(0,1);
  cas = cas/1000;
  MyString = String(cas,3) + " s";
  lcd.print(MyString);
  delay(10000);
  if(najboljsiCas < cas){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Prejšnji najboljši čas: " + String(najboljsiCas) + "s");
    najboljsiCas = cas;
    lcd.setCursor(0,1);
    lcd.print("Nov najboljši čas pa je:" + najboljsiCas + 's'); 
    
  }else{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Najboljši čas: ");
    lcd.setCursor(0,1);
    lcd.print(najboljsiCas);
  }
   while(analogRead(A2) > mejaStart){
    continue;
   }
}
