#include "control.h"
#include "motors.h"
#include <Arduino.h>


bool emergencyStop = false;

RoverMode currentMode = MANUAL;



RoverMode getRoverMode()
{
    return currentMode;
}

void setRoverMode(RoverMode mode)
{
    currentMode = mode;

    if (mode == MANUAL)
    {
        Serial.println("MODE: MANUAL");
    }
    else if (mode == AUTONOMOUS)
    {
        Serial.println("MODE: AUTONOMOUS");
    }
}



bool isEmergencyStopped()
{
    return emergencyStop;
}

void setEmergencyStop(bool stopped)
{
    emergencyStop = stopped;

    if (stopped)
    {
        stopRobot();
    }
}




