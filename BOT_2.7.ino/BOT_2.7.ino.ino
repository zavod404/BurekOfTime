#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4); // set the LCD address to 0x27 for a 16 chars and 2 line display

int ledRdeca = 2;
int ledRumena = 3;
int ledZelena = 4;
int buzzer = 5;
int threshold = 300;
boolean L1;
boolean L2;
float checkTime;
float startTime;
float endTime;
bool ifFirst = 1;
bool ifFirstStart = 1;
float bestTime = 0;
float totalTime;
float speedTime1;

void setup() {

  Serial.begin(9600);
  
  pinMode(ledRdeca, OUTPUT);
  pinMode(ledRumena, OUTPUT);
  pinMode(ledZelena, OUTPUT);
  pinMode(buzzer, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("Usmeri laserje");
  while (analogRead(A2)<threshold && analogRead(A2)<threshold){       //ne bo spustil naprej, če laserja nista centrirana
  }
  lcd.clear();
}

void loop() {
  digitalWrite(ledRumena, LOW);
  digitalWrite(ledRdeca, HIGH);
  lcd.setCursor(0,0);
  
  L1 = ifL1();
  L2 = ifL2();
  switch(L1){
    case 1: // če prvi prižgan čakaj
      lcd.print("On your marks");
      if (bestTime != 0){
        lcd.setCursor(1,1);
        lcd.print("Best: " + String((bestTime/1000),3) + "s");
      }
      ifFirst = 1;
      break;
    case 0:  //če prvi prekinjen poglej če drugi prekinjen
      switch(L2){
        case 1:     //če ni, prižgi rumeno, prvič vzemi čas (ifFirst spremenljivka) in vsakič naslednjič poglej, če je že minilo random časa        
          digitalWrite(ledRumena, HIGH);
          lcd.clear();
          lcd.print("Get set");
          if (bestTime != 0){
            lcd.setCursor(1,1);
            lcd.print("Best: " + String((bestTime/1000),3) + "s");
          }
          delay(200);
          if (ifFirst == 1){
            checkTime = millis();
            ifFirst = 0;
          }
          if ((millis()-checkTime) >= random(3000. 7000){  //START!
            digitalWrite(ledRdeca, LOW);
            digitalWrite(ledRumena, LOW);
            digitalWrite(ledZelena, HIGH);
            tone(buzzer, 1000); // Send 1KHz sound signal...
            delay(100);        // ...for 1 sec
            noTone(buzzer);     // Stop sound...  
            lcd.clear();
            lcd.print("Goooo");
            startTime = millis(); //pogleda čas na začetku štopanja
            delay(2000);
            while(ifL1()){
            }
            speedTime1 = millis();
            while (ifL2()){
            }
            endTime = millis();//počaka da se prvi ugasne, pogleda čas, počaka, da se drugi ugasne, pogleda čas
            totalTime = endTime-startTime;
            digitalWrite(ledZelena, LOW);
            lcd.clear();
            lcd.print("Last lap:");
            lcd.setCursor(1,1);
            lcd.print(String((totalTime/1000),3)+"s v=" + String(((0.08/((endTime-speedTime1)/1000))*3.6),1)); //print last lap in hitrost na LCD
            if (bestTime == 0){
              bestTime = totalTime;
            } else if (totalTime < bestTime){
              bestTime = totalTime;
            }
            delay(6000);
            lcd.clear();
          }
          break;
        case 0:    //če prekinjen drugi laser pred štartom pejd na začetek
          ifFirst=1;
          lcd.print("On your marks");
          break;
      }
    break;  
  }
}


boolean ifL1() {               // funkciji, ki vrneta, a je laser vklopljen al ne
  if (analogRead(A2)>threshold){
    return(1);
  } else { return(0); }
}
boolean ifL2() {
  if (analogRead(A3)>threshold){
    return(1);
  } else { return(0); }
}
