#include "traffic_light.h"
#include "settings.h"
#include <Arduino.h>

static unsigned long endTime = 0;
static unsigned long minGreenEndTime = 0;
int minGreenTime = 10 // seconds

// ---------------------------------------------------
// Dynamic calculation of transit time
// ---------------------------------------------------
float d = getDistance();      // meters
float v = getMaxSpeed();      // km/h
float speedMS = v / 3.6;  // conversion km/h -> m/s
float timeToTravelDistance = d / speedMS;       // time in seconds
// ---------------------------------------------------

bool inProgress = false;
bool rightSideGreen = false;
bool leftSideGreen = false;
String previousSide;

void resetTimers() {
  unsigned long now = millis();
  endTime = now + (unsigned long)(timeToTravelDistance * 1000UL);
  minGreenEndTime = now + (unsigned long)(minGreenTime * 1000UL)
}

void start_dynamic(bool carOnLeft, bool carOnRight) {
  /* Temp, need to fix this block
  if (carOnLeft && !leftSideGreen) {
    turnOffAll(5,6,7);
    setRed(6);    // left
  }

  if (carOnRight == 0 && !rightSideGreen) {
    turnOffAll(2,3,4);
    setRed(2);    // right
  }

  if (carOnLeft && carOnRight) {
    greenEndTime = now + greenLightCooldown;
  }

  if (carOnLeft && !inProgress) {
    inProgress = true;
    leftSideGreen = true;
    turnOffAll(5,6,7);
    setGreen(7);  // left
    endTime = now + (unsigned long)(timeToTravelDistance * 1000UL);
    Serial.println("Left free - Right Closed");
  } 
  
  if (carOnRight && !inProgress) {
    inProgress = true;
    rightSideGreen = true;
    turnOffAll(2,3,4);
    setGreen(4);  // right
    endTime = now + (unsigned long)(timeToTravelDistance * 1000UL);
    greenEndTime = now + (unsigned long)(greenTimeCooldown * 1000UL);
    Serial.println("Left closed - Right free");
  }

  if (inProgress && now >= endTime) {
    Serial.println("Left closed - Right closed");
    inProgress = false;
  }  
  */
}
