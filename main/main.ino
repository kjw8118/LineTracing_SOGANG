
#include <Servo.h>
#include "config.h"
#include "setup.h"
#include "loop.h"

Servo str;
uint8_t mode = 0;
uint8_t mode_tmp2;
bool flag;
bool swt;
uint32_t tm;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  set_servo(str);
  set_pinMode();
  delay(100);
  flag = false;
  swt = false;
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t mode_tmp;
  Steering(str);
  if (flag == false) {
    if (ModeSelect() == 1) {
      flag = true;
      swt = true;
    }
  }
  if (swt == true) {
    if (tm > 50) {
      mode = random(1, NUM_MODE);
      tm = 0;
      swt = false;
      flag = false;
    } else tm++;
  } else mode = 0;

  Motor(mode);
  delay(10);

}
