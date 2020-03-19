void AudioSetup(){
  pinMode(BUZZER_PIN_1, OUTPUT);  
  pinMode(BUZZER_PIN_2, OUTPUT); 

  PlaySequence(introAudio);
}

void MakeSound(int delayMicroSeconds, float miliseconds){
  int iterations = (miliseconds * 1000) / delayMicroSeconds; 

  // Switch rapidly between on and off
  for(int i = 0; i < iterations; i++){
    digitalWrite(BUZZER_PIN_1, soundSwitch ? LOW : HIGH);
    digitalWrite(BUZZER_PIN_2, soundSwitch ? HIGH : LOW);
    soundSwitch = !soundSwitch;
    delayMicroseconds(delayMicroSeconds);
  }
  
  // Yielding to prevent error with WDT (preventing reset)
   yield();
}


// Interpret an audio string you can insert in the settings
AudioObject InterpretAudioString(String sequence) {
  AudioObject audioObj;
  int startIndex = sequence.indexOf('[') + 1;
  int endIndex;
  int currentNote, currentNoteLength;

  // Stop the loop when the end is marked with the ']' char
  while(sequence[startIndex] != ']') {
    // Get the note from the sequence
    currentNote = (int)sequence[startIndex] - asciiValueA;

    // Check the end of the note description
    endIndex = sequence.indexOf('/', startIndex);

    // Get the time duration of the tone
    currentNoteLength = sequence.substring(startIndex + 1, endIndex).toInt();

    // A dash value means the player should interpret it as a silent period
    if((int)sequence[startIndex] == asciiValueDash)
      audioObj.currentSequenceNotes[audioObj.currentSequenceLength] = 0;
    else 
      audioObj.currentSequenceNotes[audioObj.currentSequenceLength] = allNotes[currentNote];
      
    audioObj.currentSequenceTimes[audioObj.currentSequenceLength] = currentNoteLength;
  
    // Increase the index for the next sequence part
    audioObj.currentSequenceLength++;
    startIndex = endIndex + 1;
  }

  return audioObj;
}

void PlaySequence(String audio) {
  AudioObject audioObj = InterpretAudioString(audio);
  
  for(int i = 0; i < audioObj.currentSequenceLength; i++) {
    // If the note is 0 delay this note
    if(audioObj.currentSequenceNotes[i] == 0){
      delay(audioObj.currentSequenceTimes[i]);
    }
    // Else play the sound
    else 
      MakeSound(audioObj.currentSequenceNotes[i], audioObj.currentSequenceTimes[i]);
  }
}
