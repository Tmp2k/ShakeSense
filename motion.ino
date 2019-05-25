/*
 * MotorKnob
 *
 * A stepper motor follows the turns of a potentiometer
 * (or other sensor) on analog input 0.
 *
 * http://www.arduino.cc/en/Reference/Stepper
 * This example code is in the public domain.
 */

#include <Stepper.h>

// change this to the number of steps on your motor
#define STEPS 200
#define PIN_BTNOUT   12
#define PIN_BTND     11
#define PIN_BTNU     10
#define PIN_BTNR     9
#define PIN_BTNL     8
#define PIN_BTN     7


#define PIN_LED   13

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS, 2, 3, 4, 5);

bool clockwise = false;
int stepAmount = 1;
int count = 0;

int excursion = 50;
int speed = 50;
int randomness = 20;
int duration = 5;
int randomExtra = 0;
unsigned long stopAt = 0;

bool shaking = false;


void setup() {

  pinMode(PIN_LED,OUTPUT);
  pinMode(PIN_BTNOUT,OUTPUT);
  digitalWrite(PIN_BTNOUT,LOW);

  pinMode(PIN_BTNU,INPUT_PULLUP);
  pinMode(PIN_BTND,INPUT_PULLUP);
  pinMode(PIN_BTNL,INPUT_PULLUP);
  pinMode(PIN_BTNR,INPUT_PULLUP);
  pinMode(PIN_BTN,INPUT_PULLUP);
  
  
  
}



void loop() {

  int thisStep;

  if(stopAt < millis()) {
    shaking = false;
    stopAt = 0;
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    
  }

  if(stopAt == 0) {
    if(!digitalRead(PIN_BTNL)) quake1();
    if(!digitalRead(PIN_BTNU)) quake2();
    if(!digitalRead(PIN_BTNR)) quake3();
  }


  if(shaking) {
    if(count > excursion + randomExtra) {
      clockwise = !clockwise;
      count = 0;
      randomExtra = random(0,randomness)- randomness/2;
    }
  
    // move a number of steps equal to the change in the
    // sensor reading
    if(clockwise) {
      thisStep = stepAmount;
    } else {
      thisStep = stepAmount * -1;
    }
    stepper.step(thisStep);
    count++;
  }
  
}


void quake1() {

  excursion = 30;
  speed = 20;
  stepper.setSpeed(speed);
  
  stopAt = millis()+10000;
  shaking = true;
}

void quake2() {

  excursion = 40;
  speed = 50;
  stepper.setSpeed(speed);

  stopAt = millis()+10000;
  shaking = true;
}

void quake3() {

  excursion = 60;
  speed = 90;
  stepper.setSpeed(speed);

  stopAt = millis()+10000;
  shaking = true;
}
