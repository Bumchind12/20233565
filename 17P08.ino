#include <Servo.h>

#define IR A0
#define PIN_SERVO 10
#define PIN_LED 9
#define _DUTY_MIN 550  // servo full clock-wise position (0 degree)
#define _DUTY_NEU 1475 // servo neutral position (90 degree)
#define _DUTY_MAX 2400 // servo full counter-clockwise position (180 degree
#define _DIST_MIN 100.0   // minimum distance to be measured (unit: mm)
#define _DIST_MAX 250.0   // maximum distance to be measured (unit: mm)
#define LOOP_INTERVAL 50   // Loop Interval (unit: msec)
#define _EMA_ALPHA 0.2
Servo myservo;
unsigned long last_loop_time;   // unit: msec

float dist_prev,dist_ema = _DIST_MIN;
int ValueOfServo;

void setup()
{
  pinMode(PIN_LED, OUTPUT);
  myservo.attach(PIN_SERVO);
  myservo.writeMicroseconds(_DUTY_NEU);
 
  Serial.begin(1000000);
}

void loop()
{
  float dist_raw;
  unsigned long time_curr = millis();
  int a_value, duty;

  // wait until next event time
  if (time_curr < (last_loop_time + LOOP_INTERVAL))
    return;
  last_loop_time += LOOP_INTERVAL;

  // Remove Next line !!!
  //a_value = analogRead(PIN_POTENTIOMETER);
  // Read IR Sensor value !!!
  a_value = analogRead(IR);
 
  // Convert IR sensor value into distance !!!
  dist_raw = (6762.0/(a_value-9)-4.0)*10.0 - 60.0;
 
  // we need distance range filter here !!!
  if (dist_raw < _DIST_MIN) {
    dist_raw = dist_prev;           // cut lower than minimum
    digitalWrite(PIN_LED, 1);       // LED OFF
    myservo.writeMicroseconds(_DUTY_MIN);
  } else if (dist_raw > _DIST_MAX) {
    dist_raw = dist_prev;           // Cut higher than maximum
    digitalWrite(PIN_LED, 1);       // LED OFF
    myservo.writeMicroseconds(_DUTY_MAX);
  } else {    // In desired Range
    digitalWrite(PIN_LED, 0);       // LED ON      
    dist_prev = dist_raw;
    ValueOfServo = (int)(((dist_ema-100)*12.3)+550);
    myservo.writeMicroseconds(ValueOfServo);
  }
 
  // we need EMA filter here !!!
  dist_ema = _EMA_ALPHA*dist_raw+(1-_EMA_ALPHA)*dist_ema;


  // map distance into duty
  //duty = map(a_value, 0, 1023, _DUTY_MIN, _DUTY_MAX);
  //myservo.writeMicroseconds(duty);

  // print IR sensor value, distance, duty !!!
  Serial.print("Min:"); Serial.print(_DIST_MIN);
  Serial.print(",IR:"); Serial.print(a_value);
  Serial.print(",dist:"); Serial.print(dist_raw);
  Serial.print(",ema:"); Serial.print(dist_ema);
  Serial.print(",Servo:"); Serial.print(ValueOfServo);
  Serial.print(",Max:"); Serial.print(_DIST_MAX);
  Serial.println("");
