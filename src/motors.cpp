#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include "motors.h"

// -------------------------
// TB6612 #1 pins
// -------------------------

#define TB1_STBY 33

#define TB1_PWMA 25
#define TB1_AIN1 26
#define TB1_AIN2 27

#define TB1_PWMB 13
#define TB1_BIN1 14
#define TB1_BIN2 12


// -------------------------
// TB6612 #2 pins
// -------------------------

#define TB2_STBY 32

#define TB2_PWMA 21
#define TB2_AIN1 22
#define TB2_AIN2 23

#define TB2_PWMB 19
#define TB2_BIN1 18
#define TB2_BIN2 5


// -------------------------
// Motor command queue
// -------------------------

QueueHandle_t motorQueue;

MotorCommand currCommand;


// -------------------------
// Helper function
// -------------------------

void setMotor(int pwmPin, int in1, int in2, int speed)
{
    speed = constrain(speed, -255, 255);

    if (speed > 0)
    {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        analogWrite(pwmPin, speed);
    }
    else if (speed < 0)
    {
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        analogWrite(pwmPin, -speed);
    }
    else
    {
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        analogWrite(pwmPin, 0);
    }
}


// -------------------------
// Stop
// -------------------------

void stopRobot()
{
    currCommand = {0, 0, 0, 0};

    if (motorQueue != NULL)
    {
        xQueueOverwrite(motorQueue, &currCommand);
    }
}


// -------------------------
// Movement commands
// -------------------------

void moveForward(int speed)
{
    currCommand = {speed, speed, speed, speed};

    if (motorQueue != NULL)
    {
        xQueueOverwrite(motorQueue, &currCommand);
    }
}


void moveBackward(int speed)
{
    currCommand = {-speed, -speed, -speed, -speed};

    if (motorQueue != NULL)
    {
        xQueueOverwrite(motorQueue, &currCommand);
    }
}


void turnLeft(int speed)
{
    currCommand = {-speed, speed, -speed, speed};

    if (motorQueue != NULL)
    {
        xQueueOverwrite(motorQueue, &currCommand);
    }
}


void turnRight(int speed)
{
    currCommand = {speed, -speed, speed, -speed};

    if (motorQueue != NULL)
    {
        xQueueOverwrite(motorQueue, &currCommand);
    }
}


// -------------------------
// Print current command
// -------------------------

void printMotors()
{
    Serial.print("FL: ");
    Serial.print(currCommand.frontLeft);

    Serial.print(" FR: ");
    Serial.print(currCommand.frontRight);

    Serial.print(" BL: ");
    Serial.print(currCommand.backLeft);

    Serial.print(" BR: ");
    Serial.println(currCommand.backRight);
}


// -------------------------
// Motor FreeRTOS task
// -------------------------

void motorTask(void *parameter)
{
    MotorCommand command;

    while (true)
    {
        if (xQueueReceive(motorQueue, &command, portMAX_DELAY))
        {
            currCommand = command;

            setMotor(
                TB1_PWMA,
                TB1_AIN1,
                TB1_AIN2,
                command.frontLeft
            );

            setMotor(
                TB1_PWMB,
                TB1_BIN1,
                TB1_BIN2,
                command.frontRight
            );

            setMotor(
                TB2_PWMA,
                TB2_AIN1,
                TB2_AIN2,
                command.backLeft
            );

            setMotor(
                TB2_PWMB,
                TB2_BIN1,
                TB2_BIN2,
                command.backRight
            );

            printMotors();
        }
    }
}
