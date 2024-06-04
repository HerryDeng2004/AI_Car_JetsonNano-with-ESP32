#include "BluetoothSerial.h"
#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
Adafruit_MPU6050 mpu;

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

#define LED_PIN   2
const int bootPin = 0; // BOOT按钮连接的引脚
BluetoothSerial SerialBT;
const char *pin = "1234"; // 蓝牙匹配代码
String slaveName = "ESP32-BT-Slave"; // 蓝牙从机名称
String myName = "ESP32-BT-Master"; // 蓝牙主机名称

const int x = 32;
const int y = 33;
int flag = 0;

void setup() {
  Serial.begin(115200);

  pinMode(26,OUTPUT);
  pinMode(25,OUTPUT);

  digitalWrite(26, HIGH);
  digitalWrite(25, LOW);

  pinMode(LED_PIN, OUTPUT); // 将LED引脚设置为输出模式
  digitalWrite(LED_PIN, LOW); // 关闭LED

  SerialBT.begin(myName, true); // 启动蓝牙串口
  Serial.printf("The device \"%s\" started in master mode, make sure slave BT device is on!\n", myName.c_str());
  SerialBT.setPin(pin); // 设置配对代码

  Serial.printf("Connecting to slave BT device named \"%s\"\n", slaveName.c_str());
  if (SerialBT.connect(slaveName)) {
    Serial.println("Connected Successfully!");
  } else {
    Serial.println("Failed to connect. Make sure remote device is available and in range, then restart app.");
  }
  //mpu6050
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }

  }

  pinMode(x, INPUT);
  pinMode(y, INPUT);
  pinMode(bootPin, INPUT_PULLUP);
}

void loop() {
  int x_value = analogRead(x);
  int y_value = analogRead(y);

  /*Serial.print(x_value);
  Serial.print(",");
  Serial.println(y_value);*/
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

 if (digitalRead(bootPin) == LOW) {
    digitalWrite(LED_PIN, HIGH);
    SerialBT.println('A');
    delay(100);
  } else {
    digitalWrite(LED_PIN, LOW);
    SerialBT.println('B');
    delay(100);
  }

  if (y_value >= 4000 || (x_value >= 4000 && y_value >= 4000)) {
    flag = 4;
    Serial.println(4);
    SerialBT.println('4');
    delay(100);
  } else if (x_value <= 100) {
    flag = 2;
    Serial.println(2);
    SerialBT.println('2');
    delay(100);
  } else if (x_value >= 4000) {
    flag = 3;
    Serial.println(3);
    SerialBT.println('3');
    delay(100);
  } else if (y_value <= 100) {
    flag = 1;
    Serial.println(1);
    SerialBT.println('1');
    delay(100);
  } else if(2500<=x_value<=3000&&2500<=y_value<=3000){
    flag = 0;
    Serial.println(0);
    SerialBT.println('0');
    delay(100);
  }

  if(a.acceleration.x>9){
    Serial.println(6);
    SerialBT.println('6');
    delay(100);
  }
  else if(a.acceleration.x<-3){
    Serial.println(5);
    SerialBT.println('5');
    delay(100);
  }
  else if(a.acceleration.z<-2){
    Serial.println(7);
    SerialBT.println('7');
    delay(100);
  }
  else if(a.acceleration.z>14){
    Serial.println(8);
    SerialBT.println('8');
    delay(100);
  }
  //delay(100);
}
