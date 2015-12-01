#include <Servo.h> 
#include <Stepper.h>
Servo myservo; // servo motor handle

#define STEPS 200  // num of steps for the stepper motor
Stepper stepper(STEPS, 8, 9, 10, 11); // pin numbers for controlling the stepper motor.

int up = -1;  // travel direction.
int down = 1;


// only run once at the beginning
void setup() {
  myservo.attach(2);  // pin 2 for controlling the servo motor.
}


// runs after the setup, forever
void loop() {
  myservo.write(0); // sets the arm angle to 0.
  delay(1000); // wait a 1000 miliseconds, 1 sec
  myservo.write(130); // arm angle to 130, squeezes the badminton birdies 
  delay(1000);
  slowlySpeedUp(down); // slowly start the elevator going down
  stepper.step(15800); // go down until reaching the throwing motors, 15800 found by try and error. 
  delay(200); // wait a bit at the bottom so everything is stable.
  myservo.write(0); // release the birdie, holding arm angle to 0 
  delay(200); // wait for the birdie to hit the throwing motors and fly away
  slowlySpeedUp(up); // go back up
  stepper.step(-15800); // go back up to the beginning point. note the negative sign
}

// Manual but highly effective. Because this robot is a mechanical device, I can't go to maximum speed immediately. 
// have to slowly speed up, go a few steps and speed up more. 
void slowlySpeedUp(int direction) {
  int initialStep = 15; // experimental number, used for deciding how quick to speed up
  stepper.setSpeed(10);
  stepper.step(direction*initialStep);
  stepper.setSpeed(20);
  stepper.step(direction*initialStep*2); // higher the speed, higher the steps so that steps/speed = time remains constant. 
  stepper.setSpeed(40);
  stepper.step(direction*initialStep*4);
  stepper.setSpeed(80);
  stepper.step(direction*initialStep*8);
  stepper.setSpeed(160);
  stepper.step(direction*initialStep*16);
  stepper.setSpeed(200); // couldn't double the speed, motor wouldn't go
  stepper.step(direction*initialStep*32);
  stepper.setSpeed(210); // can't double, motor cant handle, just incremental increase
  stepper.step(direction*initialStep*32);
}

