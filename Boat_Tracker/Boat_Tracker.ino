// The led will display heavy winds, the 2e will display heavy rain, the 3e will turn on when a thunderstorm is coming
// Hardcoded boat
const String BOAT_NAME = "viermineen";

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Adafruit_NeoPixel.h>

DynamicJsonDocument json(1024); 

#include "Timer.h"
#include "Sound_Controller.h"
#include "Led_Controller.h"
#include "Wifi_Connection.h"

const int secondDelayForWeather = 60;

// Button Setup
#define BUTTON_PIN D1
bool buttonPressed = false;

// Setup the networking side
const String networkName = "TELE2-A7E7F3_2.4G";
const String password = "36D49969D4C3";
//const String networkName = "NokiaPower";
//const String password = "arduinoenzo";

// Domain main
const String domainName = "boattracker.duckdns.org";
const String ipBackupName = "[backup ip]"; 

// Connection for the weather API and calibration of the position
const String weatherUrl = "http://" + domainName + "/arduino/weather?boat_name=" + BOAT_NAME;
const String calibrateUrl = "http://" + domainName + "/arduino/calibrate";


void setup() {
  Serial.begin(9600);
  // Setup the sound device
  AudioSetup();

  // Setup all the pins
  pinMode(BUTTON_PIN, INPUT_PULLUP);  

  // Initialize the led strip
  LedStartUpSequence();

  // Setup the wifi connection
  WiFi.begin(networkName, password);
 
  while (WiFi.status() != WL_CONNECTED) {
     LoopThroughLeds(150, 0, 0, 255);
     Serial.println("connecting");
  }

  BlinkLight(400, 0, 0, 255);
  GoodReplySound();
}

void loop() {
  // Check if the weather need to be requested
   if(CheckTimer(secondDelayForWeather)) {
      if(WiFi.status()== WL_CONNECTED){
          Serial.println("yeah");
          GetWeatherInfo(DoRequestFor(weatherUrl, true));
      } 
      else
          Serial.println("Connection has been lost");   
   }
   
   // Check for button input
   if (digitalRead(BUTTON_PIN) == LOW)
   {
      // Calibrate the location of the boat here
      if(!buttonPressed) {
        CalibrateBoatHere(DoRequestFor(calibrateUrl, false, "boat_name=" + BOAT_NAME));
        delay(100); 
      }
      buttonPressed = true;
   }
   else 
      buttonPressed = false;
  
  // Reset the timer at the end of the loop
  ResetTimer();
}

// Get the data from the weather request
void GetWeatherInfo(int httpCode) {
  if(httpCode >= 200 && httpCode < 299) {
    int stateArray[LED_COUNT] = { json["lightRain"], json["heavyRain"], json["heavyWind"] };

    // Turn on the correct leds
    delay(500);
    TurnOnWeatherLed(stateArray);
  }
  else{
    Serial.println("Weather request failed");
  }
}

// Check if the request succeeded
void CalibrateBoatHere(int httpCode) {
  if(httpCode > 200 && httpCode < 299) {
    Serial.println("Calibration Succeeded");

    // turn of the leds
    delay(500);
    SetLedsColor(0,0,0);
  }
  else 
   Serial.println("Calibration Failed");

  // Get the weather info again after calibrating
   GetWeatherInfo(DoRequestFor(weatherUrl, true));
}
