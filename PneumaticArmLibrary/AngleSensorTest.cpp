//
//  AngleSensorTest.cpp
//
//
//  Created by Team Arms Race on 4/26/14.
//
//

#include "AngleSensorTest.h"
#include "Arduino.h"

AngleSensorTest::AngleSensorTest()
{
  _angle = 10.0;
}

float AngleSensorTest::getAngle()
{
  return _angle;
}

void AngleSensorTest::setAngle(float angle){
  _angle = angle;
  return;
}
