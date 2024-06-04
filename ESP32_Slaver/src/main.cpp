#include "BluetoothSerial.h"
#include <Arduino.h>
#include <Drive.h>  //Include the Drive library
#include <ESP32_Servo.h>


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;
const char *pin = "1234"; // 可以根据需要将其更改为更安全的 PIN
String device_name = "ESP32-BT-Slave"; // 蓝牙设备名称

Servo myservo;  // create servo object to control a servo
                // 16 servo objects can be created on the ESP32
Servo myservo1;

int pos = 45;    // variable to store the servo position
int pos1=90;
int servoPin = 18;
int servoPin1=19;

// Define min and max pulse width values
int minPulseWidth = 500;   // Minimum pulse width in microseconds
int maxPulseWidth = 3000;  // Maximum pulse width in microseconds

const int ledPin = 2; // 内置LED连接的引脚
const int bootPin = 0; // BOOT按钮连接的引脚

const int IN1 = 26;
const int IN2 = 27;
const int IN3 = 13;
const int IN4 = 12;

const int light=23;
int speed=315;
int flag1=0;
int foot=4;
/*void motordir(int out1, int out2, int out3, int out4) {
  digitalWrite(IN1, out1);
  digitalWrite(IN2, out2);
  digitalWrite(IN3, out3);
  digitalWrite(IN4, out4);
}*/
Drive drive(IN1, IN2, IN3, IN4);  //Create an instance of the function
void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT); // 设置LED引脚为输出模式
  pinMode(bootPin, INPUT_PULLUP); // 设置BOOT按钮引脚为输入模式，并启用上拉电阻
  pinMode(light, OUTPUT);

  pinMode(4, OUTPUT);

  SerialBT.begin(device_name); // 启动蓝牙串口
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
  SerialBT.setPin(pin);
  Serial.println("Using PIN");

  myservo.attach(servoPin, minPulseWidth, maxPulseWidth); // attaches the servo on pin 18 to the servo object
                                                          // using specified min/max pulse widths
  myservo1.attach(servoPin1, minPulseWidth, maxPulseWidth);

  myservo.write(45);
  myservo1.write(90);  

}

void loop() {
  if (SerialBT.available()) {
    char command = SerialBT.read();
    if (command == 'A') {
      digitalWrite(ledPin, HIGH); // 打开LED
      Serial.println("LED is ON");
    } else if (command == 'B') {
      digitalWrite(ledPin, LOW); // 关闭LED
      Serial.println("LED is OFF");
    }

    else if (command == '1') {
      drive.moveForward(speed);
      Serial.println("go");
      digitalWrite(4, HIGH);
      //delay(200);
    } else if (command == '2') {
      drive.turnRight(speed);
      Serial.println("left");
      //delay(200);
    } else if (command == '3') {
      drive.turnLeft(speed);
      Serial.println("right");
      //delay(200);
    } else if (command == '4') {
      drive.moveBackward(speed);
      Serial.println("back");
      //delay(200);
    } else  if (command == '0'){
      drive.moveForward(0);
      Serial.println("stay");
      digitalWrite(4, LOW);
      //delay(200);
    }
    else if(command=='5'){
      pos=pos+foot;
      if(pos>=180)
        pos=180;
      myservo.write(pos);
      
    }
    else if(command=='6'){
      pos=pos-foot;
      if(pos<=0)
        pos=0;
      myservo.write(pos);
      digitalWrite(light, HIGH);
    }
    else if(command=='7'){
      pos1=pos1+foot;
      if(pos1>=180)
        pos1=180;
      myservo1.write(pos1);
      digitalWrite(light, LOW);
    }
    else if(command=='8'){
      pos1=pos1-foot;
      if(pos1<=0)
        pos1=0;
      myservo1.write(pos1);
      
    }


  }
}
