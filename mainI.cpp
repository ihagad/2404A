#include "main.h"

/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


//1 for defense
//2 for offense
//3 skills

//red side - offense 
//blue side - defense(match loading)

// Chassis constructor
Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  {-10, -9, -8}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  ,{1, 2, 3}

  // IMU Port
  ,20

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  //    (or tracking wheel diameter)
  ,3.25

  // Cartridge RPM
  //   (or tick per rotation if using tracking wheels)
  ,600

  // External Gear Ratio (MUST BE DECIMAL)
  //    (or gear ratio of tracking wheel)
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
  ,0.6

  // Uncomment if using tracking wheels
  /*
  // Left Tracking Wheel Ports (negative port will reverse it!)
  // ,{1, 2} // 3 wire encoder
  // ,8 // Rotation sensor

  // Right Tracking Wheel Ports (negative port will reverse it!)
  // ,{-3, -4} // 3 wire encoder
  // ,-9 // Rotation sensor
  */

  // Uncomment if tracking wheels are plugged into a 3 wire expander
  // 3 Wire Port Expander Smart Port
  // ,1
);



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // Print our branding over your terminal :D
  ez::print_ez_template();
  
  pros::delay(500); // Stop the user from doing anything while legacy ports configure.

  // Configure your chassis controls
  chassis.toggle_modify_curve_with_controller(true); // Enables modifying the controller curve with buttons on the joysticks
  chassis.set_active_brake(0.1); // Sets the active brake kP. We recommend 0.1.
  chassis.set_curve_default(0, 0); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  default_constants(); // Set the drive to your own constants from autons.cpp!
  exit_condition_defaults(); // Set the exit conditions to your own constants from autons.cpp!

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.set_left_curve_buttons (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used. 
  // chassis.set_right_curve_buttons(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.add_autons({
    //Auton("Testing",singleMotorTest),
    //Auton("hahah", trial),
    //Auton("Insert Faraz here", defense1)
    Auton("Karthik", sixTriball),
  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
}



/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}



/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}


/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency.

  ez::as::auton_selector.call_selected_auton(); // Calls selected auton from autonomous selector.
}



/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  // This is preference to what you like to drive on.
  //chassis.set_drive_brake(MOTOR_BRAKE_COAST);
  pros::Motor intake (7);
  pros::Motor shooting (5);
  //pros::ADIDigitalIn limit (20);
  pros::Controller controller (CONTROLLER_MASTER);
  pros::ADIDigitalOut frontFlap ('A');
  pros::ADIDigitalOut backR ('B');
  pros::ADIDigitalOut backL ('D');
  pros::ADIDigitalOut PTO ('C');
  pros::ADIDigitalOut hang ('G');

  bool pressed = false;
  int num = 1;

  int time = pros::millis();

  while (true) {

    // chassis.tank(); // Tank control
    chassis.arcade_standard(ez::SPLIT); // Standard split arcade
    // chassis.arcade_standard(ez::SINGLE); // Standard single arcade
    // chassis.arcade_flipped(ez::SPLIT); // Flipped split arcade
    // chassis.arcade_flipped(ez::SINGLE); // Flipped single arcade
    // Put more user control code here!
    // . . .
    //INTAKE
    chassis.set_max_speed(100);
    if (controller.get_digital(DIGITAL_L1)){
      intake.move(127); //outtake
    } 
    if (controller.get_digital(DIGITAL_L2)){
      intake.move(-127); //intake
    }
    if(controller. get_digital(DIGITAL_B)){
      intake.move(0);
    }
    //SHOOTING
    if (controller.get_digital(DIGITAL_R2)){
      shooting.move(-100);
    } else if (controller.get_digital(DIGITAL_R1)) {
      shooting.move(0);
    }
  
    //Front flaps
    if(controller.get_digital(DIGITAL_UP)){
      frontFlap.set_value(true);
    }
    if(controller.get_digital(DIGITAL_DOWN)){
      frontFlap.set_value(false);
    }

    //Back flaps
    if(controller.get_digital(DIGITAL_RIGHT)){
      backR.set_value(true);
      backL.set_value(true);
    }
    if(controller.get_digital(DIGITAL_LEFT)){
      backR.set_value(false);
      backL.set_value(false);
    }

    //PTO
    if(controller.get_digital(DIGITAL_X)){
      PTO.set_value(true);
    }

    //HANG
    if(controller.get_digital(DIGITAL_Y)){
      hang.set_value(true);
    }
    if(controller.get_digital(DIGITAL_A)){
      hang.set_value(false);
    }

    pros::delay(ez::util::DELAY_TIME);
  }
}
