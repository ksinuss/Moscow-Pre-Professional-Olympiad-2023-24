//be happy

// инициализация для дисплея
#include <OLED_I2C.h>
OLED myOLED(SDA, SCL, 8);
extern uint8_t SmallFont[];
int flagol;
String gruz;
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

// инициализация для узд
#define PIN_TRIG 3
#define PIN_ECHO 2
long duration, cm;
int cmp, cmb;
int back;

// инициализация переменных для дальнейшего получения информации о грузах (распознавание)
int flagrcv = 1;
int finish;
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
  if (flagrcv == 1)
  { data = receive();}

  if (data =="1")
  { flagin = 1;}

  if (data == "a") 
  {
    gruz = vint;
    take = 1;
  }
  if (data == "b") 
  {
    gruz = gaik;
    take = 1;
  }
  if (data == "c") 
  {
    gruz = shab;
    take = 1;
  }
  if (data == "d") 
  {
    gruz = shpl;
    take = 1;
  }
  if (data == "e") 
  {
    gruz = pdsh;
    take = 1;
  }
  if (data == "f") 
  {
    gruz = napr;
    take = 1;
  }
  if (data == "g") 
  {
    gruz = val;
    take = 1;
  }
  if (data == "h") 
  {
    gruz = dvig;
    take = 1;
  }
  if (data == "i") 
  {
    gruz = dtch;
    take = 1;
  }
    
//  if (data == "a") 
//  {
//    gruz = "VINT ";
//    take = 1;
//  }
//  if (data == "b") 
//  {
//    gruz = "GAIKA ";
//    take = 1;
//  }
//  if (data == "c") 
//  {
//    gruz = "SHAIBA ";
//    take = 1;
//  }
//  if (data == "d") 
//  {
//    gruz = "SHPILKA ";
//    take = 1;
//  }
//  if (data == "e") 
//  {
//    gruz = "PODSHIPNIK ";
//    take = 1;
//  }
//  if (data == "f") 
//  {
//    gruz = "NAPRAVLYAUSHAYA ";
//    take = 1;
//  }
//  if (data == "g") 
//  {
//    gruz = "VAL ";
//    take = 1;
//  }
//  if (data == "h") 
//  {
//    gruz = "DVIGATEL ";
//    take = 1;
//  }
//  if (data == "i") 
//  {
//    gruz = "DATCHIK ";
//    take = 1;
//  }

  if (data == "k")
  { finish = 1;}
  if (data == "0")
  { 
    flagol = 0;
    flagin = 0;
    flagup = 0;
    flagrcv = 0;
  }
  
  if (take == 1) // захват груза
  {
    flagin = 0;
    flagol = 1;
    cmb = kabanchik();
    flagup = 1;
    delay(3000);
    flagup = 0;
    for (pos = 115; pos >= 90; pos -= 1) 
    {
      servo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(40);                     // waits 40ms for the servo to reach the position
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
  if (cm > 300 or (cmb-2 <= cm and cm <= cmb+2) and back == 1) // приехали на (базу) к месту, где остановились/распознали последний груз
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
    if (finish == 1)
    { 
      gruz = fnsh;
      flagin = 0;
      drop = 0;
    }
    else
    {
      flagin = 2;
      back = 1;
      drop = 0;
    }
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
