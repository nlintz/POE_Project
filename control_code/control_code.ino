#include <ForceSensor.h>
#include <Solenoid.h>
#include <AngleSensor.h>

#include <Servo.h>

const int angleSensorPin = A0;
const int forceSensorPin = A1;
const int solenoidPin = 2;

//not final value
const float angleMax = 90.0;
const float angleMin = 0.0;

// devices
Servo servo;
ForceSensor force_sensor (forceSensorPin);
Solenoid solenoid (solenoidPin);
AngleSensor angle_sensor (angleSensorPin);


//when the sensor is below this value, treat it as zero
const float forceCutoff = 0.1;


int forceToStep(float force, int angle){
  int step_size;
  if (abs(force) <= forceCutoff){
    step_size = 0;
  }
  else {
    // convert force voltage into servo step
    // sketch
    step_size = (int) 4*force;
  }
  
  // don't let it move past end-points
  if ((step_size > 0) && (angle >= angleMax)){
     step_size = 0;
  }
  if ((step_size < 0) && (angle <= angleMin)){
    step_size = 0;
  }
  
  return  -step_size;
}

int desired_step(){
  /* 
   * Processes sensor data to return desired step_size
   */
        
  //get force value
  float force;
  force = force_sensor.getForce();
        
  //get angle value
  int angle;
  angle = angle_sensor.getAngle();
  
  // compute step
  int step_size;
  step_size = forceToStep(force, angle);

  return step_size;
}

void moveConverter(int step_size){

  // get current servo position
  int current_pos;
  current_pos = servo.read();
  
  // move the servo
  servo.write(current_pos + step_size);
  
  // delay so the servo has time to move
  delay(50);
}

int go_down(int step_size){
  /*
   * Control loop for opening (deflating)  the arm
   */
	
  int error = 0;
  int old_angle, new_angle;
  
  do{
    
    old_angle = angle_sensor.getAngle();
    moveConverter(step_size);
		
    // if behaviour is not as expected, return non-zero error
    new_angle = angle_sensor.getAngle();
    
    if (new_angle >= old_angle){
      error = 1;
      break;
    }
    step_size = desired_step();
  } while(step_size > 0);
  
  return error;
}
//
int go_up(int step_size){
  /*
   * Control loop for closing (inflating) the arm
   */
	
  int error = 0;
  int old_angle, new_angle;
  do{
    old_angle = angle_sensor.getAngle();
    moveConverter(step_size);
		
    // if behaviour is not as expected, return non-zero error
    new_angle = angle_sensor.getAngle();
    if (new_angle <= old_angle){
      error = 1;
      break;
    }
    step_size = desired_step();
  } while(step_size < 0);
	
  return error;
}

int stay_put(){
  /*
   * Control loop for not moving the arm (no real control, just error detection)
   */
	
  int error = 0;
  int old_angle, new_angle, step_size;
  
  //tollerence in movement
  int tol = 1;
  do{
    old_angle = angle_sensor.getAngle();
    
    // wait a bit to make sure the arm isn't moving
    delay(50);

    // if behaviour is not as expected, return non-zero error
    new_angle = angle_sensor.getAngle();
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
  moveConverter(180 - servo.read());
  // wait until the thing is reset
  while(true)
    delay(50);
}


void setup(){
  servo.attach(3);
  force_sensor.calibrate();
  
  // set solenoid to resevoir
  solenoid.open();
  
  // set converter to 0psi output to begin
  moveConverter(180 - servo.read());
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
  if (step_size < 0)
    error = go_up(step_size);
  else if(step_size > 0)
    error = go_down(step_size);
  else
    error = stay_put();

  if (error)
    error_handler(error);
}
