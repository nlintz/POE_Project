#include <AngleSensor.h>
#include <RegulatorTest.h>
#include <ForceSensorTest.h>
#include <Regulator.h>
#include <Solenoid.h>
#include <ForceSensor.h>
#include <AngleSensorTest.h>

#include <Servo.h>


const int angleSensorPin = A0;
const int forceSensorPin = A1;
const int solenoidPin = 2;
const int regulatorPin = 3;

//NOTE: not final values
const float MAX_ANGLE = 53.0;
const float MIN_ANGLE = 0.0;

//when the sensor is below this value, treat it as zero
const float forceCutoff = 0.1;

// devices
RegulatorTest regulator;
ForceSensorTest force_sensor;
Solenoid solenoid (solenoidPin);
AngleSensorTest* angle_sensor = &regulator._angle_sensor;


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
  force = force_sensor.getForceSin();
  
  //if it is below trheshold, don't move
  if (abs(force) <= forceCutoff)
  	force = 0;
        
  //get angle value
  int angle;
  angle = angle_sensor->getAngle();
  
  Serial.print("Angle: ");
  Serial.print(angle);
  
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
  
  do{
    
    old_angle = angle_sensor->getAngle();
    regulator.decreasePressure(step_size);
		
    // if behaviour is not as expected, return non-zero error
    new_angle = angle_sensor->getAngle();
    
    if (new_angle >= old_angle){
      error = 1;
      break;
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
  do{
    old_angle = angle_sensor->getAngle();
    regulator.increasePressure(step_size);
		
    // if behaviour is not as expected, return non-zero error
    new_angle = angle_sensor->getAngle();
    if (new_angle <= old_angle){
      error = 1;
      break;
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
  
  //tollerence in movement
  int tol = 1;
  do{
    old_angle = angle_sensor->getAngle();
    
    // wait a bit to make sure the arm isn't moving
    delay(50);

    // if behaviour is not as expected, return non-zero error
    new_angle = angle_sensor->getAngle();
    if (abs(new_angle - old_angle) > tol){
      error = 1;
      break;
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
  Serial.println("error");
  while(true){
    delay(50);
  }
}


void setup(){
  // calibrate force sensor
  force_sensor.calibrate();
  
  // set solenoid to resevoir
  solenoid.open();
  
  // set regulator to 0psi output to begin
  regulator.zero();
  
  //initiate serial connection
  Serial.begin(9600);
  
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
  int error;
  if (step_size > 0)
    error = go_up(step_size);
  else if(step_size < 0)
    error = go_down(step_size);
  else
    error = stay_put();

  if (error)
    error_handler(error);
}
