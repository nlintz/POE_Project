
#include <Servo.h>

int posSensorPin = A0;
int forceSensorPin = A1;
int solenoidPin = 2;

//not final value
const float angleMax = 90.0;
const float angleMin = 0.0;
Servo servo;

//whe the sensor is below this value, treat it as zero
float forceCutoff = 0.1

void setup(){
  servo.attach(3);  
}

//NEEDS TO BE UPDATED
enum ErrorCode{
	solenoid, angle, servo
};

int forceToStep(float force, int angle){
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
  
  return step_size
}

int desired_step(){
  /* 
   * Processes sensor data to return desired step_size
   */
        
  //get force value
  force = ForceSensor.getForce()
        
  //get angle value
  angle = AngleSensor.getAngle()
  
  // compute step
  step_size = forceToStep(force, angle)

  return step_size
}

void moveConverter(int step_size){

  // get current servo position
  current_pos = servo.read();
  
  // move the servo
  servo.write(current_pos + step_size);
  
  // delay so the servo has time to move
  delay(50);
}

ErrorCode go_down(step_size){
  /*
   * Control loop for opening (deflating)  the arm
   */
	
  ErrorCode error = angle;
  do{
    
    old_angle = angleSensor.getAngle();
    moveConverter(step_size);
		
    // if behaviour is not as expected, return non-zero error
    new_angle = angleSensor.getAngle();
    
    if (new_angle >= old_angle){
      error = angle;
      break;
    }
    step_size = desired_step();
  } while(step_size < 0);
  
  return error;
}

ErrorCode go_up(step_size){
  /*
   * Control loop for closing (inflating) the arm
   */
	
  error = 0
  do{
    old_angle = angleSensor.getAngle();
    moveConverter(step_size);
		
    // if behaviour is not as expected, return non-zero error
    new_angle = angleSensor.getAngle();
    if (new_angle <= old_angle){
      error = angle;
      break;
    }
    step_size = desired_step();
  } while(step_size > 0)
	
  return error
}

ErrorCode stay_put(step_size){
	/*
	 * Control loop for not moving the arm (no real control, just error detection)
	 */
	
	error = 0
	do{
		set muscle to reservoir
		desired_step
		
		// if behaviour is not as expected, return non-zero error
		calculate expected angle delta
		get actual angle delta
		if angle delta not expected?
			set proper error code
			break
	} while(want to go up?)
	
	return error
}

error(error_code){

}



void loop() {
  /* 
   * Main control loop.  Acts as a delegator to the three other control loops:
   * 	1 go up
   *	2 go down
   *	3 stay put
   */
	
  get desired step_size
	
  if (want to go up?)
    error = go_up(step_size)
  else if(want to go down?)
    error = go down(step_size)
  else
    error = stay_put(step_size)

  if error:
    error handler(error)
}
