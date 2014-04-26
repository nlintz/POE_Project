//
//  ForceSensor.cpp
//  
//
//  Created by Team Arms Race on 4/26/14.
//
//

#include "ForceSensor.h"
#include "Arduino.h"

ForceSensor::ForceSensor(int pin)
{
    _pin = pin;
    _calibrationReference = NULL;
    pinMode(pin, INPUT);
}

float ForceSensor::getForce()
{
    int reading = getCalibratedReading();
    float force = (2.5/512.0) * (float)reading;
    return force;
}

int ForceSensor::getCalibratedReading()
{
    int reading = analogRead(_pin);
    reading -= _calibrationReference;
    return reading;
}

void ForceSensor::calibrate()
{
    const int n = 10;
    float reading = 0;
    for (int i=0; i<n; i++) // Get n readings and average them to calibrate
    {
        reading += analogRead(_pin);
    }
    _calibrationReference = reading / n;
}