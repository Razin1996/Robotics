#include <DHT.h>
int in1 = 6;
int in2 = 7;
int ldr = A0;
int pir = 9;
#define DHTPIN 8
#define DHTTYPE DHT22
DHT dht (DHTPIN, DHTTYPE);

float h;
float t;

void setup() {
pinMode(pir,INPUT);
dht.begin();
pinMode(in1,OUTPUT);
pinMode(in2,OUTPUT);
Serial.begin(9600);
}

void loop() {
    h = dht.readHumidity();
    t = dht.readTemperature();
    //Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %, Temp: ");
    Serial.print(t);
    Serial.println(" Celsius");
  
  int pirValue = digitalRead(pir);
  int ldrValue = analogRead(ldr);
  Serial.println(ldrValue);
  if(pirValue == HIGH && ldrValue >= 50){
      digitalWrite(led, LOW);
      digitalWrite(in1,HIGH);
      digitalWrite(in2,HIGH);
      Serial.println("Motion detected but there is light outside.");
      delay(1000);
    }
    else if(pirValue == HIGH && ldrValue < 50){
      digitalWrite(led, HIGH);
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      Serial.println("Motion detected & there is dark outside");
      delay(1000);
    }
    else if(pirValue == LOW && ldrValue >= 50){
      digitalWrite(led, LOW);
      digitalWrite(in1,HIGH);
      digitalWrite(in2,HIGH);
      Serial.println("Motion stopped & there is light outside");
      delay(1000);
    }    
    else if(pirValue == LOW && ldrValue < 50){
      digitalWrite(led, LOW);
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      Serial.println("Motion stopped & there is dark outside ");
      delay(1000);
    }
}
