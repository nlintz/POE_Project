//
//  Solenoid.h
//  
//
//  Created by Team Arms Race on 4/26/14.
//
//

#ifndef Solenoid_h
#define Solenoid_h

#include "Arduino.h"

class Solenoid
{
public:
    Solenoid(int pin);
    char * getState();
    void open();
    void config();
    void close();
private:
    int _state;
    int _pin;
};

#endif
