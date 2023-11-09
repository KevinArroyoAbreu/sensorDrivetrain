/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       karro                                                     */
/*    Created:      11/7/2023, 9:19:37 AM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       josue                                                     */
/*    Created:      10/6/2023, 6:08:58 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "main.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
motor_group leftDrive(LeftFront, LeftBack);
motor_group rightDrive(RightFront, RightBack);

drivetrain robotDrive(leftDrive, rightDrive, 12.56, 275, 230, mm, 36*84 /*wheel travel = o x pi, track width, wheel base*/);

void pre_auton(void){
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

void baseStop(void){
  robotDrive.setStopping(brake);
  robotDrive.stop();
}

void Forward(float distance, int speed) {
  robotDrive.setDriveVelocity(speed, percent);
  robotDrive.driveFor(reverse, distance, inches);
  baseStop();
}

void Reverse(float distance, int speed) {
  robotDrive.setDriveVelocity(speed, percent);
  robotDrive.driveFor(forward, distance, inches);
  baseStop();
}

void ReverseUnlimited(int speed) {
  robotDrive.setDriveVelocity(speed, percent);
  robotDrive.drive(forward);
}

void TurnLeft(float angle, int speed) {
  robotDrive.setTurnVelocity(speed, percent);
  robotDrive.turnFor(right, angle, degrees);
}

void TurnRight(float angle, int speed) {
  robotDrive.setTurnVelocity(speed, percent);
  robotDrive.turnFor(left, angle, degrees);
}


void routine1(){
  
  Forward(20, 100);
  TurnLeft(32,100);
  vex::wait(500, msec);
  
}

void readValues(){
  while(1){
   Vision.takeSnapshot(BLUE_BALL);

    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Width:");
    Brain.Screen.print(Vision.objects[0].width);

    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print("Height:");
    Brain.Screen.print(Vision.objects[0].height);

    Brain.Screen.setCursor(3, 1);
    Brain.Screen.print("centerX:");
    Brain.Screen.print(Vision.objects[0].centerX);

    vex::wait(20, msec);
  }
  
}
void followObject(){
  //Vision.setBrightness(100);
   Vision.takeSnapshot(BLUE_BALL);
   // int largest = Vision.largestObject(vex::vision::object::centerX);
   // Brain.Screen.print("Hola");
   //Brain.Screen.clearLine();
   //int Vision_objectIndex = 0;
   //int cX = Vision.objects[Vision_objectIndex].centerX; //0 - 315
  //Brain.Screen.print(cX);
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print(Vision.objects[0].width);
  ////////////////////////
   int targetWidth = 120;
   int driveV = 40;
   int driveAlignV = 60;
  //height 2-212
  //width 2-316
  while(Vision.objects[0].width < targetWidth){
    Vision.takeSnapshot(BLUE_BALL);
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print(Vision.objects[0].width);

    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print(Vision.objects[0].centerX);

    if(Vision.objects[0].centerX < 158){//object to the left
      //Drive-turnLeftwards
      leftDrive.setVelocity(driveV, pct);
      rightDrive.setVelocity(driveAlignV, pct);
      leftDrive.spin(fwd);
      rightDrive.spin(fwd);

    }
    else if(Vision.objects[0].centerX > 158){//object to the right
      //Drive-turnRighwards
      leftDrive.setVelocity(driveAlignV, pct);
      rightDrive.setVelocity(driveV, pct);
      leftDrive.spin(fwd);
      rightDrive.spin(fwd);
    }
    else{
      //driveFwd
      robotDrive.setDriveVelocity(driveV, pct);
      robotDrive.drive(fwd);
    }
    vex::wait(20, msec);
   } 
   robotDrive.stop();
   /////////////////////////////
  vex::wait(20, msec);
}


void autonomous(void){
  // ..........................................................................
  routine1();
  //  ..........................................................................
}



void usercontrol(void){
  // User control code here, inside the loop
  while (1){
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.
    /*RightBack.spin(directionType::fwd, +Controller1.Axis4.position(percentUnits::pct) - Controller1.Axis3.position(percentUnits::pct), velocityUnits::pct);
    RightFront.spin(directionType::fwd, +Controller1.Axis4.position(percentUnits::pct) - Controller1.Axis3.position(percentUnits::pct), velocityUnits::pct);
    LeftBack.spin(directionType::fwd, -Controller1.Axis4.position(percentUnits::pct) - Controller1.Axis3.position(percentUnits::pct), velocityUnits::pct);
    LeftFront.spin(directionType::fwd, -Controller1.Axis4.position(percentUnits::pct) - Controller1.Axis3.position(percentUnits::pct), velocityUnits::pct);
    */
    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
  



   // Brain.Screen.print("sensorDrive");
    vex::wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main()
{
  ////////////////////////
  ////////////////////////
  //                    //
  //                    //
  //                    //
  //                    //
  ////////////////////////
  ////////////////////////
  //0                    315

  while(1){
  //select function to run:
  //followObject();
  readValues();
  vex::wait(20, msec);
  }
  //////////////////////////////////////////////////////////////////////////////////////
  
    //Brain.Screen.print("%d", largest);

  // Set up callbacks for autonomous and driver control periods.
 /* Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton(); */

  // Prevent main from exiting with an infinite loop.
  while (true){
    vex::wait(100, msec);
  }
}