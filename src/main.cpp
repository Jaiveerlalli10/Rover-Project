#include <Arduino.h>
#include "autonomous.h"
#include "motors.h"
#include "rover_wifi.h"
#include "sensors.h"

void setup()
{
    Serial.begin(115200);

    Serial.println("ESP32 Rover Starting...");

    // Create motor command queue
    motorQueue = xQueueCreate(1, sizeof(MotorCommand));

    // Set up motor pins and drivers
    setupMotors();

    // Set up sensors
    setupSensors();

    // Start with the rover stopped
    stopRobot();

    // Start Wi-Fi
    startWiFi();

    // Start Wi-Fi task
    xTaskCreate(
        wifiTask,
        "WiFi Task",
        4096,
        NULL,
        1,
        NULL
    );

    // Start motor task
    xTaskCreate(
        motorTask,
        "Motor Task",
        4096,
        NULL,
        1,
        NULL
    );

    // Start sensor task
    xTaskCreate(
        sensorTask,
        "Sensor Task",
        2048,
        NULL,
        1,
        NULL
    );

    xTaskCreate(
        autonomousTask,
        "Autonomous Task",
        2048,
        NULL,
        1,
        NULL
    );
}

void loop()
{
}
