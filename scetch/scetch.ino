#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <NTPClient.h>
#include <WiFiUdp.h> 
#include "DHT.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Address of your i2c LCD back pack should be updated.

WiFiUDP ntpUDP;
int timezone = 3; //временной сдвиг в часах от UTC 
int pos_time = 4; //отступ от края при отображении времени
NTPClient timeClient(ntpUDP, "pool.ntp.org", timezone*3600,3600123);

#define DHTTYPE DHT11 
uint8_t DHTPin = 2;
// инициализация датчика DHT.
DHT dht(DHTPin, DHTTYPE);   

const char *ssid = "Wifi";
const char *password = "1122334455";
String APIKEY = "1041444a18cfb8448343254a45721b1d";
String CityID = "702972"; //Your City ID
WiFiClient client;
const char *weatherHost = "api.openweathermap.org";
int counter = 15;
String weatherDescription = "";
String weatherLocation = "";
String Country;
float Temperature, DHTTemperature;
float Humidity, DHTHumidity;
String result;
int hh,mm,ss;
int index_date;
String date_time,date;
int hic;
long previousMillis = 0;
int list = 1;


void setup()
{
  Serial.begin(115200);
  int cursorPosition = 1;
  lcd.init();
  lcd.setBacklight(255);
  lcd.print("   Connecting");
  Serial.println("Connecting to " + String(ssid));
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  { 
    cursorPosition++;
    delay(500);
    lcd.setCursor(cursorPosition, 2);
    lcd.print(".");
  }

  lcd.clear();
  lcd.print("   Connected!");
  Serial.println("Connected to " + String(ssid));
  Serial.println(WiFi.localIP());
  delay(1000);
  bignummer();
}

void loop()
{
  if (counter == 15)  //Get new data every 10 minutes
  {
    counter = 0;
    getWeatherData();
  }
  
  unsigned long currentMillis = millis();
  //проверяем не прошел ли нужный интервал, если прошел то
  if(currentMillis - previousMillis > 10000) {
    // сохраняем время последнего переключения
    previousMillis = currentMillis; 
 
    if (list == 1){
      list = 2;
      printTime(pos_time);
    }else if(list == 2){
      list = 3;
      displayConditions(Temperature, Humidity, weatherDescription);
      counter++;
    }else if(list == 3){
      list = 1;
      printDHT();
    }
  }
}
