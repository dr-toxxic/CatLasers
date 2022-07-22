#ifndef CATLASERSERVO_H_
#define CATLASERSERVO_H_
#include <Servo.h>

#include "Constants.h"
/**
   CatLaserServo
   Defines a Servo for the Cat Laser
*/
class CatLaserServo {
  private:
    byte _min;
    byte _max;
    byte _curr;
    byte _next;
    byte _pin;
    byte _js_pin;
    Servo _servo;

  public:
    CatLaserServo(byte pin = 0, byte js_pin = 0, byte min_pos = 0, byte max_pos = 180) {
      _min = min_pos;
      _max = max_pos;
      _curr = 0;
      _next = 0;
      _pin = pin;
      _js_pin = js_pin;
    }
    void setup()
    {
      _servo.attach(_pin);  // attaches the servo on pin 9 to the servo object
    }
    void joystick_control()
    {
      _next = map (analogRead(_js_pin), SENSOR_MIN, SENSOR_MAX, _min, _max ) ;
      if ( abs (_next - _curr ) >= MIN_MOVEMENT) {


        _servo.write( _next );
        _curr = _next;
      }
    }


    void random_control() {
      _next = _curr;
      while ( abs (_next - _curr ) < MIN_MOVEMENT) {
        _next = random(_min, _max );
      }
      /*
      byte diff = _next - _curr;
      byte dir = ( diff ) / abs( diff );            // either 1 or -1
      for (byte i = _curr; i != _next; i += dir) {  // move 1 degree at a time.
        _servo.write( i );                          // tell servo to go to position in variable 'pos'
        delay(SERVO_DELAY);                         // slow it down a little.  Don't tell anyone I used delay. I am a naughty naughty little boy.
      }
      
      */
      _servo.write(_next);
      _curr = _next;

    }
};

#endif
