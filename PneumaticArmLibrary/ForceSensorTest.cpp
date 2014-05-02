//
//  ForceSensorTest.cpp
//  
//
//  Created by Team Arms Race on 4/26/14.
//
//

#include "ForceSensorTest.h"
#include "Arduino.h"

ForceSensorTest::ForceSensorTest()
{

}

float ForceSensorTest::getForce()
{
    return 1.5;
}

float ForceSensorTest::getForceSin()
{
    return 2.0 * sin(millis()/1000.0);
}

void ForceSensorTest::calibrate()
{
    _calibrationReference = 0;
}
