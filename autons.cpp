
#include "vex.h"

/**
 * Resets the constants for auton movement.
 * Modify these to change the default behavior of functions like
 * drive_distance(). For explanations of the difference between
 * drive, heading, turning, and swinging, as well as the PID and
 * exit conditions, check the docs.
 */

void default_constants(){
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);

  // Each exit condition set is in the form of (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.set_turn_exit_conditions(1, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);
}

/**
 * Sets constants to be more effective for odom movements.
 * For functions like drive_to_point(), it's often better to have
 * a slower max_voltage and greater settle_error than you would otherwise.
 */

void odom_constants(){
  default_constants();
  chassis.heading_max_voltage = 10;
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
  chassis.boomerang_lead = .5;
  chassis.drive_min_voltage = 0;
}

/**
 * The expected behavior is to return to the start position.
 */

void drive_test(){
  chassis.drive_distance(6);
  chassis.drive_distance(12);
  chassis.drive_distance(18);
  chassis.drive_distance(-36);
}

/**
 * The expected behavior is to return to the start angle, after making a complete turn.
 */

void turn_test(){
  chassis.turn_to_angle(5);
  chassis.turn_to_angle(30);
  chassis.turn_to_angle(90);
  chassis.turn_to_angle(225);
  chassis.turn_to_angle(0);
}

/**
 * Should swing in a fun S shape.
 */

void swing_test(){
  chassis.left_swing_to_angle(90);
  chassis.right_swing_to_angle(0);
}

/**
 * A little of this, a little of that; it should end roughly where it started.
 */

void full_test(){
  chassis.drive_distance(24);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(-36);
  chassis.right_swing_to_angle(-90);
  chassis.drive_distance(24);
  chassis.turn_to_angle(0);
}

/**
 * Doesn't drive the robot, but just prints coordinates to the Brain screen 
 * so you can check if they are accurate to life. Push the robot around and
 * see if the coordinates increase like you'd expect.
 */

void odom_test(){
  chassis.set_coordinates(0, 0, 0);
  while(1){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(5,20, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(5,40, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(5,60, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(5,80, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(5,100, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    task::sleep(20);
  }
}

/**
 * Should end in the same place it began, but the second movement
 * will be curved while the first is straight.
 */

void tank_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.turn_to_point(24, 24);
  chassis.drive_to_point(24,24);
  chassis.drive_to_point(0,0);
  chassis.turn_to_angle(0);
}

/**
 * Drives in a square while making a full turn in the process. Should
 * end where it started.
 */

void holonomic_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.holonomic_drive_to_pose(0, 18, 90);
  chassis.holonomic_drive_to_pose(18, 0, 180);
  chassis.holonomic_drive_to_pose(0, 18, 270);
  chassis.holonomic_drive_to_pose(0, 0, 0);
}

void blue_right() {
  IntakeTop.setVelocity(100, percent);
  IntakeBottom.setVelocity(100, percent);
  IntakeMiddle.setVelocity(100, percent);
  BallStop.set(false);
  WheelPiston.set(true);
  //drive_test();
  chassis.drive_distance(30);
  wait(500, msec);
  //turn in the direction of the goal
  chassis.turn_to_angle(90);
  wait(500, msec);
  Scraper1.set(true);
  Scraper2.set(true);
  wait(500, msec);
  IntakeBottom.spin(reverse);
  IntakeMiddle.spin(forward);
  chassis.drive_distance(13.75);
  
  wait(2000, msec); //this is how long is spins at the loader
  Scraper1.set(false);
  Scraper2.set(false);
  IntakeBottom.stop();
  IntakeMiddle.stop();
    //run intake
  chassis.drive_distance(-13);

  // IntakeTop.stop();
  chassis.turn_to_angle(-93);
  chassis.drive_distance(17.25);
  //run intake
  IntakeBottom.spin(forward);
  IntakeMiddle.spin(reverse);
  IntakeTop.spin(reverse);
  wait(150, msec);
  IntakeBottom.spin(reverse);
  IntakeMiddle.spin(forward);
  IntakeTop.spin(forward);
  wait(3000, msec);

}

void blue_left(){
  IntakeTop.setVelocity(100, percent);
  IntakeBottom.setVelocity(100, percent);
  IntakeMiddle.setVelocity(100, percent);
  WheelPiston.set(true);
  BallStop.set(false);
  //drive_test();
  chassis.drive_distance(30);
  wait(500, msec);
  //turn in the direction of the goal
  chassis.turn_to_angle(-90);
  Scraper1.set(true);
  Scraper2.set(true);
  wait(500, msec);
  IntakeBottom.spin(reverse);
  IntakeMiddle.spin(forward);
  // IntakeTop.setVelocity(100, percent);
  chassis.drive_distance(13.75);
  wait(2000, msec);
  Scraper1.set(false);
  Scraper2.set(false);
  IntakeBottom.stop();
  IntakeMiddle.stop();
  //run intake
  chassis.drive_distance(-13);
  // IntakeBottom.setVelocity(100, percent);
  // IntakeMiddle.setVelocity(100, percent);
  // IntakeTop.setVelocity(100, percent);
  chassis.turn_to_angle(0);
  wait(100, msec);
  chassis.turn_to_angle(90);
  chassis.drive_distance(17.25);
  //run intake
  IntakeBottom.spin(forward);
  IntakeMiddle.spin(reverse);
  IntakeTop.spin(reverse);
  wait(150, msec);
  IntakeBottom.spin(reverse);
  IntakeMiddle.spin(forward);
  IntakeTop.spin(forward);
  wait(2000, msec);
}
