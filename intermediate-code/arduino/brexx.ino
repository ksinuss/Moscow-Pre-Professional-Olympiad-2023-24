#include <Servo.h>
Servo servo; // create servo object to control a servo

void setup() {
  // put your setup code here, to run once:
  servo.attach(12);
  servo.write(110);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(5500);
  servo.write(95);
  delay(100);
  
}
