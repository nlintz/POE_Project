//
//  AngleSensorTest.h test class
//  
//
//  Created by Team Arms Race on 4/26/14.
//
//

#ifndef AngleSensorTest_h
#define AngleSensorTest_h

#include "Arduino.h"

class AngleSensorTest
{
public:
    AngleSensorTest();
    float getAngle();
    void setAngle(float angle);

private:
    float _angle;
    
};

#endif
