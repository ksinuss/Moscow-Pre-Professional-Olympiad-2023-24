#include <Stepper_28BYJ_48.h>
#include <Servo.h>

Stepper_28BYJ_48 stepperin (11, 10, 9, 8);
Stepper_28BYJ_48 stepperup (7, 6, 5, 4);

Servo servo;
int flag;

void setup()
{ 
  servo.attach(12);
  servo.write(75);
  // запускаем последовательную коммуникацию: 
  Serial.begin(9600);                                             
} 

void loop() 
{                                                              
//  servo.write(95);
//  delay(2000);
//  servo.write(115);
//  delay(2000);
//  flag = 1;
//  delay(100);
  flag = 2;
  delay(4000);
  flag = 3;
  delay(3000);
}
               
void yield() 
{
  if (flag == 1){
    stepperin.step(1);
  }
  if (flag == 2){
    stepperup.step(1);
  }
  if (flag == 3)
  { stepperup.step(-1);}
}
