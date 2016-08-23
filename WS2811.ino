void initRGB() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  HTTP.on("/rgb", LedRGB);
}
void LedRGB() {
  r = HTTP.arg("r").toInt();
  g = HTTP.arg("g").toInt();
  b = HTTP.arg("b").toInt();
    LedON(r, g, b);
 tone(buzer_pin, 2000, 500);



HTTP.send(200, "text/plain", "OK");
}
void LedON(int r, int g, int b) {
  //Serial.println("LedON");
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(r, g, b));
    strip.show();
  }
}
