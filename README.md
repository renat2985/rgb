# **Офлайн умный дом** на базе ESP8266 и светодиодов WS2811/WS2812/NeoPixel

<p align="center">
<img src="https://raw.githubusercontent.com/renat2985/rgb/master/tutorial/screen1.png" width="35%" height="35%">
<img src="https://raw.githubusercontent.com/renat2985/rgb/master/tutorial/screen2.png" width="35%" height="35%">
<img src="https://raw.githubusercontent.com/renat2985/rgb/master/tutorial/screen3.png" width="35%" height="35%">
<img src="https://raw.githubusercontent.com/renat2985/rgb/master/tutorial/screen4.png" width="35%" height="35%">
</p>



## Описание

Этот проект предназначен для создания автономной системы умного дома с использованием микроконтроллера ESP8266 и светодиодов WS2811/WS2812/NeoPixel. Он предоставляет функциональность управления освещением и другими устройствами без необходимости постоянного подключения к интернету.

## Особенности

- **NTP**: Синхронизация времени через протокол NTP.
- **DDNS**: Поддержка динамического DNS для удаленного доступа.
- **Таймеры**: Настройка автоматических действий по расписанию.
- **Датчики**: Поддержка DHT11, DHT22, AM2302, RHT03, DS18B20 и аналоговых датчиков.
- **Реле**: Управление до 4 реле.
- **Жалюзи**: Контроль жалюзи через интерфейс.
- **Светодиоды**: Управление светодиодами WS2811/WS2812/NeoPixel.
- **RF и IR**: Прием и передача сигналов радиочастотного и инфракрасного диапазонов.

## Установка

### 🚀 Веб установка (рекомендуется)

Откройте этот сайт и следуйте инструкциям

### [https://renat2985.github.io/rgb/](https://renat2985.github.io/rgb/)

### Или используйте NodeMCU Flasher

1. **Загрузка прошивки**: Скачайте файл прошивки [Build.Spiffs.flash.1Mb.256Kb.2018.12.03.zip](https://github.com/renat2985/rgb/releases/download/3.0/Build.Spiffs.flash.1Mb.256Kb.2018.12.03.zip)

2. **Инструмент прошивки**: Скачайте [NodeMCU Flasher](https://github.com/nodemcu/nodemcu-flasher) для Windows ([Win32](https://github.com/nodemcu/nodemcu-flasher/blob/master/Win32/Release/ESP8266Flasher.exe) или [Win64](https://github.com/nodemcu/nodemcu-flasher/blob/master/Win64/Release/ESP8266Flasher.exe)).
3. **Настройка**: Настройте параметры прошивки:
   ```
   - Модуль: Generic ESP8266 Module
   - Размер флеша: 1 МБ
   - Режим флеша: DIO
   - Частота флеша: 40 МГц
   - Скорость загрузки: 921600
   ```
     
     <img src="https://raw.githubusercontent.com/tretyakovsa/Sonoff_WiFi_switch/master/tutorial/nodemcu-flasher.png" width="400px">

## Примеры использования

Пример работы системы можно посмотреть в [этом видео](https://github.com/renat2985/rgb).

[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/rNLlpkg2BGI/0.jpg)](https://www.youtube.com/playlist?list=PL6NJTNxbvy-IPTDQk8XjTV41oRrFafrRi)

## Мобильное приложение

Для удобного управления системой доступно мобильное приложение:

- **Репозиторий**: [iot-room-finder](https://github.com/tutaf/iot-room-finder)
- **Скачать**: [Google Play](https://play.google.com/store/apps/details?id=com.tutaf.iotroomfinder)

Приложение отправляет UPnP-пакет в локальную сеть, и первое устройство, которое ответит, откроется в вашем браузере, что избавляет от необходимости запоминать IP-адреса устройств.

## Благодарности

Особая благодарность Андрею за разработку мобильного приложения.



## Другие наши проекты

  - Jalousie: [https://github.com/tretyakovsa/jaluzi](https://github.com/tretyakovsa/jaluzi)

  - Sonoff: [https://github.com/tretyakovsa/Sonoff_WiFi_switch](https://github.com/tretyakovsa/Sonoff_WiFi_switch)

  - Themes you can download here: [https://bootswatch.com/3/](https://bootswatch.com/3/)


## :battery: Donation

If you like this project, you can buy me a cup of coffee :coffee:

<img src="https://github.com/renat2985/renat2985/raw/main/donate/donate.png" width="100%">

- PayPal [https://www.paypal.me/RKevrels](https://www.paypal.me/RKevrels/5)
