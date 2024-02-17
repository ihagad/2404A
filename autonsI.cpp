#include "main.h"


/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;


  pros::Motor intake (20);
  pros::Motor shooting (19);
  //pros::ADIDigitalIn limit (20);
  pros::ADIDigitalOut frontFlaps ('E');
  pros::ADIDigitalOut backFlapsR ('B');
  pros::ADIDigitalOut backFlapsL ('C');
  pros::ADIDigitalOut hangPiston ('A');

///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);

  // chassis.set_pid_constants(&chassis.forward_drivePID, 0.75, 0.0, 1, 10);
  // chassis.set_pid_constants(&chassis.backward_drivePID, 0.75, 0.0, 1, 10);
  // chassis.set_pid_constants(&chassis.turnPID, 2.9, 0.5, 2, 10);
  // chassis.set_pid_constants(&chassis.swingPID, 1.75, 0, 1, 10);
}

void one_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void two_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void exit_condition_defaults() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}


void singleMotorTest(){
  
  //forward
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  //backward
  chassis.set_drive_pid(-24, TURN_SPEED, true);
  chassis.wait_drive();

  //right
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  //left
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();

  //intake
  intake.move_velocity(600);
  pros::delay(8000);
  intake.move_velocity(0);
  pros::delay(8000);

  //outake
  intake.move_velocity(-600);
  pros::delay(8000);
  intake.move_velocity(0);
  pros::delay(8000);

  //shooting
  shooting.move_velocity(-600);
  pros::delay(8000);
  shooting.move_velocity(0);
}

void defense1(){
  // //put in preload
  chassis.set_turn_pid(-30, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-100, DRIVE_SPEED, true);
  chassis.wait_drive();
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(37, 60, true);
  chassis.wait_drive();
  pros::delay(2000);
  //take out corner triball
  chassis.set_turn_pid(-42, TURN_SPEED);
  chassis.wait_drive();
  //pistonL.set_value(true);
  //pistonR.set_value(true);
  chassis.wait_drive();
  chassis.set_drive_pid(40, DRIVE_SPEED, true);
  chassis.wait_drive();
  chassis.set_turn_pid(-85, TURN_SPEED);
  chassis.wait_drive();
  intake.move(-127);
  chassis.set_drive_pid(124, DRIVE_SPEED, false);
  pros::delay(500);
  //pistonL.set_value(false);
  chassis.wait_drive();
  
}

void offence1(){

  chassis.set_drive_pid(-120, DRIVE_SPEED, true);

  // chassis.set_turn_pid(30, TURN_SPEED);
  // chassis.wait_drive();
  // chassis.set_drive_pid(-120, DRIVE_SPEED, true);
  // chassis.wait_drive();
  // chassis.set_turn_pid(32, TURN_SPEED);
  // chassis.wait_drive();
  // chassis.set_drive_pid(50, DRIVE_SPEED, true);
  // chassis.wait_drive();

  // chassis.set_drive_pid(-60, DRIVE_SPEED, true);
  // chassis.wait_drive();
}

void skills(){
  chassis.set_turn_pid(-30, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-95, DRIVE_SPEED+17, true);
  chassis.wait_drive();
  chassis.set_drive_pid(50, DRIVE_SPEED+10, true);
  chassis.wait_drive();
  chassis.set_turn_pid(73, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(30, DRIVE_SPEED+10, true);
  pros::delay(300);
  //change 
  shooting.move(-127);
  pros::delay(27000);
  shooting.move(0);

  chassis.set_turn_pid(135, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-55, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-240, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(215, TURN_SPEED);
  chassis.wait_drive();
  //pistonL.set_value(true);
  chassis.set_drive_pid(80, DRIVE_SPEED, true);
  chassis.wait_drive();
  //pistonL.set_value(false);
  chassis.set_drive_pid(-35, 127);
  chassis.wait_drive();
  chassis.set_turn_pid(25, 127);
  chassis.wait_drive();
  chassis.set_drive_pid(-60, 127);
  chassis.wait_drive();
  chassis.set_drive_pid(55, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(-65, 127); //-75, 127
  chassis.wait_drive();
  chassis.set_drive_pid(-130, 127); 
  chassis.wait_drive();
  chassis.set_turn_pid(-135, 127);
  chassis.wait_drive();
  //pistonR.set_value(true);
  //pistonL.set_value(true);

  chassis.set_drive_pid(100, 127);
  chassis.wait_drive();
  //pistonL.set_value(false);
  //pistonR.set_value(false);
  chassis.set_drive_pid(-100, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(180,127);
  chassis.wait_drive();
  chassis.set_drive_pid(70,127);
  chassis.wait_drive();
  chassis.set_turn_pid(270,127);
  chassis.wait_drive();

  //pistonL.set_value(true);
  //pistonR.set_value(true); 
  chassis.set_drive_pid(100,127);
  chassis.wait_drive();
  // pistonL.set_value(false);
  // pistonR.set_value(false); 
  chassis.set_drive_pid(-100,127);
  chassis.wait_drive();
  // pistonL.set_value(true);
  // pistonR.set_value(true); 
  chassis.set_drive_pid(100,127);
  chassis.wait_drive();
  // pistonL.set_value(false);
  // pistonR.set_value(false); 
  chassis.set_drive_pid(-100,127);
  chassis.wait_drive();

  chassis.set_turn_pid(-100, 127);
  chassis.wait_drive();
}

void skills2(){
  chassis.set_turn_pid(-30, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-95, DRIVE_SPEED+17, true);
  chassis.wait_drive();
  chassis.set_drive_pid(50, DRIVE_SPEED+10, true);
  chassis.wait_drive();
  chassis.set_turn_pid(71, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(30, DRIVE_SPEED+10, true);
  pros::delay(300);
  //change 
  shooting.move(-127);
  pros::delay(27000);
  shooting.move(0);

  chassis.set_turn_pid(135, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-55, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-240, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(-155, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(40, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(-70, 127); //-75, 127
  chassis.wait_drive();
  chassis.set_drive_pid(-130, 127); 
  chassis.wait_drive();
  chassis.set_turn_pid(-135, 127);
  chassis.wait_drive();
  // pistonR.set_value(true);
  // pistonL.set_value(true);

  chassis.set_drive_pid(100, 127);
  chassis.wait_drive();
  // pistonL.set_value(false);
  // pistonR.set_value(false);
  chassis.set_drive_pid(-100, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(-180,127);
  chassis.wait_drive();
  chassis.set_drive_pid(90,127);
  chassis.wait_drive();
  chassis.set_turn_pid(-90,127);
  chassis.wait_drive();

  // pistonL.set_value(true);
  // pistonR.set_value(true); 
  chassis.set_drive_pid(100,127);
  chassis.wait_drive();
  // pistonL.set_value(false);
  // pistonR.set_value(false); 
  chassis.set_drive_pid(-100,127);
  chassis.wait_drive();
  // pistonL.set_value(true);
  // pistonR.set_value(true); 
  chassis.set_drive_pid(100,127);
  chassis.wait_drive();
  // pistonL.set_value(false);
  // pistonR.set_value(false); 
  chassis.set_drive_pid(-100,127);
  chassis.wait_drive();

  chassis.set_turn_pid(-180,127);
  chassis.wait_drive();
  chassis.set_drive_pid(45,127);
  chassis.wait_drive();
  chassis.set_turn_pid(-60,127);
  chassis.wait_drive();

  // pistonL.set_value(true);
  // pistonR.set_value(true); 
  chassis.set_drive_pid(130,127);
  chassis.wait_drive();
  // pistonL.set_value(false);
  // pistonR.set_value(false); 
  chassis.set_drive_pid(-130,127);
  chassis.wait_drive();
  // pistonL.set_value(true);
  // pistonR.set_value(true); 
  chassis.set_drive_pid(130,127);
  chassis.wait_drive();
  // pistonL.set_value(false);
  // pistonR.set_value(false); 
  chassis.set_drive_pid(-130,127);
  chassis.wait_drive();
}

void sixBallElevation(){
  intake.move(127);
  chassis.set_drive_pid(13, 127);
  chassis.wait_drive();
  chassis.set_drive_pid(-85, 127);
  chassis.wait_drive();
  chassis.set_turn_pid(135, 127);
  chassis.wait_drive();
  // pistonL.set_value(true);
  chassis.set_drive_pid(65, 100);
  chassis.wait_drive();
  chassis.set_turn_pid(105, 127);
  chassis.wait_drive();
  intake.move(-127);
  pros::delay(200);
  chassis.set_drive_pid(55, 110);
  chassis.wait_drive();
  // pistonL.set_value(false);
  chassis.set_drive_pid(-45, 127);
  chassis.wait_drive();
  chassis.set_drive_pid(55, 127);
  chassis.wait_drive();
  chassis.set_drive_pid(-50, 127);
  chassis.wait_drive();
  chassis.set_turn_pid(43, 127);
  chassis.wait_drive();
  intake.move(127);
  chassis.set_drive_pid(167, 127);
  chassis.wait_drive();
  //chassis.set_drive_pid(17, 90);
  //chassis.wait_drive();
  chassis.set_turn_pid(180, 110);
  chassis.wait_drive();
  // pistonR.set_value(true);
  intake.move(-127);
  chassis.set_drive_pid(100, 110);
  chassis.wait_drive();

}
