/*
MT-19 Bluetooth Wheel Control
created by Razin Bin Issa
Date: 12-11-2018
*/
#define RM1_DIR 4 
#define RM1_PWM A0
#define RM2_DIR 5
#define RM2_PWM A1

#define LM1_DIR 6 
#define LM1_PWM A2
#define LM2_DIR 7
#define LM2_PWM A3

int PWM = 0;

void setup() {
  pinMode(RM1_DIR,OUTPUT);
  pinMode(RM1_PWM,OUTPUT);
  pinMode(RM2_DIR,OUTPUT);
  pinMode(RM2_PWM,OUTPUT);
  pinMode(LM1_DIR,OUTPUT);
  pinMode(LM1_PWM,OUTPUT);
  pinMode(LM2_DIR,OUTPUT);
  pinMode(LM2_PWM,OUTPUT);
  
  analogWrite(RM1_PWM,0);
  analogWrite(RM2_PWM,0);
  analogWrite(LM1_PWM,0);
  analogWrite(LM2_PWM,0);
  digitalWrite(RM1_DIR,LOW);
  digitalWrite(RM2_DIR,LOW);
  digitalWrite(LM1_DIR,LOW);
  digitalWrite(LM2_DIR,LOW);

  Serial.begin(9600);
}

void loop() {
  while(Serial.available())
  {
    char state = Serial.read();
    switch(state)
    {
      case '0':
      PWM = 0;
      break;
      case '1':
      PWM = 51;
      break;
      case '2':
      PWM = 102;
      break;
      case '3':
      PWM = 153;
      break;
      case '4':
      PWM = 204;
      break;
      case '5':
      PWM = 255;
      break;
      
      case 'F':
      goForward();
      break;
      case 'B':
      goBackward();
      break;
      case 'L':
      goLeft();
      break;
      case 'R':
      goRight();
      break;
      
      case 'S':
      wheelStop();
      break;
    }
  }
}

//wheel method....

void goForward()
{
  digitalWrite(RM1_DIR,HIGH);
  analogWrite(RM1_PWM,255);
  digitalWrite(RM2_DIR,HIGH);
  analogWrite(RM2_PWM,255);

  digitalWrite(LM1_DIR,HIGH);
  analogWrite(LM1_PWM,255);
  digitalWrite(LM2_DIR,HIGH);
  analogWrite(LM2_PWM,255);
  
  Serial.println("Forward");  
}

void goBackward()
{
  digitalWrite(RM1_DIR,LOW);
  analogWrite(RM1_PWM,255);
  digitalWrite(RM2_DIR,LOW);
  analogWrite(RM2_PWM,255);

  digitalWrite(LM1_DIR,LOW);
  analogWrite(LM1_PWM,255);
  digitalWrite(LM2_DIR,LOW);
  analogWrite(LM2_PWM,255);
  
  Serial.println("Backward");  
}

void goLeft()
{
  digitalWrite(RM1_DIR,HIGH);
  analogWrite(RM1_PWM,255);
  digitalWrite(RM2_DIR,HIGH);
  analogWrite(RM2_PWM,255);

  digitalWrite(LM1_DIR,LOW);
  analogWrite(LM1_PWM,255);
  digitalWrite(LM2_DIR,LOW);
  analogWrite(LM2_PWM,255);
  
  Serial.println("Left");  
}

void goRight()
{
  digitalWrite(RM1_DIR,LOW);
  analogWrite(RM1_PWM,255);
  digitalWrite(RM2_DIR,LOW);
  analogWrite(RM2_PWM,255);

  digitalWrite(LM1_DIR,HIGH);
  analogWrite(LM1_PWM,255);
  digitalWrite(LM2_DIR,HIGH);
  analogWrite(LM2_PWM,255);
  
  Serial.println("Right");  
}

void wheelStop()
{
  analogWrite(RM1_PWM,0);
  analogWrite(RM2_PWM,0);
  analogWrite(LM1_PWM,0);
  analogWrite(LM2_PWM,0);

  Serial.println("Wheel Stop");
}
