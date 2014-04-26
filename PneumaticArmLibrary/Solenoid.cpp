//
//  Solenoid.cpp
//  
//
// Created by Team Arms Race on 4/26/14.
//
//
#include "Arduino.h"
#include "Solenoid.h"

Solenoid::Solenoid(int pin)
{
    _pin = pin;
    _state = 0;
    pinMode(pin, OUTPUT);
}

void Solenoid::open()
{
    _state = 1;
    digitalWrite(_pin, HIGH);
}

void Solenoid::close()
{
    _state = 0;
    digitalWrite(_pin, LOW);
}

char * Solenoid::getState()
{
    if (_state == 0) {
        return "CLOSE";
    }
    else if (_state == 1) {
        return "OPEN";
    }
}