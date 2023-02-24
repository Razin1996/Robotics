/*
MT-19 Control
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

#define BASE_DIR 8
#define BASE_PWM A4

#define ACC1_DIR 9
#define ACC1_PWM A5

#define ACC2_DIR 10
#define ACC2_PWM A6

#define ACC3_DIR 11
#define ACC3_PWM A7

#define CLAW_DIR 12
#define CLAW_PWM A8

#define WRIST_DIR 13
#define WRIST_PWM A9

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
  pinMode(BASE_DIR,OUTPUT);
  pinMode(BASE_PWM,OUTPUT);
  pinMode(ACC1_DIR,OUTPUT);
  pinMode(ACC1_PWM,OUTPUT);
  pinMode(ACC2_DIR,OUTPUT);
  pinMode(ACC2_PWM,OUTPUT);
  pinMode(ACC3_DIR,OUTPUT);
  pinMode(ACC3_PWM,OUTPUT);
  pinMode(CLAW_DIR,OUTPUT);
  pinMode(CLAW_PWM,OUTPUT);
  pinMode(WRIST_DIR,OUTPUT);
  pinMode(WRIST_PWM,OUTPUT);

  analogWrite(RM1_PWM,0);
  analogWrite(RM2_PWM,0);
  analogWrite(LM1_PWM,0);
  analogWrite(LM2_PWM,0);
  analogWrite(BASE_PWM,0);
  analogWrite(ACC1_PWM,0);
  analogWrite(ACC2_PWM,0);
  analogWrite(ACC3_PWM,0);
  analogWrite(CLAW_PWM,0);
  analogWrite(WRIST_PWM,0);
  digitalWrite(RM1_DIR,LOW);
  digitalWrite(RM2_DIR,LOW);
  digitalWrite(LM1_DIR,LOW);
  digitalWrite(LM2_DIR,LOW);
  digitalWrite(BASE_DIR,LOW);
  digitalWrite(ACC1_DIR,LOW);
  digitalWrite(ACC2_DIR,LOW);
  digitalWrite(ACC3_DIR,LOW);
  digitalWrite(CLAW_DIR,LOW);
  digitalWrite(WRIST_DIR,LOW);

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
      
      case 'W':
      goForward();
      break;
      case 'S':
      goBackward();
      break;
      case 'A':
      goLeft();
      break;
      case 'D':
      goRight();
      break;
      
      case 'B':
      wheelStop();
      break;
      case 'V':
      armStop();
      break;
      
      case 'O':
      clawOpen();
      break;
      case 'P':
      clawClose();
      break;
      
      case '>':
      wristClockwise();
      break;
      case '<':
      wristAnticlockwise();
      break;

      case 'Y':
      acc3Open();
      break;
      case 'H':
      acc3Close();
      break;

      case 'T':
      acc2Open();
      break;
      case 'G':
      acc2Close();
      break;

      case 'R':
      acc1Open();
      break;
      case 'F':
      acc1Close();
      break;

      case 'M':
      baseClockwise();
      break;
      case 'N':
      baseAnticlockwise();
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

//arm_Base method....

void baseClockwise()
{
  digitalWrite(BASE_DIR,HIGH);
  analogWrite(BASE_PWM,255);

  Serial.println("Base Clockwise");  
}

void baseAnticlockwise()
{
  digitalWrite(BASE_DIR,LOW);
  analogWrite(BASE_PWM,255);

  Serial.println("Base Anticlockwise");  
}

//actuator1 method....

void acc1Open()
{
  digitalWrite(ACC1_DIR,HIGH);
  analogWrite(ACC1_PWM,255);

  Serial.println("Actuator1 Open");  
}

void acc1Close()
{
  digitalWrite(ACC1_DIR,LOW);
  analogWrite(ACC1_PWM,255);

  Serial.println("Actuator1 Close");  
}

//actuator2 method....

void acc2Open()
{
  digitalWrite(ACC2_DIR,HIGH);
  analogWrite(ACC2_PWM,255);

  Serial.println("Actuator2 Open");  
}

void acc2Close()
{
  digitalWrite(ACC2_DIR,LOW);
  analogWrite(ACC2_PWM,255);

  Serial.println("Actuator2 Close");  
}

//actuator3 method....

void acc3Open()
{
  digitalWrite(ACC3_DIR,HIGH);
  analogWrite(ACC3_PWM,255);

  Serial.println("Actuator3 Open");  
}

void acc3Close()
{
  digitalWrite(ACC3_DIR,LOW);
  analogWrite(ACC3_PWM,255);

  Serial.println("Actuator3 Close");  
}

//claw method....

void clawOpen()
{
  digitalWrite(CLAW_DIR,HIGH);
  analogWrite(CLAW_PWM,255);

  Serial.println("Claw Open");
}

void clawClose()
{
  digitalWrite(CLAW_DIR,LOW);
  analogWrite(CLAW_PWM,255);

  Serial.println("Claw Close");
}

//wrist method....

void wristClockwise()
{
  digitalWrite(WRIST_DIR,HIGH);
  analogWrite(WRIST_PWM,255);

  Serial.println("Wrist CW");  
}

void wristAnticlockwise()
{
  digitalWrite(WRIST_DIR,LOW);
  analogWrite(WRIST_PWM,255);

  Serial.println("Wrist CCW");  
}

void armStop()
{
  analogWrite(BASE_PWM,0);
  analogWrite(ACC1_PWM,0);
  analogWrite(ACC2_PWM,0);
  analogWrite(ACC3_PWM,0);
  analogWrite(CLAW_PWM,0);
  analogWrite(WRIST_PWM,0); 

  Serial.println("Arm Stop");   
}
