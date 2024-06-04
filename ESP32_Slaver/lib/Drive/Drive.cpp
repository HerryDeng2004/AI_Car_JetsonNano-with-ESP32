/*
  Drive.h - Library for controlling Robot Car with L298x bridge series
  Created by Oladapo E. Ajala, November 13, 2018.
  Released into the public domain.
  Copy right InvenTech llc.
*/

#include "Arduino.h"
#include "Drive.h"

#define LOW 0

Drive::Drive(int IN1, int IN2, int IN3, int IN4)
{
  pinMode(IN1, OUTPUT);  
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  _IN1 = IN1;
  _IN2 = IN2;
  _IN3 = IN3;
  _IN4 = IN4;
}

bool Drive::moveForward(int speed)
{
  analogWrite(_IN1, speed);
  analogWrite(_IN2, LOW);
  analogWrite(_IN3, speed);
  analogWrite(_IN4, LOW);  
  return true;
}

bool Drive::moveBackward(int speed)
{
  analogWrite(_IN1, LOW);
  analogWrite(_IN2, speed);
  analogWrite(_IN3, LOW);
  analogWrite(_IN4, speed); 
  return true;
}

bool Drive::turnLeft(int speed)
{
  analogWrite(_IN1, speed);
  analogWrite(_IN2, LOW);
  analogWrite(_IN3, LOW);
  analogWrite(_IN4, speed);
  return true;
}

bool Drive::turnRight(int speed)
{
  analogWrite(_IN1, LOW);
  analogWrite(_IN2, speed);
  analogWrite(_IN3, speed);
  analogWrite(_IN4, LOW);
  return true;  
}

bool Drive::stopMoving()
{
  analogWrite(_IN1, LOW);
  analogWrite(_IN2, LOW);
  analogWrite(_IN3, LOW);
  analogWrite(_IN4, LOW); 
  return true;  
}
