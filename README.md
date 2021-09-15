
## Smart Home V1.0
![](https://img.shields.io/badge/NodeMCU%20LoLin-V3-orange)  ![](https://img.shields.io/badge/version-1.0-blue) 

Features:

 1. Fire detect
 2. Fire alarm with buzzer , led, notification and email(optional)
 3. Room temperature and humidity
 4. Remote Fan ON/OFF
 5. Remote Light ON/OFF
 6. By entering the city name from the phone, it shows temperature and humidity information on the LCD screen.(It is enough to press the button on the circuit once.)

Used Libraries:
- Arduino_JSON
- ESP8266HTTPClient
- LiquidCrystal_I2C
- Wire
- WiFiClient
- DHT
- ESP8266WiFi
- BlynkSimpleEsp8266

## Blynk App Widget & Port Settings

- Temperature : “Gauge”, V5 pin, 0-50 value, reading rate : 1
- Humidity: “Gauge”, V6 pin , 0-100 value, reading rate : 1
- Fan : “Styled Button”, GP16 pin, 0-1 value, mode: switch
- Lamp : “Button”, GP15 pin, 0-1 value, mode: switch
- İnpu City Name : “Text Input”, V4 pin, character limit=15
- Notification : "Notification"
- Mail : "Email"

## Component List

  - 1 x Buzzer
- 1 x DHT11 T Temperature and Humidity Sensor
- 1 x 16x2 LCD Display(I2C)
- 1 x 12 Volt Fan
- 1 x White Led
- 1 x Red Led
- 1 x KY-019 5V Relay
- 1 x NodeMCU v3 LoLin
- 2 x 220Ω Resistor
- 2 x 1kΩ Resistor
- 1 x KY-026 Flame Sensor
- 1 x Button
- 1 x 12v 2A DC Power Supply or 9V Battery


## Circuit
![](https://github.com/FurkanTRN/smart_home/blob/master/Circuit/smart_home_devre.png.png)
## Blynk App Photo
![](https://github.com/FurkanTRN/smart_home/blob/master/Blynk%20App.png)
