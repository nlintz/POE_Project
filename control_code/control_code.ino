#include <ForceSensor.h>
#include <Solenoid.h>
#include <AngleSensor.h>
#include <Regulator.h>
#include <Servo.h>


const int angleSensorPin = A0;
const int forceSensorPin = A1;
const int solenoidPin = 9;
const int regulatorPin = 3;

//NOTE: not final values
const float MAX_ANGLE = 49.0;
const float MIN_ANGLE = 5.0;

//when the sensor is below this value, treat it as zero
const float FORCE_CUTOFF = 0.1;

//how much to let the arm drift in the wrong directio nbefore throwing an error
const float WOBBLE_TOL = 10.0;

//shoud we break for errors
const bool ERROR_CHECKING = false;
const float TIME_DELAY = 1.5;

// devices
Regulator regulator (regulatorPin);
ForceSensor force_sensor (forceSensorPin);
Solenoid solenoid (solenoidPin);
AngleSensor angle_sensor (angleSensorPin);


int forceToStep(float force){
  int step_size;
  step_size = (int) 4*force;
  
  return  step_size;
}


int desired_step(){
  /* 
   * Processes sensor data to return desired step_size
   */
        
  //get force value
  float force;
  force = force_sensor.getForce();
  
  //if it is below trheshold, don't move
  if (abs(force) <= FORCE_CUTOFF)
  	force = 0;
        
  //get angle value
  int angle;
//  angle = angle_sensor.getAngle();
  angle = 20;
  //don't go past the end points
  int stop = 0;
  if (force > 0 && angle < MAX_ANGLE)
  	stop = 1;
  else if (force < 0 && angle > MIN_ANGLE)
  	stop = 1;
  	
  int step_size = forceToStep(force) * stop;	
  return step_size;
}


int go_down(int step_size){
  /*
   * Control loop for opening (deflating)  the arm
   */
	
  int error = 0;
  float old_angle, new_angle;
  old_angle = angle_sensor.getAngle();
  
  unsigned long old_time = millis();
  do{
    // if enough time has gone by, recalculate the old time and angle
    if (millis() - old_time > TIME_DELAY){
      old_angle = angle_sensor.getAngle();
      old_time = millis();
    }
    
    old_angle = angle_sensor.getAngle();
    regulator.decreasePressure(step_size);
		
    // if behaviour is not as expected, return non-zero error
    new_angle = angle_sensor.getAngle();
    
    if (ERROR_CHECKING) {
      if (new_angle >= old_angle + WOBBLE_TOL){
        error = 1;
        break;
      }
    }
    step_size = desired_step();
  } while(step_size < 0);
  
  return error;
}
//
int go_up(int step_size){
  /*
   * Control loop for closing (inflating) the arm
   */
  int error = 0;
  float old_angle, new_angle;
  old_angle = angle_sensor.getAngle();
  
  unsigned long old_time = millis();
  do{
    // if enough time has gone by, recalculate the old time and angle
    if (millis() - old_time > TIME_DELAY){
      old_angle = angle_sensor.getAngle();
      old_time = millis();
    }
    regulator.increasePressure(step_size);
		
    // if behaviour is not as expected, return non-zero error
    new_angle = angle_sensor.getAngle();
    if (ERROR_CHECKING) {
      if (new_angle <= old_angle - WOBBLE_TOL){
        error = 1;
        break;
      }
    }
    step_size = desired_step();
  } while(step_size > 0);
	
  return error;
}

int stay_put(){
  /*
   * Control loop for not moving the arm (no real control, just error detection)
   */
	
  int error = 0;
  float old_angle, new_angle;
  int step_size;
  old_angle = angle_sensor.getAngle();
  
  unsigned long old_time = millis();
  
  do{
    // if enough time has gone by, recalculate the old time and angle
    if (millis() - old_time > TIME_DELAY){
      old_angle = angle_sensor.getAngle();
      old_time = millis();
    }
    
    // wait a bit to make sure the arm isn't moving
    delay(50);

    // if behaviour is not as expected, return non-zero error
    new_angle = angle_sensor.getAngle();
    if (ERROR_CHECKING) {
      if (abs(new_angle - old_angle) > WOBBLE_TOL){
        Serial.println(abs(new_angle - old_angle));
        error = 1;
        break;
      }
    }
    step_size = desired_step();
  } while(step_size == 0); //NOTE: make threshold?
  
  return error;
}

void error_handler (int error_code){
  // vent error muscle
  solenoid.close();
  // set converter to 0psi output
  regulator.zero();
  // wait until the thing is reset
  while(true){
    delay(50);
  }
}


void setup(){
  // calibrate force sensor
  force_sensor.calibrate();
  angle_sensor.config();
  solenoid.config();
  regulator.config();
  
  // set regulator to 0psi output to begin
  regulator.zero();
  
  Serial.begin(9600);
  
  // set solenoid to vent
  solenoid.close();
  
  // delay to get the sens
  delay((int)TIME_DELAY * 500);
  
  //set solenoid to resevoir
  solenoid.open();
}

void loop() {
  /* 
   * Main control loop.  Acts as a delegator to the three other control loops:
   * 	1 go up
   *	2 go down
   *	3 stay put
   */
  int step_size;
  step_size = desired_step();
  int error = 0;
  if (step_size > 0)
    error = go_up(step_size);
  else if(step_size < 0)
    error = go_down(step_size);
  else
    error = stay_put();
  
  if(ERROR_CHECKING){
    if (error)
      error_handler(error);
  }
}
