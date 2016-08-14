// Перезагрузка модуля
void handle_Restart() {
String restart=HTTP.arg("device");
 if (restart=="ok") ESP.restart();
}

// Меняет флаг для запуска
void LedActiv() {
 chaing = 1;
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
 HTTP.send(200, "text/plain", "OK");
}

// Установка времянной зоны
void handle_TimeZone() {
 timezone = HTTP.arg("timezone").toInt();
 Time_init(timezone);
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
 HTTP.on("/led", LedActiv);                // запуск мотора напровление храниться в переменной
 HTTP.on("/TimeLed", handle_TimeLed);      // установка времени вращения сервопривода
 HTTP.on("/TimeZone", handle_TimeZone);    // Установка времянной зоны
 HTTP.on("/Time", handle_Time);            // Синхронизировать время из сети
 HTTP.on("/times1", handle_Time_1);        // Установить время 1
 HTTP.on("/times2", handle_Time_2);        // Установить время 2
 HTTP.on("/ssdp", handle_Set_Ssdp);        // Установить имя устройства
 HTTP.on("/ssid", handle_Set_Ssid);        // Установить имя и пароль роутера
 HTTP.on("/ssidap", handle_Set_Ssidap);    // Установить имя и пароль для точки доступа
 HTTP.on("/Save", handle_saveConfig);      // Сохранить настройки в файл
 HTTP.on("/config.xml", handle_ConfigXML); // формирование config_xml страницы для передачи данных в web интерфейс
 HTTP.on("/iplocation.xml", handle_IplocationXML);  // формирование iplocation_xml страницы для передачи данных в web интерфейс
 HTTP.on("/block", handle_Block);                   // Блок для device.htm
 HTTP.on("/restart", handle_Restart);               // Перезагрузка модуля
 // Запускаем HTTP сервер
 // HTTP.sendHeader("Cache-Control","max-age=2592000, must-revalidate");
 HTTP.on("/devices", inquirySSDP);         // Блок для
 // Запускаем HTTP сервер
 HTTP.begin();
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

void handle_ConfigXML() {
 XML = "<?xml version='1.0'?>";
 XML += "<Donnees>";
 // Имя SSDP
 XML += "<SSDP>";
 XML += SSDP_Name;
 XML += "</SSDP>";
 // Статус AP
 XML += "<onOffAP>";
 XML += _setAP;
 XML += "</onOffAP>";
 // Имя сети
 XML += "<ssid>";
 XML += _ssid;
 XML += "</ssid>";
 // Пароль сети
 XML += "<password>";
 if (_password == NULL) {
  XML += " ";
 } else {
  XML += _password;
 }
 XML += "</password>";
 // Имя точки доступа
 XML += "<ssidAP>";
 XML += _ssidAP;
 XML += "</ssidAP>";
 // Пароль точки доступа
 XML += "<passwordAP>";
 if (_passwordAP == NULL) {
  XML += " ";
 } else {
  XML += _passwordAP;
 }
 XML += "</passwordAP>";
 // Времянная зона
 XML += "<timezone>";
 XML += timezone;
 XML += "</timezone>";
 //  Время работы
 XML += "<timeled>";
 XML += TimeLed;
 XML += "</timeled>";
 // Время 1
 XML += "<times1>";
 XML += times1;
 XML += "</times1>";
 // Время 2
 XML += "<times2>";
 XML += times2;
 XML += "</times2>";
 // Текущее время
 XML += "<time>";
 XML += XmlTime();
 XML += "</time>";
 // Статус
 XML += "<state>";
 XML += state0;
 XML += "</state>";
 XML += "</Donnees>";
 HTTP.send(200, "text/xml", XML);
}

void handle_Block() {
 XML = "<div class=\"block col-md-5\">";
 XML += "<h5 class=\"alert-info\">";
 XML += SSDP_Name;
 XML += "</h5>";
 XML += "<div class=\"alert alert-dismissible alert-warning\"><b>Обратите внимание</b>";
 XML += "<br>Таймер 1: ";
 XML += times1;
 XML += "<br>Таймер 2: ";
 XML += times2;
 XML += "<br>Время работы: ";
 XML += TimeLed;
 XML += "</div>";
 XML += "<input type=\"submit\" onclick=\"ajax('";
 XML += WiFi.localIP().toString();
 XML += "','rgb?r=255&g=255&b=255',this);\" value=\"Включить\" class=\"btn btn-block btn-primary\">";
 XML += "<input style=\"width:33%;display:inline-block\" class=\"btn btn-block btn-default\" value=\"Красный\" onclick=\"ajax('";
 XML += WiFi.localIP().toString();
 XML += "','rgb?r=255&g=0&b=0',this);\" type=\"submit\">";
 XML += "<input style=\"width:33%;display:inline-block\" class=\"btn btn-block btn-default\" value=\"Зеленый\" onclick=\"ajax('";
 XML += WiFi.localIP().toString();
 XML += "','rgb?r=0&g=255&b=0',this);\" type=\"submit\">";
 XML += "<input style=\"width:33%;display:inline-block\" class=\"btn btn-block btn-default\" value=\"Синий\" onclick=\"ajax('";
 XML += WiFi.localIP().toString();
 XML += "','rgb?r=0&g=0&b=255',this);\" type=\"submit\">";
  XML += "<input type=\"submit\" onclick=\"ajax('";
 XML += WiFi.localIP().toString();
 XML += "','rgb?r=0&g=0&b=0',this);\" value=\"Выключить\" class=\"btn btn-block btn-primary\">";
 XML += "<hr>";
 XML += "<div class=\"alert alert-dismissible alert-info\">Изменить конфигурацию устройсва вы можете на странице управления</div>";
 XML += "<a class=\"btn btn-block btn-default\" href=\"http://";
 XML += WiFi.localIP().toString();
 XML += "/device.htm\">Страница управления</a>";
 XML += "</div>";
 HTTP.send(200, "text/plain", XML);
}

void handle_IplocationXML() {
 XML = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
 XML += "<List>";
 XML += "<location>";
 XML += "<ip>";
 XML += WiFi.localIP().toString();
 XML += "</ip>";
 XML += Devices;
 XML += "</location>";
 XML += "</List>";
 HTTP.send(200, "text/xml", XML);
}
