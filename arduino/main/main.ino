#include <Adafruit_PWMServoDriver.h>
#include <LeArm.h>
#include <Wire.h>

LeArm robot = LeArm();
double desired_angles1[6] = {0, 45, 45, 45, 90, 50};
double desired_angles2[6] = {0, 135, 90, 90, 90, 0}; 

void setup(){
  robot.start();
}

void loop(){
  robot.goToPose(desired_angles1, 2, 0.01);
  delay(1000);
  robot.goToPose(desired_angles2, 2, 0.01);
  delay(1000);
  //robot.goHome();
  }
