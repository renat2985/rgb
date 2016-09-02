/*
 * Arduino IDE 1.6.5
 * ArduinoJson 5.2.0
 */
#include <ESP8266WiFi.h>        //Содержится в пакете
#include <ESP8266WebServer.h>   //Содержится в пакете
#include <ESP8266SSDP.h>        //Содержится в пакете
#include <FS.h>                 //Содержится в пакете
#include <time.h>               //Содержится в пакете
#include <Ticker.h>             //Содержится в пакете
#include <WiFiUdp.h>            //Содержится в пакете
#include <ESP8266HTTPUpdateServer.h> //Содержится в пакете
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>

// Web интерфейс для устройства
ESP8266WebServer HTTP(80);
ESP8266HTTPUpdateServer httpUpdater;
// Для файловой системы
File fsUploadFile;
// Для сервопривода
//Servo myled;
// Для тикера
Ticker tickerSetLow;
Ticker tickerAlert;

// Кнопка управления
#define Tach0 0

// 2811 на ноге в количестве
#define led_pin 2
#define led_num 2
#define buzer_pin 3
Adafruit_NeoPixel strip = Adafruit_NeoPixel(led_num, led_pin, NEO_GRB + NEO_KHZ800);
// Определяем переменные

String _ssid     = "WiFi"; // Для хранения SSID
String _password = "Pass"; // Для хранения пароля сети
String _ssidAP = "RGB05";   // SSID AP точки доступа
String _passwordAP = ""; // пароль точки доступа
String XML;              // формирование XML
String _setAP ="1";           // AP включен
String SSDP_Name = "jalousie";      // SSDP
String times1 = "00:00:00";      // Таймер 1
String times2 = "00:00:00";    // Таймер 2
String Devices = "";    // IP адреса устройств в сети
int timezone = 3;        // часовой пояс GTM
int TimeLed = 10;  // Время работы LED
String kolibrTime = "03:00:00"; // Время колибровки часов
volatile int chaingtime = LOW;
volatile int chaing = LOW;
volatile int chaing1 = LOW;
int state0 = 0;
int r=0;
int g=0;
int b=0;
int t=0;
unsigned int localPort = 2390;
unsigned int ssdpPort = 1900;

// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;

void setup() {
 //Serial.begin(115200);
 pinMode(Tach0, INPUT);
 pinMode(led_pin, OUTPUT);
 pinMode(buzer_pin, OUTPUT);
 //Serial.println("");
 // Параметры памяти ESP справочно можно закаментировать
 CheckFlashConfig();
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
}

void loop() {
 HTTP.handleClient();
 delay(1);
 handleUDP();
 if (chaing && !chaing1) {
  noInterrupts();
  switch (state0) {
   case 0:
   LedON(r, g,  b);
   chaing=!chaing;
   state0=1;
    break;
   case 1:
   LedON(0, 0,  0);
   chaing=!chaing;
   state0=0;
    break;
  }
  interrupts();
 }
 if (chaingtime) {
  Time_init(timezone);
  chaingtime=0;
 }
}

// Вызывается каждую секунду в обход основного циклу.
void alert() {
 String Time=XmlTime();
 if (times1.compareTo(Time) == 0) {
 Time01();
 }
 if (times2.compareTo(Time) == 0) {
 Time01();
 }
 if (kolibrTime.compareTo(Time) == 0) {
  chaingtime=1;
 }
}
