#include <Servo.h>
#include "config.h"

void set_pinMode() {

//  pinMode(PIN_CLP, INPUT);
//  pinMode(PIN_Near, INPUT);
  pinMode(PIN_LL, INPUT);
  pinMode(PIN_LM, INPUT);
  pinMode(PIN_MM, INPUT);
  pinMode(PIN_RM, INPUT);
  pinMode(PIN_RR, INPUT);

  pinMode(PIN_SONAR_TRIG, OUTPUT);
  digitalWrite(PIN_SONAR_TRIG, 0);  

  pinMode(PIN_SONAR_ECHO, INPUT);

  pinMode(PIN_MOTOR_DIR_A, OUTPUT);
  pinMode(PIN_MOTOR_DIR_B, OUTPUT);

  digitalWrite(PIN_MOTOR_DIR_A, 1);
  digitalWrite(PIN_MOTOR_DIR_B, 1);        

  analogWrite(PIN_MOTOR_PWM_A, 150);
  analogWrite(PIN_MOTOR_PWM_B, 150);
  delay(100);
  analogWrite(PIN_MOTOR_PWM_A, 100);
  analogWrite(PIN_MOTOR_PWM_B, 100);
  

}

void set_servo(Servo str){
  str.attach(PIN_SERVO);
  str.write(STEERING_MID);
}
