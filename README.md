<img width="4284" height="5712" alt="image" src="https://github.com/user-attachments/assets/c4dd1dd2-aa4e-424b-baf6-eea940189fc5" />



ESP32 Rover:
  A modular 4WD rover built around an ESP32, FreeRTOS, and wireless control.

  VIDEO: https://youtube.com/shorts/E6Apd3a_wUI?is=9W-wnkyobzcdhFxJ



OVERVIEW:
A modular 4WD rover built around an ESP32, using FreeRTOS for task management and a web-based
controller for wireless driving. The rover uses separate motor, WiFi and controller systems to
handle movement and safety features with autonomous navigation and an onboard TFT display
planned for future development.

 FEATURES:
  - Wireless driving from web-based controller
  - Forward/backward/left/right driving
  - FreeRTOS task structure
  - Software emergency stop
  - PWM motor speed control
  - TFT Display (in progress)
  - Autonomous Navigation (in progress)

HARDWARE:
  Controller
    -ESP32-WROOM-32
  Motor System
    - 4x TT Motors
    - 2x TB6612FNG Motor Drivers
  Power
  - 2x 18650 Li-ion batteries
  - 2S battery holder
  - LM2596 buck converter

  Planned
  - 3.5" ST7796S TFT
  - ultrasonic obstacle sensor

SOFTWARE:
  - C++
  - Arduino framework
  - PlatformIO
  - FreeRTOS
  - ESP32 WiFi
  - HTTP/web server
  - PWM motor speed control

I used a FreeRTOS structure to keep tasks organized as well as allow different parts of the rover
to run independently

SYSTEM ARCHITECTURE:
  - Phone:
      Allows for the access of the web-based controller and displays the interface
      of the controller for the rover
    
  - WiFi:
      The ESP32 creates its own WiFi for wireless communication
    
  - Web Server:
      Receives HTTP requests from the controller when an input is given
    
  - WiFi Task:
      Handles incoming web requests independently from the motor system
    
  - Motor Command Queue:
      Transfers motor commands from the WiFi task to the motor task.
      queue holds only one command at a time so the newer commands are always
      replacing the older commands so there is no delay of commands being built up
    
  - Motor Task:
      The current command gets executed and sends it to the TB motor boards
    
  - TB6612FNG:
      Receives the motor commands from the ESP32 and controls the direction and speed of the motors
    
  - 4 Motors:
      Moves the wheels of the rover

    PROJECT STRUCTURE:
    src
      - main.cpp:
          Initializes the rover and starts the FreeRTOS tasks
        
      - motors.cpp/motors.h:
          Handles motor control, movement commands, and the motor task.
        
      - rover_wifi.cpp/rover_wifi.h:
          Handles the WiFi network, web server, and WiFi task
        
      - control.cpp/control.h:
          Handles rover control states such as the emergency stop.

    MOTOR CONTROL:
    Each motor is controlled using
      - 2 GPIO pins for direction
      - 1 PWM pin for speed
   
    The rover converts movement command such as forward, backward, left, and right into
    individual speed values for each motor.

    EMERGENCY STOP:
    The rover has a software emergency stop button that will immediately stop the motors and
    prevent the new movement commands from being executed. emergencyStop = true, and for the rover
    to move again, the reset button must be pressed.

    Planned: The system will be able to automatically detect objects getting too close to the
    rover and the stop the car.

    ROADMAP:

    [x] 4WD motor control
    
    [x] Wireless web controller
    
    [x] FreeRTOS task structure
    
    [x] Motor command queue
    
    [x] Software emergency stop
    
    [ ] TFT display
    
    [x] Ultrasonic obstacle detection
    
    [ ] Autonomous navigation
    
    [ ] Wheel encoders
    
    [ ] PID motor control
    
    
          









