/*
 * Arduino code to control a stepper motor with pushbuttons using a Raspberry Pi Pico or any other microcontroller.
 * 
 * By KushagraK7: https://www.instructables.com/member/KushagraK7/
 * 
 * Feel free to modify the code and tinker around with it and please attribute before publising.
 */
#include<AccelStepper.h>

AccelStepper stepper(AccelStepper :: DRIVER, 16, 17);

#define B1 A2
#define B2 A1
#define B3 A0

int p = 0, pos;
int i = 0;

void setup() {
  // put your setup code here, to run once:

  pinMode(B1, INPUT_PULLUP);
  pinMode(B2, INPUT_PULLUP);
  pinMode(B3, INPUT_PULLUP);

  stepper.setSpeed(150);

  stepper.setAcceleration(5000);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  if(digitalRead(B1) == LOW) p++;

  if(digitalRead(B2) == LOW) p--;

  if(digitalRead(B3) == LOW)
  {
    while(digitalRead(B3) == LOW)
    {
      i++;

      if(i >= 2000) break;

      delay(1);
    }

    if(i >= 2000)
    {
      i = 0;
      
      stepper.setCurrentPosition(0);
      stepper.setSpeed(150);

      stepper.runToNewPosition(40);

      stepper.runToNewPosition(0);
    }
    p = 0;

    while(digitalRead(B3) == LOW);
  }

  pos = p/20;

  stepper.moveTo(pos);

  stepper.run();

  Serial.println(pos);

}
