/*
  Drive.h - Library for controlling Robot Car with L298x bridge series
  Created by Oladapo E. Ajala, November 13, 2018.
  Released into the public domain.
  Copy right InvenTech inc.
*/

#ifndef Drive_h
#define Drive_h

#include "Arduino.h"

class Drive
{
  public:
    Drive(int IN1, int IN2, int IN3, int IN4);
    bool moveForward(int speed);
    bool moveBackward(int speed);
    bool turnRight(int speed);
    bool turnLeft(int speed);
    bool stopMoving();
  private:
	int _IN1;
	int	_IN2;
	int _IN3;
	int _IN4;
};

#endif
