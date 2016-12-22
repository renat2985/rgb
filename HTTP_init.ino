void handle_wifiScan() {
  int n = WiFi.scanNetworks();
  String wifiScan = "[";
  if (n == 0)
    wifiScan = "{\"ssid\":\"none\"}";
  else
  {
    for (int i = 0; i < n - 1; ++i)
    {
      wifiScan += "{";
      wifiScan += "\"ssid\":\"";
      wifiScan += WiFi.SSID(i);
      wifiScan += "\",";
      wifiScan += "\"dbm\":";
      wifiScan += WiFi.RSSI(i);
      wifiScan += ",";
      wifiScan += "\"pass\":\"";
      wifiScan += (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? "" : "*";
      //wifiScan += WiFi.encryptionType(i);
      wifiScan += "\"}";
      if (i != n - 2) wifiScan += ",";
      delay(10);
    }
    wifiScan += "]";
  }
  HTTP.send(200, "text/json", wifiScan);
}

void webUpdateSpiffs() {
  String refresh = "<html><head><meta http-equiv=\"refresh\" content=\"1;http://";
  refresh += WiFi.localIP().toString();
  refresh += "\"></head></html>";
  HTTP.send(200, "text/html", refresh);
  t_httpUpdate_return ret = ESPhttpUpdate.updateSpiffs("http://backup.privet.lv/rgb_spiffs_1m_256k.bin");
  saveConfig();
}


// Перезагрузка модуля
void handle_Restart() {
  String restart = HTTP.arg("device");
  if (restart == "ok") {                         // Если значение равно Ок
    HTTP.send(200, "text / plain", "Reset OK"); // Oтправляем ответ Reset OK
    ESP.restart();                                // перезагружаем модуль
  }
  else {                                        // иначе
    HTTP.send(200, "text / plain", "No Reset"); // Oтправляем ответ No Reset
  }
}

// Меняет флаг для включения выключения Led
void LedActiv() {
  chaing = 1;
  sound(buzer_pin, volume, 1000, 100);
  HTTP.send(200, "text/plain", "OK");
}

// Сохраняет все настройки в файле
void handle_saveConfig() {
  saveConfig();
  HTTP.send(200, "text/plain", "OK");
}

// Время вращения сервопривода
void handle_TimeLed() {
  TimeLed = HTTP.arg("t").toInt();
  saveConfig();
  //sound(buzer_pin, volume, 1000, 100);
  HTTP.send(200, "text/plain", "OK");
}

// Установка времянной зоны
void handle_TimeZone() {
  timezone = HTTP.arg("timezone").toInt();
  Time_init(timezone);
  saveConfig();
  HTTP.send(200, "text/plain", "OK");
}
// Установка языка
void handle_SetLeng() {
  Language = HTTP.arg("set");
  saveConfig();
  HTTP.send(200, "text/plain", "OK");
}
// Установка параметров сети
void handle_Set_Ssid() {
  _ssid = HTTP.arg("ssid");
  _password = HTTP.arg("password");
  saveConfig();
  HTTP.send(200, "text/plain", "OK");
}
// Установка параметров сети
void handle_ddns() {
  DDNS = HTTP.arg("url");
  DDNSName = HTTP.arg("wanurl");
  DDNSPort = HTTP.arg("wanport").toInt();
  //Serial.println(HTTP.arg("url"));
  //Serial.println(HTTP.arg("wanurl"));
  ip_wan();
  saveConfig();
  HTTP.send(200, "text/plain", "OK");
}

// Установка параметров сети
void handle_Set_Ssdp() {
  SSDP_Name = HTTP.arg("ssdp");
  saveConfig();
  HTTP.send(200, "text/plain", "OK");
}

//Установка параметров точки доступа
void handle_Set_Ssidap() {
  _ssidAP = HTTP.arg("ssidAP");
  _passwordAP = HTTP.arg("passwordAP");
  if (HTTP.arg("onOffAP") == "true") {
    _setAP = "1";
  } else {
    _setAP = "0";
  }
  saveConfig();
  HTTP.send(200, "text/plain", "OK");
}

//Время из сети
void handle_Time() {
  Time_init(timezone);
  String Time = XmlTime();
  HTTP.send(200, "text/plain", "Время синхронизовано: " + Time);
}

//Таймер 1
void handle_Time_1() {
  times1 = HTTP.arg("time1");
  saveConfig();
  HTTP.send(200, "text/plain", "OK");
}

//Таймер 2
void handle_Time_2() {
  times2 = HTTP.arg("time2");
  saveConfig();
  HTTP.send(200, "text/plain", "OK");
}

void HTTP_init(void) {
  // SSDP дескриптор
  HTTP.on("/description.xml", HTTP_GET, []() {
    SSDP.schema(HTTP.client());
  });
  // Добавляем функцию Update для перезаписи прошивки по WiFi при 1М(256K SPIFFS) и выше
  httpUpdater.setup(&HTTP);

  HTTP.on("/webupdatespiffs", webUpdateSpiffs);                // Обнавление FS из интернет
  HTTP.on("/restartWiFi", RestartWiFi);                // Переплдключение WiFi при первом старте
  HTTP.serveStatic("/css/", SPIFFS, "/css/", "max-age=31536000"); // кеширование на 1 год
  HTTP.serveStatic("/js/", SPIFFS, "/js/", "max-age=31536000"); // кеширование на 1 год
  HTTP.serveStatic("/img/", SPIFFS, "/img/", "max-age=31536000"); // кеширование на 1 год
  //HTTP.serveStatic("/lang/", SPIFFS, "/lang/", "max-age=31536000"); // кеширование на 1 год
  HTTP.on("/led", LedActiv);                // задать цвет ленты и включить.
  HTTP.on("/TimeLed", handle_TimeLed);      // установка времени работы светодиодов
  HTTP.on("/wifiscan.json", handle_wifiScan);      // сканирование ssid
  HTTP.on("/TimeZone", handle_TimeZone);    // Установка времянной зоны
  HTTP.on("/Time", handle_Time);            // Синхронизировать время из сети
  HTTP.on("/times1", handle_Time_1);        // Установить время 1
  HTTP.on("/times2", handle_Time_2);        // Установить время 2
  HTTP.on("/ssdp", handle_Set_Ssdp);        // Установить имя устройства
  HTTP.on("/ssid", handle_Set_Ssid);        // Установить имя и пароль роутера
  HTTP.on("/ssidap", handle_Set_Ssidap);    // Установить имя и пароль для точки доступа
  HTTP.on("/Save", handle_saveConfig);      // Сохранить настройки в файл
  HTTP.on("/configs.json", handle_Configs); // формирование config_xml страницы для передачи данных в web интерфейс
  HTTP.on("/iplocation.json", handle_Iplocation);  // формирование iplocation_xml страницы для передачи данных в web интерфейс
  HTTP.on("/restart", handle_Restart);               // Перезагрузка модуля
  HTTP.on("/lang.json", handle_Leng);               // Установить язык
  HTTP.on("/ddns", handle_ddns);               // Установить DDNS
  HTTP.on("/lang", handle_SetLeng);               // Установить язык
  HTTP.on("/mdules", handle_mdules);               // Установить язык
   // Запускаем HTTP сервер
  // HTTP.sendHeader("Cache-Control","max-age=2592000, must-revalidate");
  //HTTP.on("/devices", inquirySSDP);         // Блок для
  // Запускаем HTTP сервер
  HTTP.begin();
  HTTPWAN.begin();
}

// Получение текущего времени
String XmlTime(void) {
  String Time = ""; // Строка для результатов времени
  int i = 0; // Здесь будем хранить позицию первого символа :
  time_t now = time(nullptr); // получаем времяс помощью библиотеки time.h
  Time += ctime(&now); // Преобразуем время в строку формата
  i = Time.indexOf(":"); //Ишем позицию первого символа :
  Time = Time.substring(i - 2, i + 6); // Выделяем из строки 2 символа перед символом : и 6 символов после
  return Time; // Возврашаем полученное время
}

void handle_Configs() {
  String json = "{";
  // Имя DDNS
  json += "\"DDNS\":\"";
  json += DDNS;
  // Имя DDNSName
  json += "\",\"DDNSName\":\"";
  json += DDNSName;
  // Имя DDNSPort
  json += "\",\"DDNSPort\":\"";
  json += DDNSPort;
  // Имя SSDP
  json += "\",\"SSDP\":\"";
  json += SSDP_Name;
  // Имя сети
  json += "\",\"ssid\":\"";
  json += _ssid;
  // Пароль сети
  json += "\",\"password\":\"";
  json += _password;
  // Имя точки доступа
  json += "\",\"ssidAP\":\"";
  json += _ssidAP;
  // Пароль точки доступа
  json += "\",\"passwordAP\":\"";
  json += _passwordAP;
  // Времянная зона
  json += "\",\"timezone\":\"";
  json += timezone;
  //  Время работы
  json += "\",\"timeled\":\"";
  json += TimeLed;
  // Время 1
  json += "\",\"times1\":\"";
  json += times1;
  // Время 2
  json += "\",\"times2\":\"";
  json += times2;
  // Текущее время
  json += "\",\"time\":\"";
  json += XmlTime();
  // Статус
  json += "\",\"state\":\"";
  json += state0;
  // Язык
  json += "\",\"lang\":\"";
  if (Language == NULL) {
    json += "ru";
  } else {
    json += Language;
  }
  //RGB
  json += "\",\"color\":\"";
  json += color;
  json += "\"}";
  HTTP.send(200, "text/json", json);
}

void handle_Iplocation() {
  inquirySSDP();
  String json = "";
  //Serial.println(Devices);
  if (Devices != "") {
    json = Devices;
    json += ",";
  }
  json +=mdules();

  //Serial.println(json);
  HTTP.send(200, "text/json", "[" + json + "]");
  Devices="";
}

void handle_mdules() {
  HTTP.send(200, "text/json", mdules());
}

String mdules() {
  String json = "";
  int j = a - 1;
  for (int i = 0; i <= j; i++) {
    json += "{\"ip\":\"";
    json += WiFi.localIP().toString();
    json += "\",\"module\":\"";
    json += module[i];
    //Serial.println(module[i]);
    json += "\"";
    json += "}";
    if (i != j) json += ",";
  }
  return json;
}

void handle_Leng() {
  HTTP.send(200, "text/json", Lang);
}

