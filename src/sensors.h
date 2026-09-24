#ifndef SENSORS_H
#define SENSORS_H

void setupSensors();

float getDistance();

void sensorTask(void *parameter);

#endif
