#ifndef SENSORS_H
#define SENSORS_H

void setupSensors();

float getDistance();

float getCurrentDistance();

void sensorTask(void *parameter);

#endif
