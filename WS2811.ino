void initRGB() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  HTTP.on("/rgb", LedRGB);
}
int LedRGB() {
  r = HTTP.arg("r").toInt();
  g = HTTP.arg("g").toInt();
  b = HTTP.arg("b").toInt();
  t = HTTP.arg("t").toInt();
  tickerSetLow.attach(t, setT1, 0);
  LedON(r, g, b);
  chaing = 1;
 sound(buzer_pin, volume, 1000, 100);
  HTTP.send(200, "text/plain", "OK");
}
void LedON(int r, int g, int b) {
  //Serial.println("LedON");
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(r, g, b));
    delay(100); //Плавное появление
    strip.show();
  }
}
void sound(int pin, int volume, int freq, int time_ms) {
  analogWrite(pin, volume);
  analogWriteFreq (freq);
  tickerBizz.attach_ms(time_ms, setPin, 1);
}

void setPin(int state) {
  tickerBizz.detach();
  analogWrite(buzer_pin, 0);
  digitalWrite(buzer_pin,1);
}
