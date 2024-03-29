// отправляем структуру через SoftwareSerial
// отправляет esp8266 (этот скетч), принимает Ардуина
// Провод подключен к D2 ноды и D10 Ардуины

#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX
// ВНИМАНИЕ! Нужно указывать номера GPIO, а не D-пины
// на Node получается RX-D1, TX-D2

#include "GBUS.h"

// адрес 5, буфер 20 байт
GBUS bus(&mySerial, 5, 20);

// структура для отправки
// БУДЬ ВНИМАТЕЛЕН, ЛЮБИТЕЛЬ ESP8266!!
// Тут данные кодируются хрен пойми как, компилятор "не смог"
// сначала располагай тяжёлые типы данных (float, int, long)
// РАСПОЛАГАЙ БАЙТЫ В КОНЦЕ СТРУКТУРЫ!
// int тут занимает 4 байта, так что на Arduino его нужно принимать как long!!!
// структура структур должна быть одинаковая
struct myStruct {
  float val_f;
  float val_f2;
  long val_i;
  long val_l;
  byte val_b;
};

void setup() {
  // родной сериал открываю для наблюдения за процессом
  Serial.begin(9600);
  // этот сериал будет принимать данные
  // мы указали его как обработчик
  mySerial.begin(9600);
}

void loop() {
  myStruct data;
  // забиваем данные
  data.val_f = 12.34;
  data.val_f2 = 56.78;
  data.val_i = 1234;
  data.val_l = 123456;
  data.val_b = 12;
  // отправляем на адрес 3
  bus.sendData(3, data);
  Serial.println("transmitting");
  Serial.println(analogRead(A0));
  delay(2000);

  // tick() тут не нужен! Он занимается только приёмом данных
  // отправка делается так, как реализовано в используемой либе интерфейса
}
