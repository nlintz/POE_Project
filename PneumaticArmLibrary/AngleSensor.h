//
//  AngleSensor.h
//  
//
//  Created by Team Arms Race on 4/26/14.
//
//

#ifndef AngleSensor_h
#define AngleSensor_h

#include "Arduino.h"

class AngleSensor
{
public:
    AngleSensor(int pin);
    void config();
    float getAngle();

private:
    int _pin;
    
};

#endif
