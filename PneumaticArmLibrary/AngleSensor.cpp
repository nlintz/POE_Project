//
//  AngleSensor.cpp
//
//
//  Created by Team Arms Race on 4/26/14.
//
//

#include "AngleSensor.h"
#include "Arduino.h"

AngleSensor::AngleSensor(int pin)
{
    _pin = pin;
}

void AngleSensor::config() {
	pinMode(_pin, INPUT);
}

float AngleSensor::getAngle()
{
    int reading = analogRead(_pin);
	//assumed reading 0 to 2.5 volts on a 0 to 1024 scale
	//and a angle range of 0 to 90
    float angle = ((float)reading - 164.0)*(52.0/(366.0-164.0));
    return angle;
}
