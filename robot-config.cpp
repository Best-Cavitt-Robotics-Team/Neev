
#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen.
brain  Brain;

//The motor constructor takes motors as (port, ratio, reversed), so for example
//motor LeftFront = motor(PORT1, ratio6_1, false);
controller Controller = controller(primary);

motor RightFront = motor(PORT3, ratio6_1, false);
motor RightMiddle = motor(PORT16, ratio6_1, true);
motor RightBack = motor(PORT1, ratio6_1, false);

motor LeftFront = motor(PORT17, ratio6_1, true);
motor LeftMiddle = motor(PORT11, ratio6_1, false);
motor LeftBack = motor(PORT6, ratio6_1, true);

motor IntakeBottom = motor(PORT10, ratio6_1, false);
motor IntakeMiddle = motor(PORT13, ratio18_1, false);
motor IntakeTop = motor(PORT8, ratio18_1, false);

led Scraper1(Brain.ThreeWirePort.A);
led Scraper2(Brain.ThreeWirePort.B);
led BallStop(Brain.ThreeWirePort.C);
led WheelPiston(Brain.ThreeWirePort.D);
//Add your devices below, and don't forget to do the same in robot-config.h:

inertial Inertial = inertial(PORT14);

rotation VerticalOdom = rotation(PORT5, true);
rotation HorizontalOdom = rotation(PORT7, false);


void vexcodeInit( void ) {
  // nothing to initialize
}
