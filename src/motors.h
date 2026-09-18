#ifndef MOTORS_H
#define MOTORS_H

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

struct MotorCommand {
    int frontLeft;
    int frontRight;
    int backLeft;
    int backRight;
};

extern QueueHandle_t motorQueue;

void stopRobot();
void moveForward(int speed);
void moveBackward(int speed);
void turnLeft(int speed);
void turnRight(int speed);
void printMotors();

void motorTask(void *parameter);

#endif
