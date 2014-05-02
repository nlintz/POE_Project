//
//  RegulatorTest_test.h test class
//  
//
//  Created by Team Arms Race on 4/26/14.
//
//

#ifndef RegulatorTest_h
#define RegulatorTest_h

#include "Arduino.h"
#include "Servo.h"
#include "AngleSensorTest.h"

class RegulatorTest
{
public:
    RegulatorTest();
    void zero();
    void increasePressure(int step_size);
    void decreasePressure(int step_size);
    AngleSensorTest _angle_sensor;
};

#endif
