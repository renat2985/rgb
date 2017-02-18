# esp8266 and WS2811/WS2812/NeoPixel LEDs (Arduino)

![alt](https://raw.githubusercontent.com/tretyakovsa/jaluzi/master/tutorial/screen.png)

## Components

- IDs 	# 	Component 	Footprint 	Properties
- U1 	1 	ESP8266 (beta) 	ESP8266
- R2 	1 	Resistor Resist the flow of electrical energy in a circuit, changing the voltage and current as a result. 	0617/17 	1 kohm
- P1 	1 	Power Supply This is the component used to represent the power supply in the Electronics Workbench (the breadboard simulator). There are multiple footprints so if you are designing a PCB be sure to choose which footprint works best for your design. 	Power Header 0.1" through hole 2 	12 , 5
- U2 	1 	3.3V Regulator [LD1117V33] 	TO220
- LED1 	1 	WS2811/WS2812/NeoPixel LEDs
- S1 	1 	Pushbutton Momentary switches that close a circuit when pressed. 	TACTILE-PTH
- PIEZO1 	1 	Buzzer [Piezo small] This is the Piezo buzzer included in the DFRobot Kit. It is 12mm in diameter. See datasheet for frequency response. 	PIEZO 12mm DIAMETER



##Upload instruction

###[NodeMCU Flasher (Easy)](https://github.com/renat2985/rgb/tree/master/build)

###[Arduino Windows (Video)](https://www.youtube.com/watch?v=jMK9mySGHio)

###[Arduino Linux (Video)](https://www.youtube.com/watch?v=1TAHlRqZ46k)

####Used Libraries
- Arduino core for ESP8266 WiFi chip https://github.com/esp8266/Arduino
- Arduino ESP8266 filesystem uploader https://github.com/esp8266/arduino-esp8266fs-plugin
- C++ JSON library for IoT. Simple and efficient. https://github.com/bblanchon/ArduinoJson
- Neo Pixels!  https://github.com/adafruit/Adafruit_NeoPixel
- WS2812 FX Library for Arduino and ESP8266  https://github.com/kitesurfer1404/WS2812FX

##Work example (Video)

[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/LZI4Yu47LZI/0.jpg)](https://www.youtube.com/watch?v=LZI4Yu47LZI&list=PL6NJTNxbvy-IPTDQk8XjTV41oRrFafrRi)

##Construction
```
#define TACH_PIN 0    // Кнопка управления
#define BUZER_PIN 3   // Бузер
#define LED_PIN 2     // RGB лента
int ledCount = 15;    // Количество лед огней
// If you use ESP8266 12 you can add
#define PIR_PIN 14    // RIR sensors
```
[https://circuits.io/circuits/2546437-esp8266-and-rgb-ws2811](https://circuits.io/circuits/2546437-esp8266-and-rgb-ws2811)

###Breadboard

![alt](https://raw.githubusercontent.com/renat2985/rgb/master/tutorial/breadboard.gif)

###Schematic

![alt](https://raw.githubusercontent.com/renat2985/rgb/master/tutorial/schematic.gif)

##Othe...

####Jalousie: [https://github.com/tretyakovsa/jaluzi](https://github.com/tretyakovsa/jaluzi)

####Sonoff: [https://github.com/tretyakovsa/Sonoff_WiFi_switch](https://github.com/tretyakovsa/Sonoff_WiFi_switch)


####Themes you can download here: [http://bootswatch.com/](http://bootswatch.com/)


##Donation

If you like this project, you can give me a cup of coffee :)

[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_donations&business=W4PURUNKWMRJW&lc=AU&item_name=esp8266&currency_code=USD&bn=PP%2dDonationsBF%3abtn_donate_SM%2egif%3aNonHosted)