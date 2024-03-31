#include <Servo.h>
Servo myservo1; 
Servo myservo2;
Servo myservo3;
Servo myservo4;

int pos1=80, pos2=60, pos3=130, pos4=0; 

// правый джойстик 1
const int right_X = A3;  
const int right_Y = A4;
const int right_key = 8;

// левый джойстик 2
const int left_X = A2;
const int left_Y = A5; 
const int left_key = 7;

int x1,y1,z1; // правый 1
int x2,y2,z2; // левый 2

void setup() 
{
  myservo1.write(pos1);  
  delay(1000);
  myservo2.write(pos2);
  myservo3.write(pos3);
  myservo4.write(pos4);
  delay(1500);

  pinMode(right_key, INPUT);  
  pinMode(left_key, INPUT);
  Serial.begin(9600);
}

void loop() 
{
  myservo1.attach(A1);  // set the control pin of servo 1 to A1
  myservo2.attach(A0);  // set the control pin of servo 2 to A0
  myservo3.attach(6);   //set the control pin of servo 3 to D6
  myservo4.attach(9);   // set the control pin of servo 4 to D9

  x1 = analogRead(right_X); //read the right X value 
  y1 = analogRead(right_Y);  // read the right Y value 
  z1 = digitalRead(right_key);  // read the right Z value 
  
  x2 = analogRead(left_X);
  y2 = analogRead(left_Y);   
  z2 = digitalRead(left_key); 

  updownhand();
  turn();
  open();
  updown();
  button();
}

void button()
{
  if (z1==1 or z2 == 1)
  { Serial.write('1');}
}

// вверх вниз рука
void updownhand()
{
  if(x2<50) // правый джойстик вправо - вверх
  {
    pos4--;
    myservo4.write(pos4);
    delay(5);
    if (pos4<1) { pos4=1;}
   }
  if(x2>1000) // правый джойстик влево - вниз
  {
    pos4++;
    myservo4.write(pos4);
    delay(5);
    if (pos4>100) { pos4=100;}
  }
}

 // повернуться
void turn()
{
  if(x1<50)  // если первый джойстик вправо - вправо
  {
    pos1--;
    myservo1.write(pos1);
    delay(5);
    if(pos1<1) { pos1=1;}
  }
  if(x1>1000)  // если первый джойстик влево - влево
  {
    pos1++; 
    myservo1.write(pos1); 
    delay(5);
    if(pos1>180) { pos1=180;}
  }
}

// открыть закрыть
void open()
{
  if(y1>1000) // правый джойстик вверх - открыть
  {
    pos2--;
    myservo2.write(pos2); 
    delay(5);
    if(pos2<0) { pos2=0;}
  }
  if(y1<50)  // правый джойстик вниз - закрыть
  {
    pos2++;  
    myservo2.write(pos2);  
    delay(5);
    if(pos2>180) { pos2=180;}
  }
}

// вверх вниз
void updown()
{
  if(y2<50) // левый джойстик вверх - вверх 
  {
    pos3++;
    myservo3.write(pos3);   
    delay(5);
    if(pos3>180) { pos3=180;}
  }
  if(y2>1000) // левый джойстик вниз - вниз
  {
    pos3--;
    myservo3.write(pos3); 
    delay(5);
    if(pos3<10) { pos3=10;}
  }
}
