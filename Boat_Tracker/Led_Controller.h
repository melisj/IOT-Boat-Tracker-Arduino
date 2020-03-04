// Setup the led
#define LED_COUNT 3
#define LED_PIN D2
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN);

void SetLedsColor(int r, int g, int b){
  for(int i = 0; i < LED_COUNT; i++) {
     strip.setPixelColor(i, r,g,b);
  }

  strip.show();
}

void LedStartUpSequence(){
  strip.begin();

  // Loop trough the lights
  for(int i = 0; i < LED_COUNT; i++) {
     strip.setPixelColor(i, 0, 255, 0);
     strip.show();
     delay(200);
     strip.setPixelColor(i, 0, 0, 0);
     strip.show();
  }
  
  // Blink lights
  for(int i = 0; i < 5; i++) {
    SetLedsColor(0,255,0);
    delay(1000);
    SetLedsColor(0,0,0);
  }
}

// Change the state of the led's by recieving data from the weather API
void TurnOnWeatherLed(int stateArray[LED_COUNT]) {
  for(int i = 0; i < LED_COUNT; i++) {
     strip.setPixelColor(i, stateArray[i] > 0 ? 255 : 0, stateArray[i] == 1 ? 255 : 0,0);
  }
 
  strip.show();
}
