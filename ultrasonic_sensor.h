#ifndef SENSOR_PIR_H
#define SENSOR_PIR_H

void initSensor(int trigPin, int echoPin);
int readSensor(int trigPin, int echoPin);

#endif
