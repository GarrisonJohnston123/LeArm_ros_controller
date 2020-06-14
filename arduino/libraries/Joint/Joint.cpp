/*
 * This class is a wrapper for the adafruit PWM servo driver library. It also extends the functionality to include quintic polynomial planning.
 * Joint's primary usage will be inside the LeArm class.
 * 
 * Author: Garrison Johnston -- 06/13/2020
 * Project: LeArm_ros_controller
 */

#include "Joint.h"

Joint::Joint(double ang_min, double ang_max, double pul_min, double pul_max, double home, uint32_t ser_num, Adafruit_PWMServoDriver* pwm_obj)
	: angle_min(ang_min)
	, angle_max(ang_max)
	, pulse_min(pul_min)
	, pulse_max(pul_max)
	, angle_home(home)
	, servo_num(ser_num)
	, pwm(pwm_obj)
	{
		angle_current = angle_home; // we cant sense the angle, so we have to assume it has been homed.
	}

void Joint::setAngle(double angle){
	
	// keep angle between minimum and maximum
	angle = constrain(angle, angle_min, angle_max);

	// convert angle to pulse width
	double pulse_width = map(angle, angle_min, angle_max, pulse_min, pulse_max);

	// send command to motor
	pwm->writeMicroseconds(servo_num, pulse_width);

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


