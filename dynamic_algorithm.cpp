#include "traffic_light.h"
#include "form_data_parser.h"
#include <Arduino.h>

static unsigned long endTime = 0;
const int MIN_GREEN_TIME = 10; // seconds
const int AMBER_WARNING_TIME = 1; // seconds
static unsigned long minGreenEndTime = (unsigned long)(MIN_GREEN_TIME * 1000UL);
unsigned long elapsed;

float maxTimeToTravelDistance;

bool lastGreenSideWasLeft = true;

bool turnLeftRedConditions;
bool turnLeftRedAndAmberConditions;
bool turnLeftAmberConditions;
bool turnLeftGreenConditions;

bool turnRightRedConditions;
bool turnRightRedAndAmberConditions;
bool turnRightAmberConditions;
bool turnRightGreenConditions;

bool endTimeConditions;

void updateLights(bool carOnLeft, bool carOnRight) {
  maxTimeToTravelDistance = distance / (minSpeed / 3.6); // need to convert speed from km/h to m/s because distance is in meters
  elapsed = millis();
  
  turnLeftRedConditions = leftLightState == AMBER && elapsed >= minGreenEndTime;
  turnLeftRedAndAmberConditions = leftLightState == RED && carOnLeft && rightLightState == RED && elapsed >= endTime && !lastGreenSideWasLeft;
  turnLeftAmberConditions = leftLightState == GREEN && carOnRight && elapsed >= minGreenEndTime - AMBER_WARNING_TIME * 1000;
  turnLeftGreenConditions = leftLightState == RED_AND_AMBER && elapsed >= endTime + AMBER_WARNING_TIME * 1000;

  turnRightRedConditions = rightLightState == AMBER && elapsed >= minGreenEndTime;
  turnRightRedAndAmberConditions = rightLightState == RED && carOnRight && leftLightState == RED && elapsed >= endTime && lastGreenSideWasLeft;
  turnRightAmberConditions = rightLightState == GREEN && carOnLeft && elapsed >= minGreenEndTime - AMBER_WARNING_TIME * 1000;
  turnRightGreenConditions = rightLightState == RED_AND_AMBER && elapsed >= endTime + AMBER_WARNING_TIME * 1000;

  endTimeConditions = (carOnLeft && (leftLightState == GREEN || leftLightState == AMBER)) || (carOnRight && (rightLightState == GREEN || rightLightState == AMBER));

  if (endTimeConditions) {
    endTime = elapsed + maxTimeToTravelDistance * 1000;
  }

  // Left conditions
  if (turnLeftRedConditions) {
    setRed(LEFT);
  }

  if (turnLeftRedAndAmberConditions) {
    setRedAndAmber(LEFT);
    lastGreenSideWasLeft = true;
    endTime = elapsed;
    minGreenEndTime = elapsed + MIN_GREEN_TIME * 1000;
  }

  if (turnLeftAmberConditions) {
    setAmber(LEFT);
    minGreenEndTime = elapsed + AMBER_WARNING_TIME * 1000;
  }

  if (turnLeftGreenConditions) {
    setGreen(LEFT);
  }

  // Right conditions
  if (turnRightRedConditions) {
    setRed(RIGHT);
  }

  if (turnRightRedAndAmberConditions) {
    setRedAndAmber(RIGHT);
    lastGreenSideWasLeft = false;
    endTime = elapsed;
    minGreenEndTime = elapsed + MIN_GREEN_TIME * 1000;
  }

  if (turnRightAmberConditions) {
    setAmber(RIGHT);
    minGreenEndTime = elapsed + AMBER_WARNING_TIME * 1000;
  }

  if (turnRightGreenConditions) {
    setGreen(RIGHT);
  }
}
