#include <Servo.h>

#define SEN_1_PIN A1
#define SEN_2_PIN A2
#define SEN_3_PIN A4
#define SEN_4_PIN A5

Servo ARM_SERVO1;
Servo ARM_SERVO2;
Servo ARM_SERVO3;
Servo ARM_SERVO4;
Servo ARM_SERVO5;
Servo EYE_SERVO;

const int trig = A0;
const int echo = A3;

int bluetooth_signal = 0;
int arm_servo1_pos =90;
int arm_servo2_pos =90;
int arm_servo3_pos =90;
int arm_servo4_pos =90;
int arm_servo5_pos;


void setup() 
{
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(12, OUTPUT);

  pinMode(A0, OUTPUT);
  pinMode(A3, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  
  ARM_SERVO1.attach(2);
  ARM_SERVO2.attach(10);
  ARM_SERVO3.attach(4);
  ARM_SERVO4.attach(5);
  ARM_SERVO5.attach(6);
  ARM_SERVO5.write(12);
  
  EYE_SERVO.attach(13);
  EYE_SERVO.write(90);
}

void loop() 
{
  bluetoothControl();
}

void bluetoothControl()
{
  if (Serial.available() > 0) 
  {
    bluetooth_signal = Serial.read();
  }
  switch (bluetooth_signal)
  {

/*Car moving control*/

    case 'a':
    {
      goForward(255, 255);
      break;
    }

    case 'b':
    {
      goBackward(255, 255);
      break;
    }

    case 'c':
    {
      turnLeft();
      break;
    }

    case 'd':
    {
      turnRight();
      break;
    }

    case 'e':
    {
      stopCar();
      break;
    }

    case 'f':
    {
      lineFollowing();
      break;
    }

    case 'g':
    {
      objectAvoiding();
      break;
    }
      
/*Robot arm control*/

    case 'p':
      if (arm_servo1_pos < 180)
      {
        arm_servo1_pos = (arm_servo1_pos + 1);
      }
      ARM_SERVO1.write(arm_servo1_pos);
      delay(20);
      break;
    case 'q':
      if (arm_servo1_pos > 0)
      {
        arm_servo1_pos = (arm_servo1_pos - 1);
      }
      ARM_SERVO1.write(arm_servo1_pos);
      delay(20);
      break;
      
    case 'h':
      if (arm_servo2_pos < 180)
      {
        arm_servo2_pos = (arm_servo2_pos + 1);
      }
      ARM_SERVO2.write(arm_servo2_pos);
      delay(20);
      break;
    case 'i':
      if (arm_servo2_pos > 0)
      {
        arm_servo2_pos = (arm_servo2_pos - 1);
      }
      ARM_SERVO2.write(arm_servo2_pos);
      delay(20);
      break;
      
    case 'j':
      if (arm_servo3_pos > 0)
      {
        arm_servo3_pos = (arm_servo3_pos - 1);
      }
      ARM_SERVO3.write(arm_servo3_pos);
      delay(20);
      break;
    case 'k':
      if (arm_servo3_pos < 180)
      {
      arm_servo3_pos = (arm_servo3_pos + 1);
      }
      ARM_SERVO3.write(arm_servo3_pos);
      delay(20);
      break;
      
    case 'r':
      if (arm_servo4_pos < 180)
      {
        arm_servo4_pos = (arm_servo4_pos + 1);
      }
      ARM_SERVO4.write(arm_servo4_pos);
      delay(20);
      break;
    case 's':
      if (arm_servo4_pos > 0)
      {
        arm_servo4_pos = (arm_servo4_pos - 1);
      }
      ARM_SERVO4.write(arm_servo4_pos);
      delay(20);
      break;
      
    case 'l':
      ARM_SERVO5.write(70);
      delay(20);
      break;
    case 'm':
      ARM_SERVO5.write(12);
      delay(20);
      break;
  }
}

void objectAvoiding()
{
  measureFrontDistance();
  delay(400);
  if (measureFrontDistance() > 30)
  {
    goForward(150, 150);
  }
  else
  {
    changePath();
  }
}

void changePath()
{
  stopCar();
  measureLeftDistance();
  delay(200);
  measureRightDistance();
  delay(200);
  {
    if (measureLeftDistance() > measureRightDistance())
    {
      turnLeft();
      delay(10);
    }
    else
    {
      turnRight();
      delay(10);
    }
  }
}


int measureFrontDistance() 
  {
   EYE_SERVO.write(90);
   delay(100); 
   unsigned long duration;
   int front_distance;
   digitalWrite(trig, 0);
   delayMicroseconds(2);
   digitalWrite(trig,1); 
   duration = pulseIn(echo, HIGH);
   front_distance = int(duration/2/29.412);
   return (front_distance);
  }

int measureLeftDistance() 
{ 
  EYE_SERVO.write(150);
  delay(100);
   unsigned long duration;
   int left_distance;
   digitalWrite(trig, 0);
   delayMicroseconds(2);
   digitalWrite(trig,1); 
   duration = pulseIn(echo, HIGH);
   left_distance = int(duration/2/29.412);
   return (left_distance);
}

int measureRightDistance() 
{ 
   EYE_SERVO.write(30);
   delay(100);
   unsigned long duration;
   int right_distance;
   digitalWrite(trig, 0);
   delayMicroseconds(2);
   digitalWrite(trig,1); 
   duration = pulseIn(echo, HIGH);
   right_distance = int(duration/2/29.412);
   return (right_distance);
}

void lineFollowing()
{
  char cSen_Status = 0b00000000;
  cSen_Status = cRead_Sensor();
  if((cSen_Status == 0b00001001) || (cSen_Status == 0b00001011) || (cSen_Status == 0b00001101))
  {
    goForward(150, 150);
  }
  else if((cSen_Status == 0b00001110) || (cSen_Status == 0b00001100) || (cSen_Status == 0b00001000) || (cSen_Status == 0b00000000))
  {
    goForward(150, 0);
  }
  else if((cSen_Status == 0b00000111) || (cSen_Status == 0b00000011) || (cSen_Status == 0b00000001))
  {
    goForward(0, 150);
  }
  else 
  {
    goBackward(150, 150);  
  }
}

char cRead_Sensor(void) //stop
{
  short sSen_Pin[4] = {SEN_1_PIN, SEN_2_PIN, SEN_3_PIN, SEN_4_PIN};
  char cStatus = 0b00000000;

  for(short i=0; i<4; i++)
  {
    cStatus = cStatus | (digitalRead(sSen_Pin[i]) << i);
  }

  return cStatus;
}

void goForward( byte rightLeft, byte rightSpeed)
{
  analogWrite(3, rightLeft);
  analogWrite(11, rightSpeed);
  digitalWrite(7, 1);
  digitalWrite(8, 0);
  digitalWrite(9, 1);
  digitalWrite(12, 0);
}

void turnLeft()
{
  analogWrite(3, 200);
  analogWrite(11, 200);
  digitalWrite(7, 1);
  digitalWrite(8, 0);
  digitalWrite(9, 0);
  digitalWrite(12, 1);
}

void turnRight()
{
  analogWrite(3, 200);
  analogWrite(11, 200);
  digitalWrite(7, 0);
  digitalWrite(8, 1);
  digitalWrite(9, 1);
  digitalWrite(12, 0);
}

void goBackward(byte leftSpeed, byte rightSpeed)
{
  analogWrite(3, leftSpeed);
  analogWrite(11, rightSpeed);
  digitalWrite(7, 0);
  digitalWrite(8, 1);
  digitalWrite(9, 0);
  digitalWrite(12,1);
}

void stopCar()
{
  analogWrite(3, 0);
  analogWrite(11, 0);
  digitalWrite(7, 0);
  digitalWrite(8, 0);
  digitalWrite(9, 0);
  digitalWrite(12, 0);
}
