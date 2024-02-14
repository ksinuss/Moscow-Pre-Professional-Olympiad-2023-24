//be happy

// инициализация для дисплея
#include <OLED_I2C.h>
OLED myOLED(SDA, SCL, 8);
extern uint8_t SmallFont[];
int flagol;
String gruz = " ";
String fnsh = "FINISH! ";

// инициализация для шаговых моторов
#include <Stepper_28BYJ_48.h>
Stepper_28BYJ_48 stepperin (11, 10, 9, 8);
Stepper_28BYJ_48 stepperup (7, 6, 5, 4);
int flagin;
int flagup;

// инициализация для сервопривода
#include <Servo.h>
Servo servo; // create servo object to control a servo
int pos; // variable to store the servo position
int take;
int drop;

// инициализация переменных для дальнейшего получения информации о грузах (распознавание)
int flagrcv = 1;
int finish;
String data;

void setup()
{
  Serial.begin(9600);

  servo.attach(12);
  
  myOLED.begin();
  myOLED.setFont(SmallFont);
}

void loop()
{

  if (flagrcv == 1)
  { data = receive();}

    delay(100);
  
//  if (data == "1")
//  { flagin = 1;}
//  if (data == "k")
//  { finish = 1;}
//  if (data == "0")
//  { 
//    flagol = 0;
//    flagin = 0;
//    flagup = 0;
//    flagrcv = 0;
//  }
  
  if (data == "a") 
  {
    gruz = "VINT ";
    take = 1;
  }
  if (data == "b") 
  {
    gruz = "GAIKA ";
    take = 1;
  }
  if (data == "c") 
  {
    gruz = "SHAIBA ";
    take = 1;
  }
  if (data == "d") 
  {
    gruz = "SHPILKA ";
    take = 1;
  }
  if (data == "e") 
  {
    gruz = "PODSHIPNIK ";
    take = 1;
  }
  if (data == "f") 
  {
    gruz = "NAPRAVLYAUSHAYA ";
    take = 1;
  }
  if (data == "g") 
  {
    gruz = "VAL ";
    take = 1;
  }
  if (data == "h") 
  {
    gruz = "DVIGATEL ";
    take = 1;
  }
  if (data == "i") 
  {
    gruz = "DATCHIK ";
    take = 1;
  }
  
  if (take == 1) // захват груза
  {
//    delay(100);
//    flagol = 1;
    flagup = 1;
    delay(7000);
    flagup = 0;
    flagol = 1;
    delay(300);
    flagol = 0;
    for (pos = 77; pos <= 90; pos += 1) { // 76
      // in steps of 1 degree
      servo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(50);                       // waits 15ms for the servo to reach the position
    }
    delay(2000);
    for (pos = 103; pos >= 90; pos -= 1) { // 104
      servo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(50);                       // waits 15ms for the servo to reach the position
    }
    delay(2000);
    
    flagup = 2;
    delay(7000);
    gruz = "xyu ";
    data = "";
  }

//  flagol = 1;
//  flagup = 1;
//  delay(3000);
//  flagup = 0;
//  flagup = 2;
//  delay(3000);
//  flagup = 0;

//  flagin = 1;
//  flagol = 1;
//  flagup = 1;
//  delay(7000);
//  flagup = 2;
//  delay(7000);
  
}

void yield() // выполнение функций независимо от loop
{  
  oleg();
  stepin();
  stepup();
}

void oleg() // display
{
  if (flagol == 1)
  {
    int y = 25;
    int i = CENTER;
    myOLED.print(gruz, i, y);
    myOLED.update();
//    delay(300);
  }
}

void stepin() // step motor in cart
{
  if (flagin == 1) 
  {
    stepperin.step(1);
    // delay(400000);
  }
  if (flagin == 2) 
  {
    stepperin.step(-1);
  }
}

void stepup() // step motor on top of cart
{
  if (flagup == 1) 
  {
    stepperup.step(1);
    // delay(400000);
  }
  if (flagup == 2) 
  {
    stepperup.step(-1);
  }
}

String receive() // получение сигнала о заказе или распознавшихся грузах
{
  if (Serial.available())
  {
    String data = Serial.readString();
    return data;
  }
  else
  { return "";}
}
