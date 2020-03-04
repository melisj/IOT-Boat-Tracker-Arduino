// The led will display heavy winds, the 2e will display heavy rain, the 3e will turn on when a thunderstorm is coming

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Adafruit_NeoPixel.h>

#include "Led_Controller.h"
#include "Timer.h"

// Button Setup
#define BUTTON_PIN D1
bool buttonPressed;

// Setup the networking side
const String networkName = "TELE2-A7E7F3_2.4G";
const String password = "36D49969D4C3";

// Domain main
const String domainName = "boattracker.duckdns.org";
const String ipBackupName = "[backup ip]"; 

// Connection for the weather API
const String weatherUrl = "http://" + domainName + "/arduino/weather";
const String calibrateUrl = "http://" + domainName + "/arduino/calibrate";

// Weather delay time (5 min)
const int secondDelayForWeather = 5 * 60;

DynamicJsonDocument json(1024); 

// Check the API every couple of ms
const int timeStep = 1000;

void setup() {
  Serial.begin(9600);

  // Setup all the pins
  pinMode(BUTTON_PIN, INPUT_PULLUP);  

  // Initialize the led strip
  LedStartUpSequence();

  // Setup the wifi connection
  WiFi.begin(networkName, password);
 
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.println("connecting");
  }
}

void loop() {
  
  if(CheckTimer(secondDelayForWeather)) {
    if(WiFi.status()== WL_CONNECTED){
      Serial.println("yeah");
      GetWeatherInfo();
    } 
    else
      Serial.println("Connection has been lost");   
  }
  
  // Check for button input
  if (digitalRead(BUTTON_PIN) == LOW)
  {
    if(!buttonPressed)
      CalibrateBoatHere();
    buttonPressed = true;
  }
  else 
    buttonPressed = false;

  // Reset the timer at the end of the loop
  ResetTimer();
}

void GetWeatherInfo() {
   // Send the request
    HTTPClient http;
    http.begin(weatherUrl); 
    int httpCode = http.GET(); 

    Serial.println(httpCode);

    // Recieve the request
    if (httpCode > 0) {
      deserializeJson(json, http.getString()); // Get the request response payload

      int stateArray[LED_COUNT] = { json["lightRain"], json["heavyRain"], json["heavyWind"] };
      TurnOnWeatherLed(stateArray);
    }
    
    http.end();
}

void CalibrateBoatHere() {
  // Send the request
  HTTPClient http;
  http.begin(calibrateUrl); 
  int httpCode = http.GET(); 

  Serial.println(httpCode);

  // Recieve the request
  if (httpCode > 0) {
    Serial.println("Request succeeded");
  }
  
  http.end();
}
