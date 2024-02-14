#define sensor A0 // устанавливаем аналоговый вход на Arduino

void setup() {
  Serial.begin(9600); // начинаем Serial соединение с компьютером
}

void loop() {
  
  // 5v
  float volts = analogRead(sensor)*0.0048828125;  // значение сенсора * (5/1024)
  int distance = 13*pow(volts, -1); // выяснил методом подбора из даташита
  delay(500); // пауза 1 секунда для того, чтобы различать данные
  
  if (distance <= 80){ //ставим ограничение для защиты от ложных срабатываний
    Serial.println(distance);   // пишем данные в Serial порт
  }
}

// 11 - n
// 8-9 - 9
// 13-14 - 8
// 18 - 7
