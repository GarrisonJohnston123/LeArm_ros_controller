/*
 * This class is a wrapper for the adafruit PWM servo driver library. It also extends the functionality to include quintic polynomial planning.
 * Its primary usage will be inside the LeArm class.
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
	 * @param ser_num 
	 */
	Joint(double ang_min, double ang_max, double pul_min, double pul_max, double home, uint32_t ser_num, Adafruit_PWMServoDriver* pwm_obj);
	
	/*
	 * @brief default destructor 
	 */
	~Joint() = default;


	/*
	 * @brief Commands the joint to move to a desired angle using a quintic polynomial
	 * @param angle Desired joint angle
	 * @param time_final Duration of the movement in seconds
	 * @param dt step size in seconds.  
	 */
	void setAngle(double angle, double time_final, double dt);

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
	double angle_current = 0;     // Variable used to keep track of servo angle. Only needed because of my choice of servo shield does not allow for sensing the angle 
};

#endif // JOINT_H