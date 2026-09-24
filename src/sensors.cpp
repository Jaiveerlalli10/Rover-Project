#include <Arduino.h>
#include "control.h"
#include "sensors.h"

#define TRIG_PIN 16
#define ECHO_PIN 4

bool obstacleHandled = false;
int obstacleCount = 0;

void setupSensors()
{
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    digitalWrite(TRIG_PIN, LOW);
}

float getDistance()
{
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH);

    float distance = duration * 0.0343 / 2;

    return distance;
}

void sensorTask(void *parameter)
{
    while (true)
    {
        float distance = getDistance();

        Serial.print("Distance: ");
        Serial.print(distance);
        Serial.println(" cm");
        if (distance <= 20) {
            obstacleCount++;
        } else {
            obstacleCount = 0;
        }

        if (distance <= 20 && !obstacleHandled && obstacleCount >= 3) {
        
            Serial.println("OBSTACLE DETECTED - EMERGENCY STOP!");

            setEmergencyStop(true);
            obstacleHandled = true;
        }

        if (distance > 20) {
            obstacleHandled = false;
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
