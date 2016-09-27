// Выполняется при нажатии на кнопку
void Tach_0() {
 static unsigned long millis_prev;
 // Устроняем дребезг контакта
 if (millis() - 500 > millis_prev) {
  chaing = 1; // Выстовляем признак нажатия кнопки
 }
 millis_prev = millis();
}

void alarm_clock() {
  tickerSetLow.attach(TimeLed, setT1, 0);
  LedON(r, g, b);
  state0=3;
  analogWrite(buzer_pin, volume);
}

void setT1(int state) {
  tickerSetLow.detach();
  analogWrite(buzer_pin, 0);
  digitalWrite(buzer_pin,1);
  chaing = 1;
}

