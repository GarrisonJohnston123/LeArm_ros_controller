#include <LeArm.h>

void LeArm::goToPose(double *angles, double time_final, double dt){

	double time  = 0;        // trajectory time
	uint32_t pulse_width[6]; // current pulse width 
	double eta;              // normalized time 
	double* q_0 = getPose();  // intial joint angles
	double q;                // current joint angles

	while (time <= time_final){
		
		eta = time/time_final; // Normalized time 
		
		for (uint32_t i = 0; i < 6; ++i){ // loop through joints
			
			//quintic plan
			q = q_0[i] + (angles[i]-q_0[i])*(10*pow(eta, 3)-15*pow(eta, 4)+6*pow(eta, 5));

			//set joint angle
			joints[i].setAngle(q);
		}

		//wait dt seconds
		delay(dt*1000);

		// increment time
		time += dt;
	}
	
}

void LeArm::start(){
	// start pwm 
	pwm.begin();
	pwm.setOscillatorFrequency(27000000);
	pwm.setPWMFreq(50);  // Analog servos run at ~50 Hz updates
	
	// wait 10 ms
	delay(10);

	goHome();

	delay(1000);
}

double* LeArm::getPose(){
	
	double *pose = new double[6];

	for (uint32_t i = 0; i < 6; ++i){
		pose[i] = joints[i].getAngle();
	}

	return pose;
}

void LeArm::goHome(){
	for (Joint q : joints){
		q.goHome();
	}
}