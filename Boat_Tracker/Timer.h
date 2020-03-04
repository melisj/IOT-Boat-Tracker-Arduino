// Timers
int secondsSinceStartup;
int lastSecond;
bool secondPassed;

// Used to check if this loop has surpassed the given second time
bool CheckTimer(int timer) {
  if(lastSecond == millis() / 1000)
    return false;

  secondPassed = true;
  lastSecond = millis() / 1000;
  return lastSecond % timer == 0;
  
}

void ResetTimer() {
  secondPassed = false;
}
