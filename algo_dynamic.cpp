#include "traffic_light.h"
#include "settings.h"
#include <Arduino.h>

enum TrafficState {
  IDLE,
  IN_PROGRESS
};


static TrafficState state = IDLE;
static unsigned long greenEndTime = 0;
static int activeSide = 0;  // 1 = left, 2 = right

void start_dynamic(int statusLeft, int statusRight) {
  unsigned long now = millis();

  // ---------------------------------------------------
  // Dynamic calculation of transit time
  // ---------------------------------------------------
  float d = getDistance();      // meters
  float v = getMaxSpeed();      // km/h
  float speedMS = v * 0.27778;  // conversion km/h -> m/s

  if (speedMS < 0.1) speedMS = 0.1;  // avoid division by zero
  float maxTime = d / speedMS;       // time in seconds
  // ---------------------------------------------------

  switch (state) {

    case IDLE:
      if (statusLeft == 1 && statusRight == 0) {
        turnOffAll(2,3,4);
        turnOffAll(5,6,7);
        setGreen(4);  // left
        setRed(6);    // right
        activeSide = 1;
        greenEndTime = now + (unsigned long)(maxTime * 1000UL);
        state = IN_PROGRESS;
        Serial.println("Left free - Right Closed");
      } 
      else if (statusRight == 1 && statusLeft == 0) {
        turnOffAll(2,3,4);
        turnOffAll(5,6,7);
        setGreen(7);  // right
        setRed(2);    // left
        activeSide = 2;
        greenEndTime = now + (unsigned long)(maxTime * 1000UL);
        state = IN_PROGRESS;
        Serial.println("Left closed - Right free");
      }
      break;

    case IN_PROGRESS:
      if (now >= greenEndTime) {
        turnOffAll(2,3,4);
        turnOffAll(5,6,7);
        setRed(2);
        setRed(6);
        activeSide = 0;
        state = IDLE;
        Serial.println("Left closed - Right closed");
      }
      break;
  }
}
