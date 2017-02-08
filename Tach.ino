// Выполняется при нажатии на кнопку
void Tach_0() {
  static unsigned long millis_prev;
  // Устроняем дребезг контакта
  if (millis() - 500 > millis_prev) {
    sound(BUZER_PIN, volume, 1000, 100);
    chaing = 1; // Выстовляем признак нажатия кнопки
  }
  millis_prev = millis();
}

void alarm_clock() {
  tickerSetLow.attach(timeLed, setT1, 0);
  //LedON(r, g, b);
  state0 = 0;
  chaing = 1;
  analogWrite(BUZER_PIN, volume);
}

void alarm_pir() {
  tickerSetLow.attach(timeLed, setT1, 0);

 // if (state0 == 0) {
  chaing = 1;
 state0 = 0;
 // }


}

void setT1(int state) {
  tickerSetLow.detach();
  analogWrite(BUZER_PIN, 0);
  digitalWrite(BUZER_PIN, 1);
  state0 = 1;
  chaing = 1;
}

