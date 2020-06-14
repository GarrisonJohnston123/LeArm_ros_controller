#include <Adafruit_PWMServoDriver.h>
#include <LeArm.h>
#include <Wire.h>

LeArm robot = LeArm();
double desired_angles1[6] = {45, 45, 45, 45, 45, 50};
double desired_angles2[6] = {90, 135, 90, 90, 90, 0}; 

void setup(){
  //setup serial
  Serial.begin(9600);

  //start robot
  robot.start();
}

void loop(){
  robot.goToPose(desired_angles1, 1, 0.01);
  delay(1000);
  robot.goToPose(desired_angles2, 1, 0.01);
  delay(1000);
  //robot.goHome();
  }
