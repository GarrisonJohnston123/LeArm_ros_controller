#include <Adafruit_PWMServoDriver.h>
#include <Joint.h>
#include <Wire.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
Joint gripper = Joint(0, 100, 1500, 2500, 0, 5, &pwm);
void setup(){
  pwm.begin();
  Serial.begin(9600);
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50);  // Analog servos run at ~50 Hz updates
  delay(10);
  gripper.goHome();
  delay(1000);
  }

void loop(){
  gripper.setAngle(10, 0.5, 0.01);
  delay(1000);
  gripper.setAngle(90, 0.5, 0.01);
  delay(1000);
  }
