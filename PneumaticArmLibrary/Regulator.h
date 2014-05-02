//
//  Regulator.h
//  
//
//  Created by Team Arms Race on 4/26/14.
//
//

#ifndef Regulator_h
#define Regulator_h

#include "Arduino.h"
#include "Servo.h"

class Regulator
{
public:
    Regulator(int pin);
    void zero();
    void increasePressure(int step_size);
    void decreasePressure(int step_size);

private:
    int _pin;
    Servo _servo;
};

#endif
