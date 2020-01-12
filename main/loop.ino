#include <Servo.h>
#include "config.h"


uint16_t get_SONAR() {
  uint16_t buf;
  digitalWrite(PIN_SONAR_TRIG, 1);
  delayMicroseconds(10);
  digitalWrite(PIN_SONAR_TRIG, 0);
  delayMicroseconds(20);
  buf = pulseIn(PIN_SONAR_ECHO, HIGH, 1000000);
  Serial.print("SONAR Real : ");
  Serial.println(buf);

  return buf;
}

uint8_t Sum_LineTracing() {
  uint8_t buf;
  buf = !digitalRead(PIN_LL) + !digitalRead(PIN_LM) + !digitalRead(PIN_MM) + !digitalRead(PIN_RM) + !digitalRead(PIN_RR);
  return buf;
}

float Mean_LineTracing() {
  float buf;
  buf = (!digitalRead(PIN_LL) * (-2) + !digitalRead(PIN_LM) * (-1.5) + !digitalRead(PIN_RM) * (1.5) + !digitalRead(PIN_RR) * (2));
  return buf;
}

float LineTracing() {
  float buf;

  if (Sum_LineTracing() == 2) {
    buf = Mean_LineTracing() / 2;
  } else if (Sum_LineTracing() == 3) {
    buf = Mean_LineTracing() / 3;
  } else if (Sum_LineTracing() == 5) {
    buf = 10;
  } else buf = Mean_LineTracing();


  return buf;
}

void Steering(Servo str) {
  float buf_LT;
  uint8_t ang = STEERING_MID;
  buf_LT = LineTracing();
  Serial.print("buf_LT : ");
  Serial.println(buf_LT);
  if (buf_LT != 10) {
    ang = STEERING_GAP * buf_LT / 2 + STEERING_MID;
    str.write(ang);
  }
  Serial.print("angle : ");
  Serial.println(ang);

}


void Motor(uint8_t Mode) {
  switch (Mode) {
    case 0:
      analogWrite(PIN_MOTOR_PWM_A, THROTTLE_NORMAL);
      analogWrite(PIN_MOTOR_PWM_B, THROTTLE_NORMAL);
      break;
    case 1:
      analogWrite(PIN_MOTOR_PWM_A, THROTTLE_THIRD);
      analogWrite(PIN_MOTOR_PWM_B, THROTTLE_THIRD);
      break;
    case 2:
      analogWrite(PIN_MOTOR_PWM_A, THROTTLE_DOUBLE);
      analogWrite(PIN_MOTOR_PWM_B, THROTTLE_DOUBLE);
      break;
    case 3:
      analogWrite(PIN_MOTOR_PWM_A, THROTTLE_HALF);
      analogWrite(PIN_MOTOR_PWM_B, THROTTLE_HALF);
      break;
    case 4:
      analogWrite(PIN_MOTOR_PWM_A, 0);
      analogWrite(PIN_MOTOR_PWM_B, 0);
      delay(2000);
      analogWrite(PIN_MOTOR_PWM_A, THROTTLE_NORMAL);
      analogWrite(PIN_MOTOR_PWM_B, THROTTLE_NORMAL);
    default :
      analogWrite(PIN_MOTOR_PWM_A, THROTTLE_NORMAL);
      analogWrite(PIN_MOTOR_PWM_B, THROTTLE_NORMAL);
      break;
  }
  Serial.print("mode : ");
  Serial.println(Mode);

}

uint8_t ModeSelect() {
  uint8_t buf;
  uint16_t buf_SONAR;
  buf_SONAR = get_SONAR();
  Serial.print("SONAR : ");
  Serial.println(buf_SONAR);
  if (buf_SONAR < THRESHOLD) {
    buf = 1;
  } else {
    buf = 0;
  }
  return buf;

}
