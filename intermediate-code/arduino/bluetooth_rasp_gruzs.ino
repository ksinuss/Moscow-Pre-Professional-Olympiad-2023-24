#include <Wire.h>

String gruz;
String vint = "vint";
String gaik = "gaika";
String shab = "shaiba";
String shpl = "shpilka";
String pdsh = "podshipnik";
String napr = "napravlyash";
String val = "val";
String dvig = "dvigatel";
String dtch = "datchik";

int vint0;
int gaik0;
int shab0;
int shpl0;
int pdsh0;
int napr0;
int val0;
int dvig0;
int dtch0;

int bt = 100;

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    bt = Serial.read();
    Serial.println(bt);
  }
  if (bt == 2) {
    vint0 = 1;
  }
  if (bt == 3) {
    gaik0 = 1;
  }
  if (bt == 4) {
    shab0 = 1;
  }
  if (bt == 5) {
    shpl0 = 1;
  }
  if (bt == 6) {
    pdsh0 = 1;
  }
  if (bt == 7) {
    napr0 = 1;
  }
  if (bt == 8) {
    val0 = 1;
  }
  if (bt == 9) {
    dvig0 = 1;
  }
  if (bt == 10) {
    dtch0 = 1;
  }
  if (bt == 1) {
    
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    // Читаем полученные данные и сохраняем их в переменной
    String data = Serial.readString();
    // gruz = gruzy[data];
    // Отправляем ответ обратно в Serial порт
    // Serial.println("Получено: " + data);
    if (data == "1") {
      gruz = vint;
      if (vint0 == 1) {
        Serial.println(gruz);
        digitalWrite(13, HIGH);   // зажигаем светодиод
        delay(4000);              // ждем секунду
        digitalWrite(13, LOW);    // выключаем светодиод
        delay(1000);
      }
    }
    if (data == "2") {
      gruz = gaik;
      if (gaik0 == 1) {
        Serial.println(gruz);
        digitalWrite(13, HIGH);   // зажигаем светодиод
        delay(4000);              // ждем секунду
        digitalWrite(13, LOW);    // выключаем светодиод
        delay(1000);
      }
    }
    if (data == "3") {
      gruz = shab;
      if (shab0 == 1) {
        Serial.println(gruz);
        digitalWrite(13, HIGH);   // зажигаем светодиод
        delay(4000);              // ждем секунду
        digitalWrite(13, LOW);    // выключаем светодиод
        delay(1000);
      }
    }
    if (data == "4") {
      gruz = shpl;
      if (shpl0 == 1) {
        Serial.println(gruz);
        digitalWrite(13, HIGH);   // зажигаем светодиод
        delay(4000);              // ждем секунду
        digitalWrite(13, LOW);    // выключаем светодиод
        delay(1000);
      }
    }
    if (data == "5") {
      gruz = pdsh;
      if (pdsh0 == 1) {
        Serial.println(gruz);
        digitalWrite(13, HIGH);   // зажигаем светодиод
        delay(4000);              // ждем секунду
        digitalWrite(13, LOW);    // выключаем светодиод
        delay(1000);
      }
    }
    if (data == "6") {
      gruz = napr;
      if (napr0 == 1) {
        Serial.println(gruz);
        digitalWrite(13, HIGH);   // зажигаем светодиод
        delay(4000);              // ждем секунду
        digitalWrite(13, LOW);    // выключаем светодиод
        delay(1000);
      }
    }
    if (data == "7") {
      gruz = val;
      if (val0 == 1) {
        Serial.println(gruz);
        digitalWrite(13, HIGH);   // зажигаем светодиод
        delay(4000);              // ждем секунду
        digitalWrite(13, LOW);    // выключаем светодиод
        delay(1000);
      }
    }
    if (data == "8") {
      gruz = dvig;
      if (dvig0 == 1) {
        Serial.println(gruz);
        digitalWrite(13, HIGH);   // зажигаем светодиод
        delay(4000);              // ждем секунду
        digitalWrite(13, LOW);    // выключаем светодиод
        delay(1000);
      }
    }
    if (data == "9") {
      gruz = dtch;
      if (dtch0 == 1) {
        Serial.println(gruz);
        digitalWrite(13, HIGH);   // зажигаем светодиод
        delay(4000);              // ждем секунду
        digitalWrite(13, LOW);    // выключаем светодиод
        delay(1000);
      }
    }

  // if (gruz != "") {
  //   Serial.println(gruz);
  //   digitalWrite(13, HIGH);   // зажигаем светодиод
  //   delay(5000);              // ждем секунду
  //   digitalWrite(13, LOW);    // выключаем светодиод
  //   delay(1000);
  //   }
  }
  }

  if (bt == 0) {
    digitalWrite(13, HIGH);   // зажигаем светодиод
    delay(100);              // ждем секунду
    digitalWrite(13, LOW);    // выключаем светодиод
    delay(100);
    digitalWrite(13, HIGH);   // зажигаем светодиод
    delay(100);              // ждем секунду
    digitalWrite(13, LOW);    // выключаем светодиод
    delay(100);
  }
}

