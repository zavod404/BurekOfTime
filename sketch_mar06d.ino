#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// define vars
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

// define states
enum States {GETSET, WAIT, TIMING, BACK2START};
enum Sensors {NONE, L1, L2, BOTH}

void setup() {
  // put your setup code here, to run once:
  pinMode(ledrdeca,OUTPUT);
  pinMode(ledrumena,OUTPUT);
  pinMode(ledzelena,OUTPUT);
 
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Ready"); // LCD je pripravljen (ang.Ready)
}

void loop() {
  // put your main code here, to run repeatedly:

}


