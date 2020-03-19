void SetLedsColor(int r, int g, int b){
  for(int i = 0; i < LED_COUNT; i++) {
     strip.setPixelColor(i, r, g, b);
  }
  strip.show();
}

void BlinkLight(int delayTime, int r, int g, int b){
  SetLedsColor(r, g, b);
  delay(delayTime);
  SetLedsColor(0,0,0);
  delay(delayTime);
}

void BlinkLightTimes(int delayTime, int r, int g, int b, int amount) {
  for(int i = 0; i < amount; i++) {
    MakeSound(NOTE_F, 0.1);
    BlinkLight(delayTime, r, g, b);
  }
}

void LoopThroughLeds(int delayTime, int r, int g, int b) {
  // Loop trough the leds
  for(int i = 0; i < LED_COUNT; i++) {
     strip.setPixelColor(i, r, g, b);
     strip.show();
     delay(delayTime);
     strip.setPixelColor(i, 0, 0, 0);
     strip.show();
  }
}

void LedStartUpSequence(){
  strip.begin();

  LoopThroughLeds(100, 0, 255, 0);
  
  // Blink lights
  BlinkLightTimes(250, 0, 255, 0, 4);
}

// Change the state of the led's by recieving data from the weather API
void TurnOnWeatherLed(int stateArray[LED_COUNT]) {
  for(int i = 0; i < LED_COUNT; i++) {
     strip.setPixelColor(i, stateArray[i] > 0 ? 255 : 0, stateArray[i] == 1 ? 255 : 0,0);
  }
 
  strip.show();
}
