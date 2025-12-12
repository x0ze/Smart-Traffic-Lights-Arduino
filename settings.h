#ifndef SETTINGS_H
#define SETTINGS_H

extern float distance;   // Distance parameter (meters)
extern float maxSpeed;   // Maximum speed parameter (km/h)

// Functions to read/write distance and speed
void setDistance(float d);
float getDistance();

void setMaxSpeed(float s);
float getMaxSpeed();


float computeMaxTime();

#endif
