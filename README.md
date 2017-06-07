# README #

### What is this project for? ###

* This project is an implementation of a smart screwdriver which is operated via Bluetooth through an Android App.
* It consists of 2 motors which allow us to move the screwdriver vertically up and down, as well as to rotate a screwdriver head coupled with another motor.
* The project was made for the course ELEC3607 at The University of Sydney in June 2017.

### How do I get set up? ###

* Mount a SEEED Bluetooth Shield on top of Arduino DUE
* Connect the Bluetooth TX/RX to DUE's SERIAL3
* Mount an ITEAD Dual Motor Driver on top of the Bluetooth Shield
* Power the Arduino and optionally the Motor Driver
* Connect Motors to Port X and Port Y of the Motor Driver
* Download the code and open it in Arduino Programmer.
* Upload the code to Arduino DUE.
* You will need the Android App that was made for this to interact with the device which can be found on this (https://bitbucket.org/rijulg/smart-screwdriver-android-app/overview), or you can customize the code to work with something else.

### Example ###
You can check out my version of the project at https://www.youtube.com/watch?v=kUv5TsbPHqY

The hardware was made up of plastic sheet that I obtained from a container/box, along with a 3D printed rack and pinion. The components that were used in this implementation are:
* Arduino Due
* SEEED Bluetooth Shield
* ITEAD Dual Motor Driver (https://littlebirdelectronics.com.au/products/itead-dual-step-motor-driver-shield)
* Motor 1 (Mounted on the linear actuator) (http://au.element14.com/nanotec/sp2575m0206-a/stepper-motor-7-5deg-1-6n-cm/dp/4743209)
* Motor 2 (Drives the linear actutor) (http://au.element14.com/nanotec/sp3575m0906-a/stepper-motor-7-5deg-5vdc-7/dp/4743210)

For coupling the motor with the screwdriver philips head we made use of Screw Terminal Blocks which look like this ![18721524_10211679999968934_864984293_o.png](https://bitbucket.org/repo/MrnbdRr/images/693542252-18721524_10211679999968934_864984293_o.png)

### Who do I talk to? ###

* Rijul Gupta (rijulg@gmail.com)