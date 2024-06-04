#include <ESP32_Servo.h>

Servo myservo;  // create servo object to control a servo
                // 16 servo objects can be created on the ESP32
Servo myservo1;

int pos = 0;    // variable to store the servo position
int servoPin = 18;
int servoPin1=19;

// Define min and max pulse width values
int minPulseWidth = 500;   // Minimum pulse width in microseconds
int maxPulseWidth = 3000;  // Maximum pulse width in microseconds

void setup() {
  myservo.attach(servoPin, minPulseWidth, maxPulseWidth); // attaches the servo on pin 18 to the servo object
                                                          // using specified min/max pulse widths
  myservo1.attach(servoPin1, minPulseWidth, maxPulseWidth);
}

void loop() {
  /*for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 270 degrees
    myservo.write(pos);                 // tell servo to go to position in variable 'pos'
    delay(15);                          // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 270 degrees to 0 degrees
    myservo.write(pos);                 // tell servo to go to position in variable 'pos'
    delay(15);                          // waits 15ms for the servo to reach the position
  }*/
  myservo.write(0);
  myservo1.write(0);
  delay(5000);
  myservo.write(90);
  myservo1.write(90);
  delay(5000);
  myservo.write(180);
  myservo1.write(180);
  delay(5000);

}
