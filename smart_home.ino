
#include <Arduino_JSON.h>
#include <ESP8266HTTPClient.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <WiFiClient.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_PRINT Serial
#define DHTPIN 0
#define DHTTYPE DHT11

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

char auth[] = "blynk token here";
char ssid[] = "your wifi ssid";
char pass[] = "your wifi password";

String openWeatherMapApiKey = "your api key";
String jsonBuffer;

const int buzzer = 14;
const int button = 12;
bool notification = true;
int Flame = HIGH;
const int flamePin = 13;
bool buttonState2 = true;
unsigned long oldTime = 0;
unsigned long currentTime;
String cityName;
int temp, humidity;

// you can change default city here
void weather(String city = "istanbul") {

  if ((millis() - oldTime) > 3000) {

    if (WiFi.status() == WL_CONNECTED) {
      String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "&units=metric" + "&APPID=" + openWeatherMapApiKey;

      jsonBuffer = httpGETRequest(serverPath.c_str());

      JSONVar myObject = JSON.parse(jsonBuffer);

      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
      }
      temp = myObject["main"]["temp"];
      humidity = myObject["main"]["humidity"];
      lcd.clear();
      if (temp == 0 || humidity == 0) {
        lcd.setCursor(5, 0);
        lcd.print("Check");
        lcd.setCursor(2, 1);
        lcd.print("City name");
      }
      else {
        lcd.setCursor(5, 0);
        lcd.print(city);
        lcd.setCursor(0, 1);
        lcd.print(temp);
        lcd.print((char)223);
        lcd.print("C");
        lcd.setCursor(9, 1);
        lcd.print("Hum %");
        lcd.print(humidity);
      }
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    oldTime = millis();
  }
}

BLYNK_WRITE(V4)
{
  cityName = param.asStr();
  cityName.toUpperCase();
}
String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;


  http.begin(client, serverName);


  int httpResponseCode = http.GET();

  String payload = "{}";

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();

  return payload;
}

void tempHum()
{
  float h = dht.readHumidity();       // for fahrenheith dht.readHumidity(true);
  float t = dht.readTemperature();    // for fahrenheith dht.readTemperature(true);

  if (isnan(h) || isnan(t)) {
    Serial.println("dht11 error!");
    return;
  }
  Blynk.virtualWrite(V6, h);
  Blynk.virtualWrite(V5, t);
}

void fireAlarm() {
  Flame = digitalRead(flamePin);
  if (Flame == LOW && notification) {
    Blynk.notify("Warning Fire Alarm");
    // optional
    Blynk.email("input email", "input message");
    for (int i = 0; i < 6; i++) {
      digitalWrite(buzzer, HIGH);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(350);
      digitalWrite(buzzer, LOW);
      digitalWrite(LED_BUILTIN, LOW);
      delay(300);
    }
    notificaton = false;
  }
  if (Flame == HIGH) {
    notification = true;
  }
}
void homeScreen() {
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("IP Adress");
  lcd.setCursor(2, 1);
  lcd.print(WiFi.localIP());
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  WiFi.begin(ssid, pass);
  lcd.init();
  lcd.backlight();
  dht.begin();
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(250);
    Serial.print(".");
  }
  lcd.print("WiFi Connected");
  delay(1000);
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.println(WiFi.localIP());
  Wire.begin(4, 5);
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Smart Home");
  lcd.print("V1.0");
  lcd.setCursor(6, 1);
  pinMode(flamePin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(button, INPUT);
  Blynk.notify("Device Online");
  timer.setInterval(1000L, tempHum);
  timer.setInterval(1000L, fireAlarm);

}
void loop()
{

  Blynk.run();
  timer.run();
  delay(10);

  if (digitalRead(button) == HIGH && buttonState2 == true)
  {
    while (digitalRead(button) == HIGH)
    {
      if (digitalRead(button) == LOW)
        break ;
    }
    weather(cityName);
    buttonState2 = false ;
  }

  if (digitalRead(button) == HIGH && buttonState2 == false)
  {
    while (digitalRead(button) == HIGH)
    {
      if (digitalRead(button) == LOW)
        break ;
    }
    homeScreen();
    buttonState2 = true ;
  }
}
