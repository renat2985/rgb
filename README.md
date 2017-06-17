# esp8266 and WS2811/WS2812/NeoPixel LEDs (Arduino)

<a href="https://raw.githubusercontent.com/renat2985/rgb/master/tutorial/screen1.png"><img src="https://raw.githubusercontent.com/renat2985/rgb/master/tutorial/screen1.png" align="left" height="220" width="400" ></a>
<a href="https://raw.githubusercontent.com/renat2985/rgb/master/tutorial/screen2.png"><img src="https://raw.githubusercontent.com/renat2985/rgb/master/tutorial/screen2.png" align="left" height="220" width="400" ></a>
<a href="https://raw.githubusercontent.com/renat2985/rgb/master/tutorial/screen3.png"><img src="https://raw.githubusercontent.com/renat2985/rgb/master/tutorial/screen3.png" align="left" height="220" width="400" ></a>
<a href="https://raw.githubusercontent.com/renat2985/rgb/master/tutorial/screen4.png"><img src="https://raw.githubusercontent.com/renat2985/rgb/master/tutorial/screen4.png" align="left" height="220" width="400" ></a>

## Components

- IDs 	# 	Component 	Footprint 	Properties
- U1 	1 	ESP8266 (beta) 	ESP8266
- R2 	1 	Resistor Resist the flow of electrical energy in a circuit, changing the voltage and current as a result. 	0617/17 	1 kohm
- P1 	1 	Power Supply This is the component used to represent the power supply in the Electronics Workbench (the breadboard simulator). There are multiple footprints so if you are designing a PCB be sure to choose which footprint works best for your design. 	Power Header 0.1" through hole 2 	12 , 5
- U2 	1 	3.3V Regulator [LD1117V33] 	TO220
- LED1 	1 	WS2811/WS2812/NeoPixel LEDs
- S1 	1 	Pushbutton Momentary switches that close a circuit when pressed. 	TACTILE-PTH
- PIEZO1 	1 	Buzzer [Piezo small] This is the Piezo buzzer included in the DFRobot Kit. It is 12mm in diameter. See datasheet for frequency response. 	PIEZO 12mm DIAMETER



## Upload instruction

### [NodeMCU Flasher (Easy)](https://github.com/renat2985/rgb/tree/master/build)

### [Arduino Windows (Video)](https://www.youtube.com/watch?v=jMK9mySGHio)

### [Arduino Linux (Video)](https://www.youtube.com/watch?v=1TAHlRqZ46k)

#### Used Libraries
 - ESP8266WiFi.h
 - ESP8266WebServer.h
 - ESP8266SSDP.h
 - FS.h
 - time.h
 - Ticker.h
 - WiFiUdp.h
 - ESP8266HTTPUpdateServer.h
 - ESP8266httpUpdate.h
 - ESP8266HTTPClient.h
 - DNSServer.h
 - StringCommand.h           https://github.com/tretyakovsa/ESP8266-StringCommand
 - ArduinoJson.h             Ставим через менеджер библиотек
 - DHT.h                     https://github.com/markruys/arduino-DHT
 - OneWire.h                 Ставим через менеджер библиотек
 - DallasTemperature.h       Ставим через менеджер библиотек
 - PubSubClient.h            https://github.com/Imroy/pubsubclient
 - Adafruit_NeoPixel.h       https://github.com/adafruit/Adafruit_NeoPixel
 - WS2812FX.h                https://github.com/kitesurfer1404/WS2812FX

## Work example (Video)

[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/NrIrLw1rOdk/0.jpg)](https://www.youtube.com/watch?v=NrIrLw1rOdk&list=PL6NJTNxbvy-IPTDQk8XjTV41oRrFafrRi)

## Construction
```
  #define TACH_PIN 0    // Кнопка управления
  #define PIR_PIN 16     // RIR sensors
  #define RELE1_PIN 12  // Реле
  #define LED_PIN 13    // Светодиод
  #define DHTPIN 14     // DHT сенсор.
  #define RGB_PIN 2     // WS2811/WS2812/NeoPixel LEDs
  #define impuls_PIN 3  //электросчетчик
```
[https://circuits.io/circuits/2546437-esp8266-and-rgb-ws2811](https://circuits.io/circuits/2546437-esp8266-and-rgb-ws2811)

### Breadboard

![alt](https://raw.githubusercontent.com/renat2985/rgb/master/tutorial/breadboard.gif)

### Schematic

![alt](https://raw.githubusercontent.com/renat2985/rgb/master/tutorial/schematic.gif)

## Othe...

#### Jalousie: [https://github.com/tretyakovsa/jaluzi](https://github.com/tretyakovsa/jaluzi)

#### Sonoff: [https://github.com/tretyakovsa/Sonoff_WiFi_switch](https://github.com/tretyakovsa/Sonoff_WiFi_switch)


#### Themes you can download here: [http://bootswatch.com/](http://bootswatch.com/)


## Donation

If you like this project, you can give me a cup of coffee :)

[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_donations&business=W4PURUNKWMRJW&lc=AU&item_name=esp8266&currency_code=USD&bn=PP%2dDonationsBF%3abtn_donate_SM%2egif%3aNonHosted)

### WebMoney
- USD Z242847016348
- RUS R466173026928
- EUR E555861976545