#include "control.h"
#include "motors.h"

bool emergencyStop = false;

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
