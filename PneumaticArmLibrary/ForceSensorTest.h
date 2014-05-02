//
//  ForceSensorTest_test.h test class
//  
//
//  Created by Team Arms Race on 4/26/14.
//
//

#ifndef ForceSensorTest_h
#define ForceSensorTest_h

#include "Arduino.h"

class ForceSensorTest
{
public:
    ForceSensorTest();
    float getForce();
    float getForceSin();
    void calibrate();
    int getCalibratedReading();

private:
    int _pin;
    int _calibrationReference;
};

#endif
