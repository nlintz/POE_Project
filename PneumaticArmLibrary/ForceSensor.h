//
//  ForceSensor.h
//  
//
//  Created by Team Arms Race on 4/26/14.
//
//

#ifndef ForceSensor_h
#define ForceSensor_h

#include "Arduino.h"

class ForceSensor
{
public:
    ForceSensor(int pin);
    float getForce();
    void calibrate();
    int getCalibratedReading();

private:
    int _pin;
    int _calibrationReference;
    
};

#endif
