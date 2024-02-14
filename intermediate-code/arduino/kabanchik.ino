//be happy

// инициализация для дисплея
#include <OLED_I2C.h>
extern uint8_t SmallFont[];
OLED myOLED(SDA, SCL, 8);
String del = "                       ";
String scan = "SCANNING... ";
String fnsh = "FINISH! ";
String gruz = " ";
int flagol;

// инициализация для шаговых моторов
#include <Stepper_28BYJ_48.h>
Stepper_28BYJ_48 stepperin (11, 10, 9, 8);
Stepper_28BYJ_48 stepperup (7, 6, 5, 4);
int flagin;
int flagup;
int back;

// инициализация для сервопривода
#include <Servo.h>
Servo servo; // create servo object to control a servo
int pos; // variable to store the servo position
int take;
int drop;

// инициализация для узд
#define PIN_TRIG 3
#define PIN_ECHO 2
int penki[] = {7, 15, 23, 31, 39, 46, 54, 61};
long duration, cm;
int cmp, cmb;
byte i = 0;
int cell;

// инициализация для икд
#define sensor A0
int vl, kop;
int n = 4;

// инициализация переменных для дальнейшего получения информации о грузах (распознавание)
String data = "";
int flagrcv = 1;
int finish = -1;
int count;
int flag;

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
  delay(100); // start yield
  
  if (flagrcv == 1)
  { data = receive();}

  // начинаем работу устройства
  if (data == "2" or data == "3")
  { 
    if (data == "2") // два груза в заказе
    { flag = 2;}
    if (data == "3") // три груза в заказе
    { flag = 3;}
    finish = 0;
    cell = penki[i];
    vl = 0;
    flagin = 1;
    flagol = 2;
    delay(200);
    flagol = 0;
    flagrcv = 1;
    data = "";
  }
  // завершаем работу устройства
  if (data == "0")
  { 
    int y = 25;
    int x = CENTER;
    myOLED.print(del, x, y);
    myOLED.update();
    flagol = 0;
    flagin = 0;
    flagup = 0;
    flagrcv = 0;
  }

//  if (data == "n" and take == 0)
//  { flagin = 1;}

  // груз распознан
  if (data.length() > 1)
  { 
    gruz = data;
    take = 1;
    flagol = 1;
    delay(100);
    flagol = 0;
    flagrcv = 0;
    data = "";
  }

  cm = kabanchik(); // считываем показания узд
  if (kop == 1)
  { vl = baton();} // считываем показания икд (для перемещения к накопителю)
  
  // перемещаемся от ячейки до ячейки
  if (cm >= cell-1 and cm <= cell+1 and back == 0 and kop == 0 and take == 0 and finish == 0)
  {
    if (i < 9)
    { 
      flagin = 0;
      flagrcv = 1;
      delay(1000);
      i++;
      cell = penki[i];
      if (take == 0)
      { flagin = 1;}
    }
    if (i == 8)
    {
      // flagin = 0;
      // delay(500);
      // kop = 1;
      // flagin = 1;
      delay(100);
      flagin = 0;
      back = 1;
      i = 0;
      flagin = 2;
    }
  }
  
  // приехали к накопителю
  if (vl <= n+1 and vl >= n-1)
  { 
    flagin = 0;
    kop = 0;
    delay(100);
    drop = 1;
  }

  // приехали на (базу) к месту, где остановились/распознали последний груз
  if ((cm > 100 or (cmb-2 <= cm and cm <= cmb+2)) and back == 1) 
  {
    flagin = 0;
    delay(500);
    Serial.println("t");
    back = 0;
    flagin = 1;
  }

  if (take == 1) // захват груза
  {
    flagin = 0;
    flagin = 2;
    delay(300);
    flagin = 0;
    cmb = kabanchik();
    // forward paw
    flagup = 1;
    delay(5000);
    flagup = 0;
    // servo
    for (pos = 77; pos <= 90; pos += 1) { // close (захват)
      // in steps of 1 degree
      servo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(50);                     // waits for the servo to reach the position
    }
    delay(2000);
    // back paw
    flagup = 2;
    delay(5000);
    flagup = 0;
    flagrcv = 0;
    take = 0;
    data = "";
    flagin = 1;
    kop = 1;
  }

  if (drop == 1) // скидываем груз
  {
    flagin = 0;
    flagup = 1;
    delay(3000);
    flagup = 0;
    for (pos = 103; pos >= 90; pos -= 1)  // open (скинуть)
    {
      servo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(50);                     // waits for the servo to reach the position
    }
    delay(2000);
    flagup = 2;
    delay(3000);
    flagup = 0;
    count++;
    if (count == flag)
    { 
      flagol = 3;
      delay(200);
      flagol = 0;
      flagin = 0;
      back = 0;
      Serial.println("q");
    }
    else
    {
      flagin = 2;
      back = 1;
    }
    drop = 0;
    vl = 0;
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
  int y = 25;
  int x = CENTER;
  if (flagol == 1)
  {
    myOLED.print(del, x, y);
    myOLED.update();
//    String text = gruz;
//    String part = getPart(text, ' ', 0);
//    Serial.println(part2); // p2
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
  {
    stepperin.step(1);
    // delay(400000);
  }
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
//   Serial.print("Расстояние до объекта: ");
//   Serial.print(cm);
//   Serial.println(" см.");
  // Задержка между измерениями для корректной работы скеча
  delay(300);
  return cm;
}

int baton() // infrared sensor
{
  float volts = analogRead(sensor)*0.0048828125;  // значение сенсора * (5/1024)
  int distance = 13*pow(volts, -1); // выяснил методом подбора из даташита
  delay(500); // пауза для того, чтобы различать данные
  // if (distance <= 80) //ставим ограничение для защиты от ложных срабатываний
  // { 
  //   Serial.println(distance);  // пишем данные в Serial порт
  // }
  return distance;
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

//String getPart(String text, char del, int index)
//{
//  int found = 0;
//  int sInd[] = {0, -1};
//  int mInd = text.length()-1;
//
//  for(int i=0; i<=mInd && found<=index; i++){
//    if(text.charAt(i)==del || i==mInd){
//        found++;
//        sInd[0] = sInd[1]+1;
//        sInd[1] = (i == mInd) ? i+1 : i;
//    }
//  }
//
//  return found>index ? text.substring(sInd[0], sInd[1]) : "";
//}
