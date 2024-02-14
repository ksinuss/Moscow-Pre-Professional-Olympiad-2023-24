#include <Stepper_28BYJ_48.h>
Stepper_28BYJ_48 stepperin (11, 10, 9, 8);
Stepper_28BYJ_48 stepperup (7, 6, 5, 4);
int flagin;
int flagup;

#include <OLED_I2C.h>
extern uint8_t SmallFont[];
OLED myOLED(SDA, SCL, 8);
String del = "                       ";
String scan = "SCANNING... ";
String fnsh = "FINISH! ";
String gruz = " ";
int flagol;
int y = 25;
int x = CENTER;


void setup() {
  // put your setup code here, to run once:
  
}

void loop() {
  // 1
  stepperin.step(1);
  stepperin.step(1);
  stepperin.step(1);
  stepperin.step(1);
  stepperin.step(1);
  stepperin.step(1);
  stepperin.step(1);
  stepperin.step(1);
  stepperin.step(1);
  stepperin.step(1);
  stepperin.step(1);
  stepperin.step(1);
  stepperin.step(1);
  stepperin.step(1);
  stepperin.step(1);
  stepperin.step(1);
  stepperin.step(1);
  delay(100);
  myOLED.print(scan, x, y);
  myOLED.update();
  flagin = 1;
  delay(750);
  flagin = 0;
  delay(800); //w
  flagin = 1;
  delay(750);
  flagin = 0;
  myOLED.print(del, x, y);
  myOLED.update();
  myOLED.print("VINT " , x, y);
  myOLED.update();
  flagup = 1; //take
  delay(3000);
  flagup = 2;
  delay(3000);
  flagin = 1;
  delay(8000); //n
  flagin = 0;
  flagup = 1;
  delay(3000); //drop
  flagup = 2;
  delay(3000);
  flagup = 0;
  flagin = 2;
  delay(8000);
  flagin = 1;
  delay(750);
  flagin = 0;
  delay(800);
  flagin = 1;
  delay(750);
  flagin = 0;
  myOLED.print(del, x, y);
  myOLED.update();
  myOLED.print("GAIKA " , x, y);
  myOLED.update();
  flagup = 1; //take
  delay(3000);
  flagup = 2;
  delay(3000);
  flagin = 1;
  delay(8000); //n
  flagin = 0;
  flagup = 1;
  delay(3000); //drop
  flagup = 2;
  delay(3000);
  flagup = 0;
  myOLED.print(fnsh, x, y);
  myOLED.update();
  delay(10000);
  // 2
  delay(100);
  myOLED.print(scan, x, y);
  myOLED.update();
  flagin = 1;
  delay(750);
  flagin = 0;
  delay(800); //w
  flagin = 1;
  delay(750);
  flagin = 0;
  myOLED.print(del, x, y);
  myOLED.update();
  myOLED.print("VINT " , x, y);
  myOLED.update();
  flagup = 1; //take
  delay(3000);
  flagup = 2;
  delay(3000);
  flagin = 1;
  delay(8000); //n
  flagin = 0;
  flagup = 1;
  delay(3000); //drop
  flagup = 2;
  delay(3000);
  flagup = 0;
  flagin = 2;
  delay(8000);
  flagin = 1;
  delay(750);
  flagin = 0;
  delay(800);
  flagin = 1;
  delay(750);
  flagin = 0;
  myOLED.print(del, x, y);
  myOLED.update();
  myOLED.print("SHAIBA " , x, y);
  myOLED.update();
  flagup = 1; //take
  delay(3000);
  flagup = 2;
  delay(3000);
  flagin = 1;
  delay(8000); //n
  flagin = 0;
  flagup = 1;
  delay(3000); //drop
  flagup = 2;
  delay(3000);
  flagup = 0;
  flagin = 2;
  delay(8000);
  flagin = 1;
  delay(750);
  flagin = 0;
  delay(800);
  flagin = 1;
  delay(750);
  flagin = 0;
  myOLED.print(del, x, y);
  myOLED.update();
  myOLED.print("DVIGATEL " , x, y);
  myOLED.update();
  flagup = 1; //take
  delay(3000);
  flagup = 2;
  delay(3000);
  flagin = 1;
  delay(8000); //n
  flagin = 0;
  flagup = 1;
  delay(3000); //drop
  flagup = 2;
  delay(3000);
  flagup = 0;
  myOLED.print(fnsh, x, y);
  myOLED.update();
  delay(10000);
  //3
  delay(100);
  myOLED.print(scan, x, y);
  myOLED.update();
  flagin = 1;
  delay(750);
  flagin = 0;
  delay(800); //w
  flagin = 1;
  delay(750);
  flagin = 0;
  myOLED.print(del, x, y);
  myOLED.update();
  myOLED.print("VINT " , x, y);
  myOLED.update();
  flagup = 1; //take
  delay(3000);
  flagup = 2;
  delay(3000);
  flagin = 1;
  delay(8000); //n
  flagin = 0;
  flagup = 1;
  delay(3000); //drop
  flagup = 2;
  delay(3000);
  flagup = 0;
  flagin = 2;
  delay(8000);
  flagin = 1;
  delay(750);
  flagin = 0;
  delay(800);
  flagin = 1;
  delay(750);
  flagin = 0;
  myOLED.print(del, x, y);
  myOLED.update();
  myOLED.print("PODSHIPNIK " , x, y);
  myOLED.update();
  flagup = 1; //take
  delay(3000);
  flagup = 2;
  delay(3000);
  flagin = 1;
  delay(8000); //n
  flagin = 0;
  flagup = 1;
  delay(3000); //drop
  flagup = 2;
  delay(3000);
  flagup = 0;
  flagin = 2;
  delay(8000);
  flagin = 1;
  delay(750);
  flagin = 0;
  delay(800);
  flagin = 1;
  delay(750);
  flagin = 0;
  myOLED.print(del, x, y);
  myOLED.update();
  myOLED.print("VAL " , x, y);
  myOLED.update();
  flagup = 1; //take
  delay(3000);
  flagup = 2;
  delay(3000);
  flagin = 1;
  delay(8000); //n
  flagin = 0;
  flagup = 1;
  delay(3000); //drop
  flagup = 2;
  delay(3000);
  flagup = 0;
  myOLED.print(fnsh, x, y);
  myOLED.update();
  delay(10000);
}

void yield() // выполнение функций независимо от loop
{  
  oleg();
  stepin();
  stepup();
}

void oleg() // display
{
  int y = 25;
  int x = CENTER;
  if (flagol == 1)
  {
    myOLED.print(del, x, y);
    myOLED.update();
    myOLED.print(gruz, x, y);
    myOLED.update();
  }
  if (flagol == 2)
  {
    myOLED.print(del, x, y);
    myOLED.update();
    myOLED.print(scan, x, y);
    myOLED.update();
  }
  if (flagol == 3)
  {
    myOLED.print(del, x, y);
    myOLED.update();
    myOLED.print(fnsh, x, y);
    myOLED.update();
  }
}

void stepin() // step motor in cart
{
  if (flagin == 1) 
  { stepperin.step(1);}
  if (flagin == 2) 
  { stepperin.step(-1);}
}

void stepup() // step motor on top of cart
{
  if (flagup == 1) 
  { stepperup.step(1);}
  if (flagup == 2) 
  { stepperup.step(-1);}
}
