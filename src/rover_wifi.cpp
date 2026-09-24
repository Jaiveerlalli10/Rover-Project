#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "rover_wifi.h"
#include "motors.h"
#include "control.h"

const char* ssid = "ESP32_Rover";
const char* password = "rover123";

WebServer server(80);

void startWiFi() {

    WiFi.softAP(ssid, password);

    Serial.println("Wi-Fi started!");
    Serial.print("IP address: ");
    Serial.println(WiFi.softAPIP());

    // Main webpage
    server.on("/", []() {

        String html = R"rawliteral(
           <!DOCTYPE html>
<html>

<head>
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no">

    <title>ESP32 Rover</title>

    <style>

        * {
            box-sizing: border-box;
            user-select: none;
            -webkit-user-select: none;
            -webkit-touch-callout: none;
        }

        html, body {
            margin: 0;
            padding: 0;
            width: 100%;
            height: 100%;
            overflow: hidden;
            background: #000000;
            color: white;
            font-family: Arial, sans-serif;
            touch-action: none;
        }

        body {
            min-height: 100svh;
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
        }

        h1 {
            position: absolute;
            top: 5vh;
            margin: 0;

            font-size: clamp(20px, 6vw, 30px);
            letter-spacing: 4px;
            font-weight: bold;
        }

        .controller {

            --button-size: min(26vw, 105px);
            --gap: min(3vw, 12px);

            display: grid;

            grid-template-columns:
                var(--button-size)
                var(--button-size)
                var(--button-size);

            grid-template-rows:
                var(--button-size)
                var(--button-size)
                var(--button-size);

            gap: var(--gap);

            align-items: center;
            justify-items: center;
        }

        .reset-container {
            position: fixed;
            bottom: 20px;
            left: 0;
            width: 100%;
            text-align: center;
        }

        .reset {
            width: auto;
            height: auto;
            padding: 12px 30px;
            font-size: 18px;
            border-radius: 10px;
        }

        button {

            width: var(--button-size);
            height: var(--button-size);

            border: 2px solid white;
            border-radius: 50%;

            background: black;
            color: white;

            display: flex;
            align-items: center;
            justify-content: center;

            padding: 0;

            touch-action: none;

            -webkit-tap-highlight-color: transparent;
        }

        button:active {
            background: white;
        }

        /* CSS arrow */

        .arrow {

            width: 45%;
            height: 45%;

            background: white;

            clip-path: polygon(
                50% 0%,
                100% 40%,
                65% 40%,
                65% 100%,
                35% 100%,
                35% 40%,
                0% 40%
            );
        }

        button:active .arrow {
            background: black;
        }

        .arrow.right {
            transform: rotate(90deg);
        }

        .arrow.down {
            transform: rotate(180deg);
        }

        .arrow.left {
            transform: rotate(270deg);
        }

        /* Stop button */

        .stop {
            background: #c40000;
            border-color: #ff4444;

            font-size: clamp(14px, 4vw, 20px);
            font-weight: bold;
            letter-spacing: 1px;
        }

        .stop:active {
            background: #ff3333;
        }

        .empty {
            width: var(--button-size);
            height: var(--button-size);
        }

    </style>

</head>

<body>

    <h1>ESP32 ROVER</h1>


    <div class="controller">

        <!-- Top -->

        <div class="empty"></div>

        <button
            onpointerdown="startCommand('/forward')"
            onpointerup="stopCommand()"
            onpointercancel="stopCommand()"
            onpointerleave="stopCommand()">

            <span class="arrow up"></span>

        </button>

        <div class="empty"></div>


        <!-- Middle -->

        <button
            onpointerdown="startCommand('/left')"
            onpointerup="stopCommand()"
            onpointercancel="stopCommand()"
            onpointerleave="stopCommand()">

            <span class="arrow left"></span>

        </button>


        <!-- EMERGENCY STOP -->

        <button
            class="stop"
            onclick="fetch('/emergency')">

            STOP

        </button>


        <button
            onpointerdown="startCommand('/right')"
            onpointerup="stopCommand()"
            onpointercancel="stopCommand()"
            onpointerleave="stopCommand()">

            <span class="arrow right"></span>

        </button>


        <!-- Bottom -->

        <div class="empty"></div>

        <button
            onpointerdown="startCommand('/backward')"
            onpointerup="stopCommand()"
            onpointercancel="stopCommand()"
            onpointerleave="stopCommand()">

            <span class="arrow down"></span>

        </button>

        <div class="empty"></div>

    </div>


    <!-- RESET -->

    <div class="reset-container">

        <button
            class="reset"
            onclick="fetch('/reset')">

            RESET

        </button>

    </div>


    <script>

        function startCommand(command) {
            fetch(command);
        }

        function stopCommand() {
            fetch('/stop');
        }

    </script>


</body>

</html>
        )rawliteral";

        server.send(200, "text/html", html);
    });


    // Forward
    server.on("/forward", []() {
    moveForward(120);

    Serial.println("FORWARD");
    printMotors();

    server.send(200, "text/plain", "Moving forward");
});


   server.on("/backward", []() {
    moveBackward(120);

    Serial.println("BACKWARD");
    printMotors();

    server.send(200, "text/plain", "Moving backward");
});

server.on("/left", []() {
    turnLeft(120);

    Serial.println("LEFT");
    printMotors();

    server.send(200, "text/plain", "Turning left");
});

server.on("/right", []() {
    turnRight(120);

    Serial.println("RIGHT");
    printMotors();

    server.send(200, "text/plain", "Turning right");
});

server.on("/stop", []() {
    stopRobot();

    Serial.println("STOP");
    printMotors();

    server.send(200, "text/plain", "Stopped");
});


server.on("/emergency", []() {
    setEmergencyStop(true);

    Serial.println("EMERGENCY STOP");
    printMotors();

    server.send(200, "text/plain", "Emergency stop activated");
});


server.on("/reset", []() {
    setEmergencyStop(false);

    Serial.println("EMERGENCY STOP RESET");

    server.send(200, "text/plain", "Emergency stop reset");
});


server.begin();

Serial.println("Web server started!");
}


void handleWiFi() {
    server.handleClient();
}


void wifiTask(void *paramter) {
    while (true) {
        handleWiFi();

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}




