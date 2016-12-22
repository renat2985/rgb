#include <ESP8266WiFi.h>             //Содержится в пакете
#include <ESP8266WebServer.h>        //Содержится в пакете
#include <ESP8266SSDP.h>             //Содержится в пакете
#include <FS.h>                      //Содержится в пакете
#include <time.h>                    //Содержится в пакете
#include <Ticker.h>                  //Содержится в пакете
#include <WiFiUdp.h>                 //Содержится в пакете
#include <ESP8266HTTPUpdateServer.h> //Содержится в пакете
#include <ESP8266httpUpdate.h>
#include <ESP8266HTTPClient.h>
#include <DNSServer.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>
#include <WS2812FX.h>                //https://github.com/kitesurfer1404/WS2812FX

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 4, 1);
DNSServer dnsServer;
int DDNSPort = 8080; // порт для обращение к устройству с wan
// Web интерфейс для устройства
ESP8266WebServer HTTP(80);
ESP8266WebServer HTTPWAN(DDNSPort);
ESP8266HTTPUpdateServer httpUpdater;
// Для файловой системы
File fsUploadFile;
// Для сервопривода
//Servo myled;
// Для тикера
Ticker tickerSetLow;
Ticker tickerAlert;
Ticker tickerBizz;

// Кнопка управления
#define Tach0 0

// 2811 на ноге в количестве
#define buzer_pin 3
#define LED_COUNT 15 //Количество лед огней
#define LED_PIN 2

#define DEFAULT_COLOR 0xff6600
#define DEFAULT_BRIGHTNESS 255
#define DEFAULT_SPEED 100
#define DEFAULT_MODE FX_MODE_STATIC

#define BRIGHTNESS_STEP 15              // in/decrease brightness by this amount per click
#define SPEED_STEP 10                   // in/decrease brightness by this amount per click

String modes = "";
WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Определяем переменные
String module[] = {"rbg"};
//,"sonoff","jalousie"};
// Общие настройки модуля
String _ssid     = "WiFi";      // Для хранения SSID
String _password = "Pass";      // Для хранения пароля сети
String _ssidAP = "RGB05";       // SSID AP точки доступа
String _passwordAP = "";        // пароль точки доступа
String _setAP = "1";            // AP включен
String SSDP_Name = "jalousie";  // SSDP
String Language = "ru";         // язык web интерфейса
String Lang = "";  // файлы языка web интерфейса
int timezone = 3;               // часовой пояс GTM
String kolibrTime = "03:00:00"; // Время колибровки часов
volatile int chaingtime = LOW;
// Переменные для обнаружения модулей
 String Devices = "";            // IP адреса устройств в сети
// Переменные для таймеров
String times1 = "";             // Таймер 1
String times2 = "";             // Таймер 2
int TimeLed = 60;               // Время работы будильника
// Переменные для DDNS
String DDNS = "";               // url страницы тестирования WanIP
String DDNSName = "";           // адрес сайта DDNS

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
  Serial.begin(115200);
  pinMode(Tach0, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(buzer_pin, OUTPUT);
  digitalWrite(buzer_pin, 1);
  // Serial.println("");
  // Включаем работу с файловой системой
  FS_init();
  // Загружаем настройки из файла
  loadConfig();
  // Подключаем RGB
  initRGB();
  // Кнопка будет работать по прерыванию
  attachInterrupt(Tach0, Tach_0, FALLING);
  //Запускаем WIFI
  WIFIAP_Client();
  // Закускаем UDP
  udp.begin(localPort);
  //udp.beginMulticast(WiFi.localIP(), ssdpAdress1, ssdpPort);
  //Serial.print("Local port: ");
  //Serial.println(udp.localPort());
  //настраиваем HTTP интерфейс
  HTTP_init();
  //Serial.println("HTTP Ready!");
  //запускаем SSDP сервис
  SSDP_init();
  //Serial.println("SSDP Ready!");
  // Включаем время из сети
  Time_init(timezone);
  // Будет выполняться каждую секунду проверяя будильники
  tickerAlert.attach(1, alert);
  ip_wan();
}

void loop() {
  dnsServer.processNextRequest();
  HTTP.handleClient();
  delay(1);
  HTTPWAN.handleClient();
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
        analogWrite(buzer_pin, 0);
        digitalWrite(buzer_pin, 1);
        state0 = 0;
        break;
    }
    interrupts();
  }
  if (chaingtime) {
    Time_init(timezone);
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
  Time = Time.substring(3, 8); // Выделяем из строки минуты секунды
  // В 15, 30, 45 минут каждого часа идет запрос на сервер DDNS
  if ((Time == "00:00" || Time == "15:00" || Time == "30:00" || Time == "45:00") && DDNS != "") {
    ip_wan();
  }
  if (kolibrTime.compareTo(Time) == 0) {
    chaingtime = 1;
  }
}


