void WIFIAP_Client() {
 if (_setAP == "0") {
  WiFi.mode(WIFI_STA);
  Serial.println("WIFI_STA");
  WiFi.begin(_ssid.c_str(), _password.c_str());
  connectSTA();
  Serial.println("");
  Serial.println(WiFi.status());
  if (WiFi.status()==6){
   connectAP();
  }
 } else {
  connectAP();
  connectSTA();
 }
}

void connectSTA(){
 int i = 0;
 int statusAP = 0;
 while (WiFi.status() != WL_CONNECTED && i < 50) {
  delay(500);
  i++;
  Serial.print(".");
 }
}

void connectAP(){
 WiFi.softAP(_ssidAP.c_str(), _passwordAP.c_str());
 IPAddress myIP = WiFi.softAPIP();
 Serial.print("AP IP address: ");
 Serial.println(myIP);
 Serial.println("WIFI_AP_STA");
}
