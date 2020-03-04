#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display


float vse_OK = 0;
float cas;
int lightSensor;
int meja = 0;
String MyString;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Ready");
  meja = analogRead(A0) - 200;
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("Ready");
  while(1){
    lightSensor=analogRead(A0);
    if (lightSensor < meja && vse_OK == 0 ) { //Prične s štopanjem časa
      cas = millis();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Counting...");
      vse_OK = 1;
      delay (5000);
    }
    else if (lightSensor < meja && vse_OK == 1){ // konča štopanje, ko presekaš žarek ta drugič
      cas = millis() - cas;
      lcd.setCursor(0,0);
      lcd.print("Finished in :");
      lcd.setCursor(0,1);
      cas = cas/1000;
      MyString = String(cas,3) + "s";
      lcd.print(MyString);
      vse_OK = 0;
      while(1){ //potreben restart Arduina, da se lahko znova začne meriti čas
        continue;
      }
      lcd.clear();
    }
}
}
