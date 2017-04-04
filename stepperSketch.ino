/* 
 *   === FINDING FEANOR
 *  
 *   === Zach Pewitt & John Fordice
 * 
 *   === Washington University in St. Louis
 * 
 *   === ESE 205 - Prof. Humberto Gonzalez
 * 
 *   This sketch controls the sensitivity of our
 *   phototransistors, calculates the appropriate angle 
 *   from a zero point, then controls the rotation of
 *   the panel via the two stepper motors.
 *  
 */

 /* 
    x an integer
 
    steps(x) --> stepper moves clockwise x steps
    
    steps(-x) --> stepper moves counterclockwise x steps

    The wiring on the ITEAD 4-Wire terminal isA:
      RED, BLUE, BLACK, GREEN

    The trick to be able to rotate both directions is to define the Stepper object
      with 2 input pins instead of 4 input pins.
*/

#include <Stepper.h>

const int stepsPerRevolution = 200;
//the number of motor steps which defines a complete revolution

const int tolTopBot = 65;
const int tolLeftRight = 45;
//if the subtractive differences between 

int stepCount = 0;
int stepsTB = 0;
int stepsLR = 0;
//counters which will be in/decremented in the loop() based on the
//direction of rotation

int diffLR;
//subtractive difference between the voltage values read from 
//the left and right phototransistors


int diffTB;
//subtractive difference between the voltage values read from
//the top and bottom phototransistors

int PTR;
int PTL;
int PTT;
int PTB;
//phototransistors corresponding to the right, left, top, and
//bottom positions, respectively

String readStr = "";
//string to store the bits entered into the serial monitor

int leftBound = -3200;
int rightBound = 3200;
//physial limits for the number of steps to the left and right
//to avoid wire tangle

int topBound = -1400;
int bottomBound = 1400
//physial limits for the number of steps to the left and right
//to avoid wire tangle


Stepper LRStepper(stepsPerRevolution, 2, 3);
//create the stepper object to rotate whole assembly

Stepper TBStepper(stepsPerRevolution, 6, 7);
//create the stepper object to rotate the panel


void setup() {

  Serial.begin(9600);
  pinMode(13,OUTPUT);
  
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  TBStepper.setSpeed(200);
  //setting y-axis (top/bottom) motor control pins and parameters

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  LRStepper.setSpeed(125);
  //setting x-axis (top/bottom) motor control pins and parameters 
}

void loop() {

  PTT = analogRead(1);
  PTL = analogRead(2);
  PTB = analogRead(3);
  PTR = analogRead(0);
  //read in raw voltages from all four phototransistors
  
  diffLR = PTL - PTR;
  //calculating subtracive differences between left-right pair
  
  diffTB = PTT - PTB;
  //calculating subtracive differences between top-bottom pair

  if (diffLR > tolLR && stepsLR > -3200) {
    LRStepper.step(-1);
    stepsLR -= 1; 
  }
  
  else if (diffLR < -tolLR && stepsLR < 3200) {
    LRStepper.step(1);
    stepsLR += 1;
  }
  
  if (diffTB > tolTB && stepsTB > -1400) {
    TBStepper.step(-1);
    stepsTB -= 1; 
  }
  
  else if (diffTB < -tolTB && stepsTB < 1400) {
    TBStepper.step(1);
    stepsTB += 1;
  }
  
  if ((stepsLR == rightBound or stepsLR == -leftBound)
     or (stepsTB == bottomBound or stepsTB == -topBound) {
       digitalWrite(13,HIGH);
  } 
}
