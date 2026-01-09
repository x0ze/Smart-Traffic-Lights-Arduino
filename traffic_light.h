#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

enum Side {
  LEFT,
  RIGHT
};

enum LightState {
  RED,
  RED_AND_AMBER,
  AMBER,
  GREEN
};

extern LightState leftLightState;
extern LightState rightLightState;

void initLight();
void setRed(Side side);
void setRedAndAmber(Side side);
void setAmber(Side side);
void setGreen(Side side);

#endif
