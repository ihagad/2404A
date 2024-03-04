#include "lemlib/api.hpp"
#include "main.h"

// controller
    pros::Controller controller(pros::E_CONTROLLER_MASTER);
    pros::Motor intake (13, true);
    pros::Motor shooting (11, true);
    // pros::ADIDigitalIn limit (20);
    //pros::Controller controller (CONTROLLER_MASTER);
    pros::ADIDigitalOut pistonL ('C');
    pros::ADIDigitalOut pistonR ('B');
    pros::ADIDigitalOut frontFlap ('A');

// drive motors
    pros::Motor lF(-8, pros::E_MOTOR_GEARSET_06); // left front motor. port 12, reversed
    pros::Motor lM(-9, pros::E_MOTOR_GEARSET_06); // left middle motor. port 11, reversed
    pros::Motor lB(-10, pros::E_MOTOR_GEARSET_06); // left back motor. port 1, reversed
    pros::Motor rF(3, pros::E_MOTOR_GEARSET_06); // right front motor. port 2
    pros::Motor rM(2, pros::E_MOTOR_GEARSET_06); // right middle motor. port 11
    pros::Motor rB(1, pros::E_MOTOR_GEARSET_06); // right back motor. port 13

// motor groups
    pros::MotorGroup leftMotors({lF, lM, lB}); // left motor group
    pros::MotorGroup rightMotors({rF, rM, rB}); // right motor group

// Inertial Sensor on port 20
    pros::Imu imu(6);

// tracking wheels
// horizontal tracking wheel encoder. Rotation sensor, port 15, reversed (negative signs don't work due to a pros bug)
//pros::Rotation horizontalEnc(15, true);
// horizontal tracking wheel. 2.75" diameter, 3.7" offset, back of the robot (negative)
//lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_275, -3.7);

// drivetrain settings
lemlib::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              11.25, // 10 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 3.25" omnis
                              360, // drivetrain rpm is 360
                              8 // chase power is 2. If we had traction wheels, it would have been 8
);

// lateral motion controller
lemlib::ControllerSettings linearController(20, // proportional gain (kP)
                                            0, // integral gain (kI)
                                            19, // derivative gain (kD)
                                            3, // anti windup
                                            1, // small error range, in inches
                                            100, // small error range timeout, in milliseconds
                                            3, // large error range, in inches
                                            500, // large error range timeout, in milliseconds
                                            20 // maximum acceleration (slew)
);

// angular motion controller
lemlib::ControllerSettings angularController(2, // proportional gain (kP)
                                             0, // integral gain (kI)
                                             10, // derivative gain (kD)
                                             3, // anti windup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);

// sensors for odometry
// note that in this example we use internal motor encoders (IMEs), so we don't pass vertical tracking wheels
lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// create the chassis
lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors
    chassis.setPose(0, 0, 0);


    // the default rate is 50. however, if you need to change the rate, you
    // can do the following.
    // lemlib::bufferedStdout().setRate(...);
    // If you use bluetooth or a wired connection, you will want to have a rate of 10ms

    // for more information on how the formatting for the loggers
    // works, refer to the fmtlib docs

    // thread to for brain screen and position logging
    pros::Task screenTask([&]() {
        lemlib::Pose pose(0, 0, 0);
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // log position telemetry
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
            // delay to save resources
            pros::delay(50);
        }
    });
}

/**
 * Runs while the robot is disabled
 */
void disabled() {}

/**
 * runs after initialize if the robot is connected to field control
 */
void competition_initialize() {}

// get a path used for pure pursuit
// this needs to be put outside a function
ASSET(trial1_txt); // '.' replaced with "_" to make c++ happy
/**
 * Runs during auto
 *
 * This is an example autonomous routine which demonstrates a lot of the features LemLib has to offer
 */
void autonomous() {
    chassis.follow(trial1_txt, 2000, 15);
}

/**
 * Runs in driver control
 */
void opcontrol() {
    // controller
    // loop to continuously update motors

     int time = pros::millis();

    while (true) {
        // get joystick positions
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        // move the chassis with curvature drive

        chassis.arcade(leftY, rightX);

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
        shooting.move(100);
        } else if (controller.get_digital(DIGITAL_R1)) {
        shooting.move(0);
        }

        //FLAPPER
        if(controller.get_digital(DIGITAL_UP)){
        frontFlap.set_value(true);
        }
        if(controller.get_digital(DIGITAL_DOWN)){
        frontFlap.set_value(false);
        }

        //BACK PISTON
        if(controller.get_digital(DIGITAL_RIGHT)){
        pistonL.set_value(true);
        pistonR.set_value(true);
        }
        if(controller.get_digital(DIGITAL_LEFT)){
        pistonL.set_value(false);
        pistonR.set_value(false);
        }

        // delay to save resources
        pros::delay(10);
    }
}
