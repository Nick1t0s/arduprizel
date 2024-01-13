#define WIFI_SSID "ASUS21G"
#define WIFI_PASS "Asus164w"
#define BOT_TOKEN "6659027776:AAHCFUoVzs_dZltD2DXTffTEZD71wDbp0tY"

#include <FastBot.h>
FastBot bot(BOT_TOKEN);

#include <GyverOLED.h>
GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;

#include <SoftwareSerial.h>
SoftwareSerial mySerial(14, 12); // RX, TX
// сначала объявляем обработчик
// это может почти быть любая интерфейсная либа,
// например софтСериал на любой другой платформе

#include "GBUS.h"
GBUS bus(&mySerial, 3, 25);  // адрес 3, буфер 25 байт

// приёмная структура
// структура структур должна быть одинаковая
struct myStruct {
  float val_f;
  float val_f2;
  int val_i;   // а тут long, иначе всё сломается
  long val_l;
  byte val_b;
};

float f;
float f2;
int i;
long l;
byte b;


void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
  oled.init();        // инициализация
  oled.clear();       // очистка
  oled.setScale(2);   // масштаб текста (1..4)
  oled.home();        // курсор в 0,0
  oled.print("Conecting");
  oled.setCursor(0,2);
  oled.print("to Wi-Fi");
  oled.setCursor(0,4);
  connectWiFi();
  oled.home();
  oled.clear();
  oled.print("Conected");
  bot.attach(newMsg);
}

// обработчик сообщений
void newMsg(FB_msg& msg) {
  // выводим ID чата, имя юзера и текст сообщения
  if (msg.text == "/getData"){
    bot.sendMessage(String(f),msg.chatID);
    bot.sendMessage(String(f2),msg.chatID);
    bot.sendMessage(String(i),msg.chatID);

    bot.sendMessage(String(i),msg.chatID);
    bot.sendMessage(String(i),msg.chatID);
    bot.sendMessage("",msg.chatID);
    bot.sendMessage("",msg.chatID);
    
    bot.sendMessage("",msg.chatID);
    bot.sendMessage("",msg.chatID);
    bot.sendMessage("",msg.chatID);

  }
}

void loop() {
  // здесь принимаются данные
  // если это аппаратный сериал - слишком часто его опрашивать даже не нужно
  bus.tick();

  // приняли данные
  if (bus.gotData()) {
    myStruct data;
    bus.readData(data);
    f = data.val_f;
    f2 = data.val_f2;
    i = data.val_i;
    l = data.val_l;
    b = data.val_b;
    // выводим
    Serial.println(data.val_f);
    Serial.println(data.val_f2);
    Serial.println(data.val_i);
    Serial.println(data.val_l);
    Serial.println(data.val_b);
    Serial.println();
  }
  bot.tick();
}

void connectWiFi() {
  int abs=0;
  delay(2000);
//  Serial.println();
//  oled.print("Conecting");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    oled.print(".");
    abs+=1;
    if(abs>2){
      abs=0;
      delay(500);
      oled.home();
      oled.clear();
      oled.print("Conecting");
      oled.setCursor(0,2);
      oled.print("to Wi-Fi");
      oled.setCursor(0,4);
    }
    if (millis() > 15000) ESP.restart();
  }}