#include "Joint.h"

Joint::Joint(double ang_min, double ang_max, double pul_min, double pul_max, double home, uint32_t ser_num, Adafruit_PWMServoDriver* pwm_obj)
	: angle_min(ang_min)
	, angle_max(ang_max)
	, pulse_min(pul_min)
	, pulse_max(pul_max)
	, angle_home(home)
	, servo_num(ser_num)
	, pwm(pwm_obj)
	{}

void Joint::setAngle(double angle, double time_final, double dt){
	
	// keep angle between minimum and maximum
	angle = constrain(angle, angle_min, angle_max);

	// setup variables
	double time  = 0; // trajectory time
	uint32_t pulse_width; // current pulse width 
	double q;             // current joint angle
	double eta;           // normalized time 
	double q_0 = angle_current; // intial joint angle

	while (time <= time_final){
		eta = time/time_final; // Normalized time 
		
		//quintic plan
		q = q_0 + (angle-q_0)*(10*pow(eta, 3)-15*pow(eta, 4)+6*pow(eta, 5));

		// convert angle to pulsewidth
		pulse_width  = map(q, angle_min, angle_max, pulse_min, pulse_max);

		//send command to motor
		pwm->writeMicroseconds(servo_num, pulse_width);

		//wait dt seconds
		delay(dt*1000);

		// increment time
		time += dt;
	}
	// set current angle
	angle_current = angle;

}

double Joint::getAngle(){
	return angle_current;
}

void Joint::goHome(){
	// convert home position to pulse width
	double pulse_width  = map(angle_home, angle_min, angle_max, pulse_min, pulse_max);

	// write command to servos
	pwm->writeMicroseconds(servo_num, pulse_width);

	// set current angle
	angle_current = angle_home;
}
