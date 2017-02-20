/*
 * esp8266 and WS2811/WS2812/NeoPixel LEDs (Arduino) https://github.com/renat2985/rgb
 * Arduino core for ESP8266 WiFi chip https://github.com/esp8266/Arduino
 * Arduino ESP8266 filesystem uploader https://github.com/esp8266/arduino-esp8266fs-plugin
 */
#include <ESP8266WiFi.h>             //Содержится в пакете
#include <ESP8266WebServer.h>        //Содержится в пакете
#include <ESP8266SSDP.h>             //Содержится в пакете
#include <FS.h>                      //Содержится в пакете
#include <time.h>                    //Содержится в пакете
#include <Ticker.h>                  //Содержится в пакете
#include <WiFiUdp.h>                 //Содержится в пакете
#include <ESP8266HTTPUpdateServer.h> //Содержится в пакете
#include <ESP8266httpUpdate.h>       //Содержится в пакете
#include <ESP8266HTTPClient.h>       //Содержится в пакете
#include <DNSServer.h>               //Содержится в пакете

#include <ArduinoJson.h>             //https://github.com/bblanchon/ArduinoJson
#include <Adafruit_NeoPixel.h>       //https://github.com/adafruit/Adafruit_NeoPixel
#include <WS2812FX.h>                //https://github.com/kitesurfer1404/WS2812FX

// Настройки DNS сервера и адреса точки в режиме AP
const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 4, 1);
DNSServer dnsServer;
// Web интерфейс для устройства
ESP8266WebServer HTTP(80);
//ESP8266WebServer HTTPWAN(ddnsPort);
ESP8266WebServer *HTTPWAN;
ESP8266HTTPUpdateServer httpUpdater;
// Для файловой системы
File fsUploadFile;
// Для тикера
Ticker tickerSetLow;
Ticker tickerAlert;
Ticker tickerBizz;

#define TACH_PIN 0    // Кнопка управления
#define BUZER_PIN 3   // Бузер
#define LED_PIN 2     // RGB лента
// If you use ESP8266 12 you can add
#define PIR_PIN 14    // RIR sensors

#define DEFAULT_COLOR 0xff6600
#define DEFAULT_BRIGHTNESS 255
#define DEFAULT_SPEED 100
#define DEFAULT_MODE FX_MODE_STATIC

#define BRIGHTNESS_STEP 15      // in/decrease brightness by this amount per click
#define SPEED_STEP 10           // in/decrease brightness by this amount per click
int ledCount = 15;              // Количество лед огней
WS2812FX ws2812fx = WS2812FX(ledCount, LED_PIN, NEO_GRB + NEO_KHZ800);

String modes = "";

// Определяем строку для json config
String jsonConfig = "";

// Определяем переменные
String module[]={"rgb", "pir"};
//,"sonoff","jalousie"};

// Общие настройки модуля
String ssidName     = "WiFi";      // Для хранения SSID
String ssidPass = "Pass";      // Для хранения пароля сети
String ssidApName = "RGB05";       // SSID AP точки доступа
String ssidApPass = "";        // пароль точки доступа
String ssdpName = "jalousie";  // SSDP
String Language = "ru";         // язык web интерфейса
String Lang = "";               // файлы языка web интерфейса
int timeZone = 3;               // часовой пояс GTM
String kolibrTime = "03:00:00"; // Время колибровки часов
volatile int chaingtime = LOW;
// Переменные для обнаружения модулей
String Devices = "";            // Поиск IP адресов устройств в сети
String DevicesList = "";            // IP адреса устройств в сети
// Переменные для таймеров
String times1 = "";             // Таймер 1
String times2 = "";             // Таймер 2
int timeLed = 60;               // Время работы будильника
// Переменные для ddns
String ddns = "";               // url страницы тестирования WanIP
String ddnsName = "";           // адрес сайта ddns
int ddnsPort = 8080;            // порт для обращение к устройству с wan
int pirTime = 0;                // 0 = PIR off; >1 = PIR on;

volatile int chaing = LOW;
volatile int chaing1 = LOW;
int volume = 512;// max =1023
int state0 = 0;
int t = 300;
int s = 5;
String color = "ff6600";

unsigned int localPort = 2390;
unsigned int ssdpPort = 1900;

// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;

void setup() {
 //Serial.begin(115200);
 pinMode(PIR_PIN, INPUT);
 pinMode(TACH_PIN, INPUT);
 pinMode(LED_PIN, OUTPUT);
 pinMode(BUZER_PIN, OUTPUT);
 digitalWrite(BUZER_PIN, 1);
 // Включаем работу с файловой системой
 FS_init();
 // Загружаем настройки из файла
 loadConfig();
 //Обновляем количество LED

 //Adafruit_NeoPixel ws2812fx = Adafruit_NeoPixel();
 //ws2812fx.updateLength(ledCount);
 //ws2812fx.updateType(NEO_GRB + NEO_KHZ800);
 //ws2812fx.setPin(PIR_PIN);

 HTTPWAN = new ESP8266WebServer(ddnsPort);
 // Подключаем RGB
 initRGB();
 // Кнопка будет работать по прерыванию
 attachInterrupt(TACH_PIN, Tach_0, FALLING);
 //Запускаем WIFI
 WIFIAP_Client();
 // Закускаем UDP
 udp.begin(localPort);
 //udp.beginMulticast(WiFi.localIP(), ssdpAdress1, ssdpPort);
 //настраиваем HTTP интерфейс
 HTTP_init();
 //запускаем SSDP сервис
 SSDP_init();
 // Включаем время из сети
 Time_init(timeZone);
 // Будет выполняться каждую секунду проверяя будильники
 tickerAlert.attach(1, alert);
 ip_wan();
}

void loop() {
 dnsServer.processNextRequest();
 HTTP.handleClient();
 delay(1);
 HTTPWAN->handleClient();
 delay(1);
 handleUDP();
 if (chaing && !chaing1) {
  noInterrupts();
  switch (state0) {
   case 0:
    chaing = !chaing;
    state0 = 1;
    ws2812fx.start();
    break;
   case 1:
    chaing = !chaing;
    state0 = 0;
    ws2812fx.stop();
    break;
   case 3:
    analogWrite(BUZER_PIN, 0);
    digitalWrite(BUZER_PIN, 1);
    state0 = 0;
    break;
  }
  interrupts();
 }
 if (chaingtime) {
  Time_init(timeZone);
  chaingtime = 0;
 }

 ws2812fx.service();
}

// Вызывается каждую секунду в обход основного цикла.
void alert() {
 String Time = XmlTime();
 if (times1.compareTo(Time) == 0) {
  alarm_clock();
 }
 if (times2.compareTo(Time) == 0) {
  alarm_clock();
 }
 if (kolibrTime.compareTo(Time) == 0) {
  chaingtime = 1;
 }
 if (pirTime > 0 && state0 == 0 && digitalRead(PIR_PIN)) {
  alarm_pir();
 }

 Time = Time.substring(3, 8); // Выделяем из строки минуты секунды
 // В 15, 30, 45 минут каждого часа идет запрос на сервер ddns
 if ((Time == "00:00" || Time == "15:00" || Time == "30:00" || Time == "45:00") && ddns != "") {
  ip_wan();
 }
}


