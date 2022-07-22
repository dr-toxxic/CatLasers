
#include <ezButton.h>

#include "Constants.h"
#include "CatLaserServo.h"

// GLOBALS
ezButton button(BUTTON_PIN);  // create ezButton object
CatLaserServo myservo[SERVO_CNT] = {CatLaserServo(SERVO1_PIN, JS_X,  30, 90),  CatLaserServo(  SERVO2_PIN, JS_Y, 45, 135  )  };

long t = 0;
bool curServo = false;
bool useJS = false;

void setup() {
  Serial.begin(9600);
  button.setDebounceTime(DEBOUNCE_TIME); // set debounce time to 50 milliseconds
  for (int i = 0; i < SERVO_CNT; i++) {
    myservo[i].setup();
  }
}

void loop() {
  checkButton();

  if ( t < millis() ) {

    if ( useJS) {
      joystick_control();
    }
    else {
      random_control();
    }
    t = millis() + getIncrement();
  }
}
int getIncrement() {
  if ( useJS)
    return JS_DELAY;
  else
    return random( DELAY_MIN, DELAY_MAX); //  choose a new delay time

}

void joystick_control() {
  for (int i = 0; i < SERVO_CNT; i++) {
    myservo[i].joystick_control();
  }

}
void random_control() {
  myservo[curServo].random_control();              // tell servo to go to position in variable 'pos'
  curServo = ! curServo;
}

void checkButton() {
  button.loop(); // MUST call the loop() function first

  int btnState = button.getState();
  //Serial.println(btnState);

  if (button.isPressed()) { 
    Serial.println("The button is pressed");
    useJS = !useJS;
  }

  if (button.isReleased())
    Serial.println("The button is released");
    
}
