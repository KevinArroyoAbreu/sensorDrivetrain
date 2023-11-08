#include "vex.h"
#include "robot-config.h"
#include <cmath>

using namespace vex;

// A global instance of competition
extern competition Competition;

// define your global instances of motors and other devices here
extern motor_group leftDrive;
extern motor_group rightDrive;
extern motor_group cataPuncherMotors;

extern drivetrain robotDrive;

void pre_auton(void);

void baseStop(void);

void Forward(float distance, int speed);

void Reverse(float distance, int speed);

void TurnLeft(float angle, int speed);

void TurnRight(float angle, int speed);

void routine1();
// Main will set up the competition functions and callbacks.
//
int main();