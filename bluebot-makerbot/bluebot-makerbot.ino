#include <BluetoothSerial.h>
BluetoothSerial btSerial;
#define BT_NAME "ESP32BT-SCT" // Set bluetooth name

// Include Wire Library for I2C
#include <Wire.h>
 
// Include Adafruit PCA9685 Servo Library
#include <Adafruit_PWMServoDriver.h>
 
// Creat object to represent PCA9685 at default I2C address
Adafruit_PWMServoDriver pca9685 = Adafruit_PWMServoDriver(0x40);

int bluetooth_signal = 0;

#define SERVOMIN  80  // Minimum value
#define SERVOMAX  600  // Maximum value
#define SER1  7
#define SER2  6
#define SER3  5
#define SER4  4
#define SER5  3
int pwm1, pwm2, pwm3, pwm4, pwm5;
int arm_servo1_pos = 90, arm_servo2_pos = 90, arm_servo3_pos = 90, arm_servo4_pos = 90, arm_servo5_pos = 0; 

void setup() 
{
  Serial.begin(115200);
  btSerial.begin(BT_NAME);

  // Initialize PCA9685
  pca9685.begin();
 
  // Set PWM Frequency to 50Hz
  pca9685.setPWMFreq(50);
}

void loop() 
{
  bluetoothControl();
}

void goBackward( int rightLeft, int rightSpeed)
{
  pca9685.setPWM(8, 4096, 0);
  pca9685.setPWM(9, 0, rightLeft);
  pca9685.setPWM(10, 0, rightSpeed);
  pca9685.setPWM(11, 4096, 0);
}

void turnRight()
{
  pca9685.setPWM(8, 4096, 0);
  pca9685.setPWM(9, 0, 0);
  pca9685.setPWM(10, 4096, 0);
  pca9685.setPWM(11, 0, 0);
}

void turnLeft()
{
  pca9685.setPWM(8, 0, 0);
  pca9685.setPWM(9, 4096, 0);
  pca9685.setPWM(10, 0, 0);
  pca9685.setPWM(11, 4096, 0);
}

void goForward(int leftSpeed, int rightSpeed)
{
  pca9685.setPWM(8, 0, leftSpeed);
  pca9685.setPWM(9, 4096, 0);
  pca9685.setPWM(10, 4096, 0);
  pca9685.setPWM(11, 0, rightSpeed);
}

void stopCar()
{
  pca9685.setPWM(8, 0, 0);
  pca9685.setPWM(9, 0, 0);
  pca9685.setPWM(10, 0, 0);
  pca9685.setPWM(11, 0, 0);
}

void bluetoothControl()
{
  if (btSerial.available() > 0) 
  {
    bluetooth_signal = btSerial.read();
  }
  switch (bluetooth_signal)
  {

/*Car moving control*/

    case 'a':
    {
      goForward(4069, 4069);
      break;
    }

    case 'b':
    {
      goBackward(4069, 4069);
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

    case 'p':
      if (arm_servo1_pos < 180)
      {
        arm_servo1_pos = (arm_servo1_pos + 1);
      }
 
    // Determine PWM pulse width
    pwm1 = map(arm_servo1_pos, 0, 180, SERVOMIN, SERVOMAX);
    // Write to PCA9685
    pca9685.setPWM(SER1, 0, pwm1);
    delay(30);
    break;
    
    case 'q':
      if (arm_servo1_pos > 0)
      {
        arm_servo1_pos = (arm_servo1_pos - 1);
      }
 
    // Determine PWM pulse width
    pwm1 = map(arm_servo1_pos, 0, 180, SERVOMIN, SERVOMAX);
    // Write to PCA9685
    pca9685.setPWM(SER1, 0, pwm1);
    delay(30);
    break;
      
    case 'h':
      if (arm_servo2_pos < 180)
      {
        arm_servo2_pos = (arm_servo2_pos + 1);
      }
    pwm2 = map(arm_servo2_pos, 0, 180, SERVOMIN, SERVOMAX);
    // Write to PCA9685
    pca9685.setPWM(SER2, 0, pwm2);
    delay(30);
    break;
    
    case 'i':
      if (arm_servo2_pos > 0)
      {
        arm_servo2_pos = (arm_servo2_pos - 1);
      }
    pwm2 = map(arm_servo2_pos, 0, 180, SERVOMIN, SERVOMAX);
    // Write to PCA9685
    pca9685.setPWM(SER2, 0, pwm2);
    delay(30);
    break;
      
    case 'j':
      if (arm_servo3_pos > 0)
      {
        arm_servo3_pos = (arm_servo3_pos - 1);
      }
    pwm3 = map(arm_servo3_pos, 0, 180, SERVOMIN, SERVOMAX);
    // Write to PCA9685
    pca9685.setPWM(SER3, 0, pwm3);
    delay(30);
    break;
    
    case 'k':
      if (arm_servo3_pos < 180)
      {
      arm_servo3_pos = (arm_servo3_pos + 1);
      }
    pwm3 = map(arm_servo3_pos, 0, 180, SERVOMIN, SERVOMAX);
    // Write to PCA9685
    pca9685.setPWM(SER3, 0, pwm3);
    delay(30);
      break;
      
    case 'r':
      if (arm_servo4_pos < 180)
      {
        arm_servo4_pos = (arm_servo4_pos + 1);
      }
    pwm4 = map(arm_servo4_pos, 0, 180, SERVOMIN, SERVOMAX);
    // Write to PCA9685
    pca9685.setPWM(SER4, 0, pwm4);
    delay(30);
    break;
    
    case 's':
      if (arm_servo4_pos > 0)
      {
        arm_servo4_pos = (arm_servo4_pos - 1);
      }
    pwm4 = map(arm_servo4_pos, 0, 180, SERVOMIN, SERVOMAX);
    // Write to PCA9685
    pca9685.setPWM(SER4, 0, pwm4);
    delay(30);
    break;
      
    case 'l':
    pwm5 = map(55, 0, 180, SERVOMIN, SERVOMAX);
    // Write to PCA9685
    pca9685.setPWM(SER5, 0, pwm5);
    delay(30);
    break;
    
    case 'm':
    pwm5 = map(0, 0, 180, SERVOMIN, SERVOMAX);
    // Write to PCA9685
    pca9685.setPWM(SER5, 0, pwm5);
    delay(30);
    break;
  }
}
