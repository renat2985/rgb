void initRGB() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  HTTP.on("/rgb", LedRGB);                // запуск мотора напровление храниться в переменной
}
void LedRGB() {
  int r = HTTP.arg("r").toInt();
  int g = HTTP.arg("g").toInt();
  int b = HTTP.arg("b").toInt();
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(r, g, b));
    strip.show();
    HTTP.send(200, "text/plain", "OK");
  }

}

