// Setup the led
#define BUZZER_PIN_1 D5
#define BUZZER_PIN_2 D6

bool soundSwitch = true;

void MakeSound(int delayMiliseconds, float seconds){
  int iterations = (seconds * 1000) / delayMiliseconds; 

  for(int i = 0; i < iterations; i++){
     if(soundSwitch) {
      digitalWrite(BUZZER_PIN_1, HIGH);
      digitalWrite(BUZZER_PIN_2, LOW);
      soundSwitch = false;
     }
     else {
      digitalWrite(BUZZER_PIN_1, LOW);
      digitalWrite(BUZZER_PIN_2, HIGH);
      soundSwitch = true;
     }
     delay(delayMiliseconds);
  }
}

void AudioSetup(){
  pinMode(BUZZER_PIN_1, OUTPUT);  
  pinMode(BUZZER_PIN_2, OUTPUT);  

  MakeSound(4, 0.2);
}
