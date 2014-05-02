//
//  Regulator.cpp
//  
//
//  Created by Team Arms Race on 4/26/14.
//
//

#include "Regulator.h"
#include "Arduino.h"
#include "Servo.h"

Regulator::Regulator(int pin)
{
    _pin = pin;
    Servo servo;
    _servo = servo;
    _servo.attach(_pin);
}

void Regulator::zero(){
	servo.write(170);
}

void Regulator::increasePressure(int step_size){
	// remvoe sign since we know we are increasing presssure
	step_size = abs(step_size);
	int current_pos = servo.read();
	servo.write(current_pos - step_size);
	
	// delay so servo has time to move there
	delay(50);
}

void Regulator::decreasePressure(int step_size){
	// remvoe sign since we know we are increasing presssure
	step_size = abs(step_size);
	int current_pos = servo.read();
	servo.write(current_pos + step_size);
	
	// delay so servo has time to move there
	delay(50);
}
