#include <DFRobot_sim808.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <Wire.h> //Including wire library
#include <SFE_BMP180.h> //Including BMP180 library
#define ALTITUDE 35.6 //Altitude where I live (change this to your altitude)
SFE_BMP180 pressure; //Creating an object

int mq2 = A5;
const int buzzer = 8;
const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance;
int tempV=0;
int tempB=0;

#define PHONE_NUMBER "+8801517016040"
#define MESSAGE1  "Your gas is under 20% tell us to refill."
#define MESSAGE2  "Gas is about to finish please refill it."
#define MESSAGE3  "I don't want to refill gas anymore. Thank you."
#define MESSAGE4  "Gas is leaking."
DFRobot_SIM808 sim808(&Serial);

SoftwareSerial mySerial(26,24);//RX,TX
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
    lcd.begin(16, 2);
    mySerial.begin(9600);
    Serial.begin(9600); //Starting serial communication
    pinMode(mq2, INPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(buzzer,OUTPUT);
    Serial.println("Program started");

  if (pressure.begin()) //If initialization was successful, continue
    Serial.println("BMP180 init success");
  else //Else, stop code forever
  {
    Serial.println("BMP180 init fail");
    while (1);
  }
  while(Serial.available()<0){
    
  }
  Serial.print(Serial.read());
}

void loop() {
  char status;
  double T, P, p0;
  status = pressure.startTemperature();
  if (status != 0) {
    delay(status);

    status = pressure.getTemperature(T);
    if (status != 0) {
      Serial.print("Temp: ");
      Serial.print(T, 1);
      Serial.println(" deg C");
      lcd.setCursor(0,1);
      lcd.print("T:");
      lcd.setCursor(2,1);
      lcd.print(T);

      status = pressure.startPressure(3);

      if (status != 0) {
        delay(status);

        status = pressure.getPressure(P, T);
        if (status != 0) {
//          Serial.print("Pressure measurement: ");
//          Serial.print(P);
//          Serial.println(" hPa (Pressure measured using temperature)");

          p0 = pressure.sealevel(P, ALTITUDE);
          Serial.print("Relative (sea-level) pressure: ");
          Serial.print(p0);
          Serial.println("hPa");
          lcd.setCursor(7,1);
          lcd.print("P:");
          lcd.setCursor(9,1);
          lcd.print(p0);
          if(p0<= 1015){
            if(tempV == 0){
               while(!sim808.init()) {
                delay(1000);
                Serial.print("Sim808 init error\r\n");
               }  
                Serial.println("Sim808 init success");
                Serial.println("Start to send message ...");

                //******** define phone number and text **********
                sim808.sendSMS(PHONE_NUMBER,MESSAGE1); 
              tempV++;
            }
          }
        }
      }
    }
  } 
  int mq2_reader = analogRead(mq2);
  lcd.setCursor(0,0);
  lcd.print("G:Normal");
  Serial.println(mq2_reader);
  if(mq2_reader > 350){
          lcd.setCursor(0,0);
      lcd.print("G:Alert!");
      if(tempB == 0){
      while(!sim808.init()) {
          delay(1000);
          Serial.print("Sim808 init error\r\n");
        }  
        Serial.println("Sim808 init success");
        Serial.println("Start to send message ...");

        //******** define phone number and text **********
        sim808.sendSMS(PHONE_NUMBER,MESSAGE4);
      }
  }
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  Serial.println(distance);
  if(distance >50){
      lcd.setCursor(9,0);
      lcd.print("Dish: N");
  }else{
      lcd.setCursor(9,0);
      lcd.print("Dish: Y");
  }
  while(mySerial.available()){
      char state = mySerial.read();
      if(state == 'Y'){
          getCylinder();
        }
       else if(state == 'N'){
          getNoCylinder();  
        }
    }
    delay(1000);
}

void getCylinder(){
        while(!sim808.init()) {
          delay(1000);
          Serial.print("Sim808 init error\r\n");
        }  
        Serial.println("Sim808 init success");
        Serial.println("Start to send message ...");

        //******** define phone number and text **********
        sim808.sendSMS(PHONE_NUMBER,MESSAGE2);
        Serial.println("Y"); 
    } 

void getNoCylinder(){
      while(!sim808.init()) {
        delay(1000);
        Serial.print("Sim808 init error\r\n");
      }  
      Serial.println("Sim808 init success");
      Serial.println("Start to send message ...");

      //******** define phone number and text **********
      sim808.sendSMS(PHONE_NUMBER,MESSAGE3);
      Serial.println("N"); 
      }
