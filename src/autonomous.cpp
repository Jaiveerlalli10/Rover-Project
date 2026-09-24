#include <Arduino.h>

#include "autonomous.h"
#include "control.h"
#include "motors.h"
#include "sensors.h"

void autonomousTask(void *parameter)
{
    while (true)
    {
        if (getRoverMode() == AUTONOMOUS)
        {
            float distance = getCurrentDistance();

            if (distance > 30)
            {
                moveForward(100);
            }
            else
            {
                stopRobot();

                vTaskDelay(pdMS_TO_TICKS(200));

                turnRight(100);

                vTaskDelay(pdMS_TO_TICKS(500));

                stopRobot();
            }
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
