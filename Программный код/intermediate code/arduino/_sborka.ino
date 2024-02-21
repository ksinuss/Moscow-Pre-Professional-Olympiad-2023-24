//be happy

// инициализация для дисплея
#include <OLED_I2C.h>
OLED myOLED(SDA, SCL, 8);
extern uint8_t SmallFont[];
int flagol;
String gruz;

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

// инициализация для узд
#define PIN_TRIG 3
#define PIN_ECHO 2
long duration, cm;
int cmp, cmb;
int back;

// инициализация переменных для дальнейшего получения информации о грузах (заказ и распознавание)
// int datapp;
int flagrcv = 1;
int vint0;
int gaik0;
int shab0;
int shpl0;
int pdsh0;
int napr0;
int val0;
int dvig0;
int dtch0;
// String dataras;
String data;
String vint = "VINT ";
String gaik = "GAIKA ";
String shab = "SHAIBA ";
String shpl = "SHPILKA ";
String pdsh = "PODSHIPNIK ";
String napr = "NAPRAVLYAUSHAYA ";
String val = "VAL ";
String dvig = "DVIGATEL ";
String dtch = "DATCHIK ";

void setup()
{
  Serial.begin(9600);
  
  myOLED.begin();
  myOLED.setFont(SmallFont);
  
  servo.attach(12);

  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
}

void loop()
{
  // datapp = receiveapp();
  if (flagrcv == 1)
  { data = receive();}
  
  if (data == "11")
  { 
    vint0 = 0;
    gaik0 = 0;
    shab0 = 0;
    shpl0 = 0;
    pdsh0 = 0;
    napr0 = 0;
    val0 = 0;
    dvig0 = 0;
    dtch0 = 0;
  }

  if (data == "2") 
  { vint0 = 1;}
  if (data == "3") 
  { gaik0 = 1;}
  if (data == "4") 
  { shab0 = 1;}
  if (data == "5") 
  { shpl0 = 1;}
  if (data == "6") 
  { pdsh0 = 1;}
  if (data == "7") 
  { napr0 = 1;}
  if (data == "8") 
  { val0 = 1;}
  if (data == "9") 
  { dvig0 = 1;}
  if (data == "10") 
  { dtch0 == 1;}

  if (data == "a") 
  {
    gruz = vint;
    if (vint0 == 1) 
    { take = 1;}
  }
  if (data == "b") 
  {
    gruz = gaik;
    if (gaik0 == 1) 
    { take = 1;}
  }
  if (data == "c") 
  {
    gruz = shab;
    if (shab0 == 1) 
    { take = 1;}
  }
  if (data == "d") 
  {
    gruz = shpl;
    if (shpl0 == 1) 
    { take = 1;}
  }
  if (data == "e") 
  {
    gruz = pdsh;
    if (pdsh0 == 1) 
    { take = 1;}
  }
  if (data == "f") 
  {
    gruz = napr;
    if (napr0 == 1) 
    { take = 1;}
  }
  if (data == "g") 
  {
    gruz = val;
    if (val0 == 1) 
    { take = 1;}
  }
  if (data == "h") 
  {
    gruz = dvig;
    if (dvig0 == 1) 
    { take = 1;}
  }
  if (data == "i") 
  {
    gruz = dtch;
    if (dtch0 == 1) 
    { take = 1;}
  }
  
  if (take == 1) // захват груза
  {
    flagin = 0;
    cmb = kabanchik();
    flagup = 1;
    delay(3000);
    flagup = 0;
    for (pos = 115; pos >= 90; pos -= 1) 
    {
      servo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(40);                       // waits 40ms for the servo to reach the position
    }
    flagup = 2;
    delay(3000);
    flagup = 0;
    flagin = 1;
    flagrcv = 0;
    take = 0;
  }

  cmp = cm; // предыдущее значение узд для дальнейшего сравнения
  cm = kabanchik(); // считываем показания узд

  if (cm > 0 and back == 0) // едем вперед
  {
    flagin = 1;
    back = 0;
  }
  if (cm > 58 and cmp < 900 and cm < 900 and back == 0) // приехали к накопителю
  {
    delay(500);
    drop = 1;
  }
  if ((cm > 300 or (cmb-2 <= cm and cm <= cmb+2)) and back == 1) // приехали на (базу) к месту, где остановились/распознали последний груз
  {
    flagin = 0;
    delay(10);
    back = 0;
    flagin = 1;
    flagrcv = 1;
  }
  
  if (drop == 1) // скидываем груз
  {
    flagin = 0;
    flagup = 1;
    delay(3000);
    flagup = 0;
    for (pos = 65; pos <= 90; pos += 1) 
    {
      servo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(40);                     // waits 40ms for the servo to reach the position
    }
    flagup = 2;
    delay(3000);
    flagup = 0;
    flagin = 2;
    back = 1;
    drop = 0;
  }
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
    delay(50);
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
  if (flagup == 1) {
  stepperup.step(1);
  // delay(400000);
  }
  if (flagup == 2) {
    stepperup.step(-1);
  }
}

int kabanchik() // ultrasonic distance sensor 
{
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG, HIGH);
  // Выставив высокий уровень сигнала, ждем около 10 микросекунд. В этот момент датчик будет посылать сигналы с частотой 40 КГц.
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  // Время задержки акустического сигнала на эхолокаторе.
  duration = pulseIn(PIN_ECHO, HIGH);
  // Теперь осталось преобразовать время в расстояние
  cm = (duration / 2) / 29.1;
  Serial.print("Расстояние до объекта: ");
  Serial.print(cm);
  Serial.println(" см.");
  // Задержка между измерениями для корректной работы скеча
  delay(500);
  return cm;
}

// int receiveapp() // получение заказа с приложения
// {
//   if (Serial.available() and flagrcv == 1)
//   {
//     int data = Serial.read();
//     return data;
//   }
//   else
//   { return -1;}
// }

// String receiveras() // получение сигнала о распознавшихся грузах
// {
//   if (Serial.available() and flagrcv == 2)
//   {
//     String data = Serial.readString();
//     return data;
//   }
//   else
//   { return "";}
// }

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
