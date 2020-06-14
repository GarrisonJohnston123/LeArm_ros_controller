/*
This class is used to define an LeArm object. The LeArm object can be used to control the robot in jointspace.
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

	void goToPose(double *angles, double time_final, double dt);

	void start();

	double* getPose();

	void goHome();

private:
	Joint joints[6] = { Joint(0, 180,  500, 2500, 90, 0, &pwm), // Joint 1
						Joint(0, 180,  500, 2500, 135, 1, &pwm), // Joint 2
						Joint(0, 180,  500, 2500, 90, 2, &pwm), // Joint 3
						Joint(0, 180,  500, 2500, 90, 3, &pwm), // Joint 4
						Joint(0, 180,  500, 2500, 90, 4, &pwm), // Joint 5
						Joint(0, 100, 1500, 2500,  0, 5, &pwm)  // Gripper
					};
	Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

	
};


#endif // LEARM_H