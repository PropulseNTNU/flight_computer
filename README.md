# Flight Computer

This repository contains the code necessary to run the flight computer including sensors and the state machine.


## Getting Started

Start by making a directory flight_computer and clone this repository inside to it.
```
cd
mkdir flight_computer && cd $_
git clone https://github.com/PropulseNTNU/Flight-Computer.git
```

### Prerequisites

What things you need to install

```
Arduino
Teensyduino - https://www.pjrc.com/teensy/td_download.html
```

## Running the code on the Teensy 3.6

Follow the following guide to connect the Teensy 3.6 to Arduino: 
https://www.pjrc.com/teensy/tutorial.html

Simply open the sensor_interface.ino file using the Arduino IDE and hit upload.

### Editing the code/test code

If you would like to add running code on the different states of the FSM,
this can be done by the following procedure:

```
1. Locate the state xxxx you would like to edit code on, this can be found under:
src/FSM/states
2. Put your code/changes inside the xxxx_state.cpp file
3. If you would like to only test your state, edit the START_STATE variable inside
the sensor_interface.ino file to XXXX in capital letters.
4. If you would like to test the entry of the state, locate the previous state
under src/FSM inside the states.h file(The previous state inside the enum state).
5. Simply save all changes and then hit upload.
```

## Authors

* **Kevin Kaldvansvik** - *Initial work* - [Kevinkald](https://github.com/Kevinkald)

See also the list of [contributors](https://github.com/SensorInterface/contributors) who participated in this project.
