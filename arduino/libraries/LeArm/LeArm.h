/*
 * This class is used to define an LeArm object. The LeArm object can be used to control the robot in jointspace.
 * 
 * Author: Garrison Johnston -- 06/14/2020
 * Project: LeArm_ros_controller
 */

#ifndef LEARM_H
#define LEARM_H

// Includes
#include <Joint.h>
#include <Adafruit_PWMServoDriver.h>


class LeArm {
public:
	/*
	 * @brief Constructor
	 */
	LeArm() = default;

	/*
	 * @brief default destructor 
	 */
	~LeArm() = default;

	/*
	 * @brief This function moves the robot to a desired pose using a quintic polynomial planner
	 * @param angles Pointer to an array of joint angles
	 * @param time_final Time it takes to execute trajectory
	 * @param dt Time step 
	 */
	void goToPose(double *angles, double time_final, double dt);

	/*
	 * @brief This function starts the robot and sends the robot home
	 */
	void start();

	/*
	 * @brief This function returns the current pose of the robot
	 * @return A pointer to an array of the current joint angles 
	 */
	double* getPose();

	/*
	 * @brief Sends the robot to its home configuration
	 */
	void goHome();

private:

	// array of Joint objects used to interact with the joints and define PWM and joint limit paramters 
	Joint joints[6] = { Joint(0, 180,  500, 2500, 90, 0, &pwm), // Joint 1
						Joint(0, 180,  500, 2500, 135, 1, &pwm), // Joint 2
						Joint(0, 180,  500, 2500, 90, 2, &pwm), // Joint 3
						Joint(0, 180,  500, 2500, 90, 3, &pwm), // Joint 4
						Joint(0, 180,  500, 2500, 90, 4, &pwm), // Joint 5
						Joint(0, 100, 1500, 2500,  0, 5, &pwm)  // Gripper
					};
	Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(); // Object used to interact with the servos

	
};


#endif // LEARM_H