#ifndef CONTROL_H
#define CONTROL_H

enum RoverMode
{
    MANUAL,
    AUTONOMOUS
};

RoverMode getRoverMode();

void setRoverMode(RoverMode mode);

bool isEmergencyStopped();

void setEmergencyStop(bool stopped);

#endif
