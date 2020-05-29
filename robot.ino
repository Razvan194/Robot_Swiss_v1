#include <Wire.h>
#include <Servo.h>
#include <LedControl.h>
#include <LiquidCrystal_I2C.h>
Servo servo;

int trigPin = A1;
int echoPin = A0;
float pingTime;
int timp = 500;

int s1 = 12;
int s2 = 11;
int s3 = 10;
int s4 = 9;
int s5 = 8;
int buton = 7;

int a1 = 2;
int a2 = 5;
int b1 = 4;
int b2 = 3;

int s = 140;

// matrix led
 
int CLK = 13;
int DIN = A3;
int CS = A2; 
byte dreapta[] = {0x18,0x0c,0x06,0xff,0xff,0x06,0x0c,0x18};
byte stanga[] = {0x18,0x30,0x60,0xff,0xff,0x60,0x30,0x18};
byte inainte[] = {0x18,0x3c,0x7e,0xdb,0x99,0x18,0x18,0x18};
byte spate[] = {0x18,0x18,0x18,0x99,0xdb,0x7e,0x3c,0x18};
LedControl lc =LedControl(DIN,CLK,CS ,0);

LiquidCrystal_I2C lcd(0x3F, 16, 2);
char Program[16];

void setup() {
  // put your setup code here, to run once:
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
  pinMode(s4, INPUT);
  pinMode(s5, INPUT);
  pinMode(buton, INPUT);
   servo.attach(6);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(250000);

  lc.shutdown(0,false);
  lc.setIntensity(0,15);
  lc.clearDisplay(0);

  lcd.init();
  lcd.backlight();
  
}

void loop() {
  // put your main code here, to run repeatedly:
 
         urmaritor_linie();
      // ocolitor_obstacole();
  }

  
    
void controlDirection( int d , int s ) {
  switch( d ) {
      case 0:
        // STOP Normal
        digitalWrite(a1, LOW);
        digitalWrite(a2, LOW);
        digitalWrite(b1, LOW);
        digitalWrite(b2, LOW);
        break;
      case 1:
        // Forward
        digitalWrite(a1, HIGH);
        analogWrite(a2, 255-s);
        digitalWrite(b1, HIGH);
        analogWrite(b2, 255-s);
        break;
     case 2:
        // Reverse
        digitalWrite(a1, LOW);
        analogWrite(a2, 255-s);
        digitalWrite(b1, LOW);
        analogWrite(b2, 255-s);
        break;
     case 3:
        // Wide Right
        digitalWrite(a1, LOW);
        digitalWrite(a2, LOW);
        digitalWrite(b1, HIGH);
        digitalWrite(b2, LOW);
        break;
     case 4:
        // Tight Right
        digitalWrite(a1, LOW);
        digitalWrite(a2, HIGH);
        digitalWrite(b1, HIGH);
        digitalWrite(b2, LOW);
        break;
     case 5:
        // Wide Left
        digitalWrite(a1, HIGH);
        digitalWrite(a2, LOW);
        digitalWrite(b1, LOW);
        digitalWrite(b2, LOW);
        break;
     case 6:
        // Tight Left
        digitalWrite(a1, LOW);
        digitalWrite(a2, HIGH);
        digitalWrite(b1, HIGH);
        digitalWrite(b2, LOW);
        break;
     case 10:
        // STOP Fast
        digitalWrite(a1, HIGH);
        digitalWrite(a2, HIGH);
        digitalWrite(b1, HIGH);
        digitalWrite(b2, HIGH);
        break;
  }
}

int distantascan(){
  digitalWrite(trigPin, LOW);
  delay(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); //Microsecunde 1/1000000
  digitalWrite(trigPin, LOW);

  pingTime = pulseIn(echoPin, HIGH);

//Transformam din Microsecunde in Secunde
//Viteza sunetului este de 343,4 m/s

  float secunde = pingTime / 1000000;
  float metri = secunde * 343;
  float cm = metri * 100;
  cm = cm/2;
  Serial.println("distanta este: ");
  Serial.print(cm);
  return cm;
  
}

void printByte(byte caracter[]){
  for(int i = 0; i<8;i++){
    lc.setRow(0,i,caracter[i]);
  }
}

void urmaritor_linie(){

  int senzor1 = digitalRead(s1);
  int senzor2 = digitalRead(s2);
  int senzor3 = digitalRead(s3);
  int senzor4 = digitalRead(s4);
  int senzor5 = digitalRead(s5);
  int senzorButon = digitalRead(buton);
  
  if(senzor1 == LOW && senzor2 == HIGH && senzor3 == HIGH && senzor4 == HIGH && senzor5 == HIGH && senzorButon == LOW){
 controlDirection(5,s);
 lcd.print("merg dreapta");
    lcd.clear();
}else if(senzor1 == LOW && senzor2 == LOW && senzor3 == HIGH && senzor4 == HIGH && senzor5 == HIGH && senzorButon == LOW){
  controlDirection(5,s);
  lcd.print("merg dreapta");
    lcd.clear();
}else if(senzor1 == HIGH && senzor2 == LOW && senzor3 == HIGH && senzor4 == HIGH && senzor5 == HIGH && senzorButon == LOW){
  controlDirection(5,s);
  lcd.print("merg dreapta");
    lcd.clear();
}else if(senzor1 == HIGH && senzor2 == LOW && senzor3 == LOW && senzor4 == HIGH && senzor5 == HIGH && senzorButon == LOW){
  controlDirection(5,s);
  lcd.print("merg dreapta");
    lcd.clear();
}else if(senzor1 == HIGH && senzor2 == HIGH && senzor3 == LOW && senzor4 == HIGH && senzor5 == HIGH && senzorButon == LOW){
  controlDirection(1,s);
  lcd.print("merg in fata");
   lcd.clear();
}else if(senzor1 == HIGH && senzor2 == HIGH && senzor3 == LOW && senzor4 == LOW && senzor5 == HIGH && senzorButon == LOW){
  controlDirection(3,s);
   lcd.print("merg stanga");
    lcd.clear();
}else if(senzor1 == HIGH && senzor2 == HIGH && senzor3 == HIGH && senzor4 == LOW && senzor5 == HIGH && senzorButon == LOW){
  controlDirection(3,s);
  lcd.print("merg stanga");
    lcd.clear();
}else if(senzor1 == HIGH && senzor2 == HIGH && senzor3 == HIGH && senzor4 == LOW && senzor5 == LOW && senzorButon == LOW){
  controlDirection(3,s);
  lcd.print("merg stanga");
    lcd.clear();
}else if(senzor1 == HIGH && senzor2 == HIGH && senzor3 == HIGH && senzor4 == HIGH && senzor5 == LOW && senzorButon == LOW){
  controlDirection(3,s);
  lcd.print("merg stanga");
    lcd.clear();
}else if(senzor1 == HIGH && senzor2 == HIGH && senzor3 == LOW && senzor4 == HIGH && senzor5 == HIGH && senzorButon == HIGH){
  controlDirection(0,0);
  lcd.print("stationez");
    lcd.clear();
}else{
  controlDirection(0,0);
}
}

void ocolitor_obstacole(){
  int distRight = 0;
int distLeft = 0;

servo.write(90);
  if (distantascan() > 20){
   controlDirection(1,s);
   printByte(inainte);
   lcd.print("merg in fata");
   delay(300);
   lcd.clear();
  }
  else{
    controlDirection(0,s);
    delay(500);
    servo.write(0);
    distRight = distantascan();
    lcd.print("scaneaza dreapta");
    delay(500);
    lcd.clear();
    servo.write(180);
    delay(500);
    distLeft = distantascan();
    lcd.print("scaneaza stanga");
    delay(500);
    lcd.clear();
    servo.write(90);
    delay(500);
    
    if(distRight <= distLeft){
      controlDirection(2,0);
      lcd.print("merg in spate");
      delay(500);
      lcd.clear();
      printByte(spate);
      delay(300);
      controlDirection(5,s);
      
      delay(400);
      printByte(stanga);
      lcd.print("merg stanga");
      delay(300);
      lcd.clear();
    }
    else{
     controlDirection(2,0);
     lcd.print("merg in spate");
      delay(500);
      lcd.clear();
      printByte(spate);
      delay(1000);
      controlDirection(3,s);
      delay(400);
      printByte(dreapta);
      lcd.print("merg dreapta");
      delay(300);
      lcd.clear();
    }
  }
}
