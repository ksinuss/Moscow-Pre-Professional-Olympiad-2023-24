// инициализация для шаговых моторов
#include <Stepper_28BYJ_48.h>
Stepper_28BYJ_48 stepperin (11, 10, 9, 8);
int back;
int flagin;

// инициализация для узд
#define PIN_TRIG 3
#define PIN_ECHO 2
long duration, cm;
int cmp, cmb;
int penki1[] = {7, 15, 23, 31, 39, 46, 54, 61};
//int n = 64; // 70-71 + delay(100)
byte i = 0;

// инициализация для irc
#define sensor A0 // устанавливаем аналоговый вход на Arduino
int vl, kop;
int n = 4;

int cell;
int llec;

void setup() {
  Serial.begin(9600);

  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  delay(5000);
}

void loop() 
{
  delay(100); // start yield
  
  cm = kabanchik(); // считываем показания узд
  if (kop == 1)
  { vl = baton();} // считываем показания икд
  
  if (cm > 100)
  { 
    Serial.println("ux");
    flagin = 0;
    kop = 0;
    vl = 0;
    cell = penki1[i];
    delay(1000);
    flagin = 1;
    back = 0;
  }
  
//  cmp = cm; // предыдущее значение узд для дальнейшего сравнения

  if (vl <= n+1 and vl >= n-1 and back == 0)
  { 
    flagin = 0;
    kop = 0;
    delay(3000);
    flagin = 2;
    back = 1;
    i = 0;
  }

  if (cm >= cell-1 and cm <= cell+1 and back == 0)
  {
    Serial.println(cm);
//    if (llec == n)
//    { 
//      Serial.println(cell);
//      Serial.println(llec);
//      Serial.println(n);
//      delay(50);
//      flagin = 0;
//      delay(1000);
//      back = 1;
//      flagin = 2;
//      i = 0;
//    }
    if (i < 9)
    { 
      flagin = 0;
      delay(1000);
      i++;
      cell = penki1[i];
      flagin = 1;
    }
    if (i == 8)
    {
      Serial.println(cm);
      Serial.println(vl);
      flagin = 0;
      delay(500);
//      llec = n;
      kop = 1;
      flagin = 1;
    }
  }
}

void yield() // выполнение функций независимо от loop
{
  stepin();
}

void stepin() // step motor in cart
{
  if (flagin == 1) 
  {
    stepperin.step(1);
  }
  if (flagin == 2) 
  {
    stepperin.step(-1);
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
  delay(300);
  return cm;
}

int baton() // irc
{
  float volts = analogRead(sensor)*0.0048828125;  // значение сенсора * (5/1024)
  int distance = 13*pow(volts, -1); // выяснил методом подбора из даташита
  delay(500); // пауза 1 секунда для того, чтобы различать данные
  if (distance <= 80) //ставим ограничение для защиты от ложных срабатываний
  { 
    Serial.println(distance);  // пишем данные в Serial порт
  }
  return distance;
}
