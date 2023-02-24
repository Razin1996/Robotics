#include <LiquidCrystal.h>
#include <Wire.h>
#include <RTClib.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(8, 9);

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
String Data = "";

#define N_CHARS2  ((sizeof(MessageOut2)/sizeof(MessageOut2[0]))-1)

char MessageOut2[32];



int index2 = 0;
unsigned long oldTime2 = 0;

byte indexer = 0; // Index into array; where to store the character
char inData[58]; // Allocate some space for the string
char inChar; // Where to store the character read

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  lcd.begin(20 , 4);
  lcd.setCursor(2,0);
  lcd.print("Md. Saiful Islam");
  if (! rtc.begin()) {
     Serial.println("Couldn't find RTC");
     while (1);
   }
   if (rtc.lostPower()) {
     rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
   }
}

void loop() {
  DateTime now = rtc.now();
  lcd.setCursor(1,1);
  lcd.print("Developed by Razin");
  lcd.setCursor(1,2);
   lcd.print(now.year(), DEC);
   lcd.print('/');
   lcd.print(now.month(), DEC);
   lcd.print('/');
   lcd.print(now.day(), DEC);
   lcd.print("(");
   lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
   lcd.print(")");
   lcd.print(now.hour(), DEC);
   lcd.print(':');
   lcd.print(now.minute(), DEC);
   delay(3000);
//if(daysOfTheWeek[now.dayOfTheWeek()]== "Mon"){
    if(now.hour()==12 || now.hour()==13){
//        if(now.minute()> 30){
            lcd.setCursor(0,3);
            lcd.print("Class at UB10304");
            Serial.println("Class at UB10304");
//          }
      }
//  }

  char character;
  while(mySerial.available())
  {
    character = mySerial.read();
    switch(character)
    {
      case '0':
      goPrint();
      break;
    }
  }
 setHeadingLeft(" Developed by Mongol Tori Team.", 4, 10);
}

void goPrint(){
    lcd.setCursor(0,4);
    lcd.print("Hi");
    delay(2000);
  }

void setHeadingLeft(char * msg, byte row, unsigned long duration2) 
{
  strncpy(MessageOut2, msg, sizeof(MessageOut2));
  if(millis() - oldTime2 > duration2)
  {
     oldTime2 = millis();
     if(index2 < 20) // check to see if index2 is under the array max size
     {
        index2++; // increment index
        for (int i = 0; i < N_CHARS2; i++) // same as above
        {
           lcd.setCursor(i,row);
           if(index2 == N_CHARS2) index2 = 0;

              if(MessageOut2[index2++] != NULL){
                 lcd.print(MessageOut2[index2-1]);
                 Serial.println(MessageOut2[index2-1]);
        }
              else {
                 lcd.print(' ');
              }    
              }
           }
           else index2 = 0; // otherwise set it back to 0
     }
}
