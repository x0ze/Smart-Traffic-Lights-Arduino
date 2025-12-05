#include "traffic_light.h"
#include <Arduino.h>

void start_dynamic(int statusLeft, int statusRight) {

  if (statusLeft == HIGH && statusRight == LOW /*&& roadFree*/) {
    /*counter();*/
    setGreen(13);
    setRed(12);
  }
 // Right sensor detects a car? 
    // No car coming from the left at present (in the last x seconds)?
        // Right lights green
        // Left lights red
  if (statusRight == HIGH && statusLeft == LOW /*&& roadFree*/) {
    setGreen(12);
    setRed(13);
  }
 // Left sensor detects a car? 
    // No car coming from the right at present (in the last x seconds)?
        // Left lights green
        // Right lights red
}

void counter(const unsigned long maxTime, unsigned long currentMillis) {
  unsigned long previousMillis = 0;
  const long interval = 1000;  
  unsigned long secondsCounter = 0;
  bool roadFree = false;

  if (currentMillis - previousMillis >= interval && secondsCounter < maxTime) {
    previousMillis = currentMillis;
    secondsCounter++;

    if (secondsCounter == maxTime) {
      roadFree = true;
    }
  }
}