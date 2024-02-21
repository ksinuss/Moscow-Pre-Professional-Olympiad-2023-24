// #include <map>
// map <string, string> gruzy = {
//   {"1", "vint"},
//   {"2", "gaika"},
//   {"3", "shaiba"},
//   {"4", "shpilka"},
//   {"5", "podshipnik"},
//   {"6", "napravlyash"},
//   {"7", "val"},
//   {"8", "dvigatel"},
//   {"9", "datchik"}
// };

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


void setup() {
  vint = 1;
  shab = 1;
  dtch = 1;
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    // Читаем полученные данные и сохраняем их в переменной
    String data = Serial.readString();
    // gruz = gruzy[data];
    // Отправляем ответ обратно в Serial порт
    // Serial.println("Получено: " + data);
    if (data == "1") {
      gruz = vint;
      if (vint0 == 1) {}
    }
    if (data == "2") {
      gruz = gaik;
      if (gaik0 == 1) {}
    }
    if (data == "3") {
      gruz = shab;
      if (shab0 == 1) {}
    }
    if (data == "4") {
      gruz = shpl;
      if (shpl0 == 1) {}
    }
    if (data == "5") {
      gruz = pdsh;
      if (pdsh0 == 1) {}
    }
    if (data == "6") {
      gruz = napr;
      if (napr0 == 1) {}
    }
    if (data == "7") {
      gruz = val;
      if (val0 == 1) {}
    }
    if (data == "8") {
      gruz = dvig;
      if (dvig0 == 1) {}
    }
    if (data == "9") {
      gruz = dtch;
      if (dtch0 == 1) {}
    }

  if (gruz != "") {
    Serial.println(gruz);
    digitalWrite(13, HIGH);   // зажигаем светодиод
    delay(5000);              // ждем секунду
    digitalWrite(13, LOW);    // выключаем светодиод
    delay(1000);
    }
  }

}
