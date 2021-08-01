#include <BluetoothSerial.h>
BluetoothSerial btSerial;
#define BT_NAME "ESP32BT-SCT" // Set bluetooth name

int bluetooth_signal = 0;

int in1 = 27;
int in2 = 26;
int in3 = 25;
int in4 = 33;

void setup() 
{
  Serial.begin(115200);
  btSerial.begin(BT_NAME);
  pinMode(27, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(33, OUTPUT);
}

void loop() 
{
  bluetoothControl();
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
  }
}

void goForward( byte rightLeft, byte rightSpeed)
{
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);
}

void turnLeft()
{
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
}

void turnRight()
{
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);
}

void goBackward(byte leftSpeed, byte rightSpeed)
{
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  digitalWrite(in3, 0);
  digitalWrite(in4,1);
}

void stopCar()
{
  digitalWrite(in1, 0);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 0);
}
