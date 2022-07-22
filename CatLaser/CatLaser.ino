#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates
#define SERVO_CNT 2
#define JS_X A0
#define JS_Y A1
#define DELAY_MIN 200
#define DELAY_MAX 2000
#define OSC_FREQ 27000000


uint8_t servonum = 0;
int current_pulse[SERVO_CNT];
int pulse_inc[SERVO_CNT];
int max_pulse[SERVO_CNT];
int min_pulse[SERVO_CNT];
long count = 0;
uint16_t x = 0;
uint16_t y = 0;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");
  for (int i = 0; i < SERVO_CNT; i++) {
    current_pulse[i] = USMIN;
    pulse_inc[i] = 1;
    max_pulse[i] = USMAX;
    min_pulse[i] = USMIN * 1.1;
  }

//  min_pulse[1] =  (USMAX + USMIN) * .6;
    max_pulse[1] =  (USMAX + USMIN) * .6;

  pwm.begin(); 
  pwm.setOscillatorFrequency(OSC_FREQ);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10);
}


void loop() {

#ifdef USE_JOYSTICK
  x = analogRead(JS_X);
  y = analogRead(JS_Y);

  pwm.writeMicroseconds(0, map(x, 0, 1023, min_pulse[0], max_pulse[0]));
  pwm.writeMicroseconds(1, map(y, 0, 1023, min_pulse[1], max_pulse[1]));
#else
  for (int i = 0; i < SERVO_CNT; i++)
    pwm.writeMicroseconds(i,  random(min_pulse[i], max_pulse[i]));

  delay( random( DELAY_MIN, DELAY_MAX) );
#endif
}
