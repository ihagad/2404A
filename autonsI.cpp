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


pros::Motor intake (19, true);
pros::Motor shooting (9, true);
pros::ADIDigitalOut piston1 ('A');
pros::ADIDigitalOut piston2 ('B');

///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  // chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  // chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  // chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  // chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.75, 0.0, 1, 10);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.75, 0.0, 1, 10);
  chassis.set_pid_constants(&chassis.turnPID, 2.9, 0.5, 2, 10);
  chassis.set_pid_constants(&chassis.swingPID, 1.75, 0, 1, 10);
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

void offence1(){
  // //put in preload
  // chassis.set_turn_pid(45, TURN_SPEED);
  // chassis.set_drive_pid(30, DRIVE_SPEED, true);

  // //take out corner triball
  // chassis.set_turn_pid(180);
  // piston1.set_value(true);
  // chassis.set_drive_pid(-10, DRIVE_SPEED, true);
  // chassis.set_turn_pid();
}

void trial(){
  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
}

void defense1(){
  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.set_drive_pid(-48, DRIVE_SPEED, true);
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
}
