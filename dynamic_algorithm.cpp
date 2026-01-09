#include "traffic_light.h"
#include "form_data_parser.h"
#include <Arduino.h>

static unsigned long endTime = 0;
int minGreenTime = 10; // seconds
static unsigned long minGreenEndTime = (unsigned long)(minGreenTime * 1000UL);

float maxTimeToTravelDistance = distance / (minSpeed / 3.6); // need to convert speed from km/h to m/s because distance is in meters

bool last_green_side_was_left = true;

void updateLights(bool carOnLeft, bool carOnRight) {
  unsigned long elapsed = millis();
  
}
