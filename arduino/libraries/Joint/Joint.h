/*
 * This class is a wrapper for the adafruit PWM servo driver library.
 * Joint's primary usage will be inside the LeArm class.
 * 
 * Author: Garrison Johnston -- 06/13/2020
 * Project: LeArm_ros_controller
 */


#ifndef JOINT_H
#define JOINT_H

// Includes
#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>


class Joint {
public:
	/*
	 * @brief Constructor
	 * @param ang_min The minimum angle for the servo
	 * @param ang_max The maximum angle for the servo
	 * @param pul_min The minimum pulse width for the servo in microseconds
	 * @param pul_max The maximum pulse width for the servo in microseconds
	 * @param home The home angle for the servo
	 * @param ser_num the servo number from 0-5.
	 * @param pwm_obj Adafruit_PWMServoDriver object. Needed to interact with the shield.
	 */
	Joint(double ang_min, double ang_max, double pul_min, double pul_max, double home, uint32_t ser_num, Adafruit_PWMServoDriver* pwm_obj);
	
	/*
	 * @brief default destructor 
	 */
	~Joint() = default;

	/*
	 * @brief Commands the joint to move to a desired angle
	 * @param angle Desired joint angle.  
	 */
	void setAngle(double angle);

	/* 
	 * @brief Returns the current angle of the servo in whatever units angle_min and angle_max are in.
	 * @return current joint angle
	 */
	double getAngle();

	/* 
	 * @brief sends the joint to the home configuration. 
	 * @details Because I cannot sense the angle of the servo, this needs to be done at startup. Warning: this will go fast, place robot near home config before calling! 
	 */
	void goHome();

private:
	const double angle_min;       // The minimum angle for the servo
	const double angle_max;       // The maximum angle for the servo
	const double pulse_min;       // The minimum pulse width for the servo in microseconds
	const double pulse_max;       // The maximum pulse width for the servo in microseconds
	const double angle_home;      // The home angle for the servo
	const uint32_t servo_num;     // The servo number 0-5. 0 = base yaw joint. 5 = gripper
	Adafruit_PWMServoDriver* pwm; // Object used to send commands to the servo
	double angle_current;     // Variable used to keep track of servo angle. Only needed because of my choice of servo shield does not allow for sensing the angle 
};

#endif // JOINT_H