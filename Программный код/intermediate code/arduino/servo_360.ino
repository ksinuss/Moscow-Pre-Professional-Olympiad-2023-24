#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(12);  // attaches the servo on pin 9 to the servo object
//  myservo.write(0);
}

void loop() {
  myservo.write(1);
  delay(50);
//  myservo.write(-1);
//  delay(50);
  for (pos = 77; pos <= 90; pos += 1) { // 76
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(50);                       // waits 15ms for the servo to reach the position
  }
//  delay(2000);
//  for (pos = 103; pos >= 90; pos -= 1) { // 104
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(50);                       // waits 15ms for the servo to reach the position
//  }
  delay(2000);
}

//void serv() // servo
//{
//  if (flagserv == 1)
//  {
//    for (pos = 65; pos <= 90; pos += 1) 
//    {
//      servo.write(pos);              // tell servo to go to position in variable 'pos'
//      delay(40);                       // waits 40ms for the servo to reach the position
//    }
//  }
//  if (flagserv == 2)
//  {
//    for (pos = 115; pos >= 90; pos -= 1) 
//    {
//      servo.write(pos);              // tell servo to go to position in variable 'pos'
//      delay(40);                       // waits 40ms for the servo to reach the position
//    }
//  }
//}
