//
//  RegulatorTest.cpp
//  
//
//  Created by Team Arms Race on 4/26/14.
//
//

#include "RegulatorTest.h"
#include "Arduino.h"
#include "AngleSensorTest.h"

RegulatorTest::RegulatorTest()
{
    AngleSensorTest angle_sensor;
    _angle_sensor = angle_sensor;
}

void RegulatorTest::zero(){
	_angle_sensor.setAngle(0.0);
}

void RegulatorTest::increasePressure(int step_size){
	// just increase the angle
	step_size = abs(step_size);
	float current_angle = _angle_sensor.getAngle();
	_angle_sensor.setAngle(current_angle + ((float) step_size)/5.0);
	delay(50);
}

void RegulatorTest::decreasePressure(int step_size){
	// just decrease the angle
	step_size = abs(step_size);
	float current_angle = _angle_sensor.getAngle();
	_angle_sensor.setAngle(current_angle - ((float) step_size)/5.0);

	// delay so servo has time to move there
	delay(50);
}
