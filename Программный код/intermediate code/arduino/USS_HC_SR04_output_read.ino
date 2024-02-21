#define PIN_TRIG 14 //10 - 16, 14 - 16
#define PIN_ECHO 15 //11, 15

long duration, cm;

void setup() {
  // Инициализируем взаимодействие по последовательному порту
  Serial.begin (9600);
  //Определяем вводы и выводы - УЗД
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT); 
}

void loop() {  
  // Сначала генерируем короткий импульс длительностью 2-5 микросекунд.
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG, HIGH);
  // Выставив высокий уровень сигнала, ждем около 10 микросекунд. В этот момент датчик будет посылать сигналы с частотой 40 КГц.
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  //  Время задержки акустического сигнала на эхолокаторе.
  duration = pulseIn(PIN_ECHO, HIGH);
  // Теперь осталось преобразовать время в расстояние
  cm = (duration / 2) / 29.1;
  Serial.print("Расстояние до объекта: ");
  Serial.print(cm);
  Serial.println(" см.");
  // Задержка между измерениями для корректной работы скеча
  delay(500);
}

// start - 3;
// finish - 65;

void yield() {}

// 1 - 2
// 2 - 8
// 3 - 16
// 4 - 24
// 5 - 32
// 6 - 40
// 7 - 47/48
// 8 - 56
// 9 - 62/63
// n - 70/71 + delay(100)
