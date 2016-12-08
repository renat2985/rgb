void WIFIAP_Client() {
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(_ssid.c_str(), _password.c_str());
  tries(11);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(WL_CONNECTED);
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  if (WiFi.status() != WL_CONNECTED)
  {
    StartAPMode();
  }
}

bool StartAPMode()
{
  WiFi.disconnect();
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(_ssidAP.c_str(), _passwordAP.c_str());
  dnsServer.start(DNS_PORT, "*", apIP);
  return true;
}

bool RestartWiFi() {
  //Холодный перезапуск WiFi при первой настройке
  Serial.println("WiFi reconnect");
  // Не отключаясь точки доступа подключаемся к роутеру для получения будущего IP
  WiFi.mode(WIFI_AP_STA );
  WiFi.begin(_ssid.c_str(), _password.c_str());
  tries(30);

  Serial.println("");
  Serial.println(WiFi.localIP());
  HTTP.send(200, "text/plain", WiFi.localIP().toString());
  delay(5000);
  // Отключаем точку доступа и переподключаемся к роутеру
  ESP.restart();
}

// Попытки подключения к сети
void tries(byte tries) {
  while (--tries && WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }
}

