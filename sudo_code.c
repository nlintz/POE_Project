
int posSensorPin= A0;
int solenoidPin= 2;  
Servo servo;

enum ErrorCode{
	solenoid, position, servo
};

float get_desired_velocity(){
	/*
	 * Processes sensor data to return desired velocity
	 */
	
	return velocity
}

float current_pressure(){
	/*
	 * Uses angle sensor to measure pressure in air muscle
	 */
	 
	 return pressure
}

void synchronize_converter() {
	
}

void loop() {
	/* 
	 * Main control loop.  Acts as a delegator to the three other control loops:
	 * 	1 go up
	 *	2 go down
	 *	3 stay put
	 */
	
	get desired velocity
	
	if (want to go up?)
		error = go_up(velocity)
	else if(want to go down?)
		error = go down(velocity)
	else
		error = stay_put(velocity)
	
	if error:
		error handler(error)
}

ErrorCode go_down(velocity){
	/*
	 * Control loop for opening (deflating)  the arm
	 */
	
	error = 0
	do{
		given velocity, calculate pressure delta
		
		set muscle to exhaust
		
		

		
		synchronize converter
		get_desired_velocity
		
		// if behaviour is not as expected, return non-zero error
		calculate expected position delta
		get actual position delta
		if position delta not expected?
			set proper error code
			break
	} while(want to go down?)
	
	set muscle to reservoir
	return error
}

ErrorCode go_up(velocity){
	/*
	 * Control loop for closing (inflating) the arm
	 */
	
	error = 0
	do{
		set muscle to reservoir
		move converter(velocity)
		get_desired_velocity
		
		// if behaviour is not as expected, return non-zero error
		calculate expected position delta
		get actual position delta
		if position delta not expected?
			set proper error code
			break
	} while(want to go up?)
	
	return error
}

ErrorCode stay_put(velocity){
	/*
	 * Control loop for not moving the arm (no real control, just error detection)
	 */
	
	error = 0
	do{
		set muscle to reservoir
		get_desired_velocity
		
		// if behaviour is not as expected, return non-zero error
		calculate expected position delta
		get actual position delta
		if position delta not expected?
			set proper error code
			break
	} while(want to go up?)
	
	return error
}

error(error_code){

}