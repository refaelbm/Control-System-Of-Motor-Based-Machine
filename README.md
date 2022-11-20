# Control-System-Of-Motor-Based-Machine

Introduction:

In this project we want to design and implement a control system for a motor based machine that can be controlled by analog joystick and with serial communication channel with PC for remote control.

Program languages: C++, Python.

Programming Tools: CCS

Backend Tools: MSP430G2553(Personal kit), MSP430FG4619(Lab kit).
 

Design Scope:

 We write C++ code for the controller that will get data ,transmit data and control the motor. In total the controller will need to do 5 tasks.

 We write Python code for the GUI part that will give the user the option to communicate with the controller to run 4 tasks.

 

 The controller design:

 1. Performing a reset of the motor with user input.
 2. Sending motor data containing how many steps are needed for 360 degrees and how much is done in one step.
 3. Getting data from the joystick. 
 4. Write into the flash memory the text file that contains commands for the controller.
 5. Execute the desired text file the controller has in the flash.

 

 The GUI options:

 1. Reset motor and geting info about the motor.
 2. Enable control the joystick move the motor pointer to the wanted dagree.
 3. Enable control with the joystick for the painting option. 
 4. Upload up to 3 text files with commands and after uploading allow the user to select what script to run.

 The text file commands:

 ![image](https://user-images.githubusercontent.com/94614385/202896457-3482da63-14f2-4811-8102-80b57a33162a.png) 


 
 

Write a code for a CPU to control motor based machine with creating a comunction between with a CP for the GUI

The CPU need to do 6 tasks:

1) Moving the motor and waiting for the user input for the inital reset
2) Returning info about the motor as how much steps needed to be made for 360 degres and how much one steps is equal for the degres
3) Geting data from a joystick and with that controling the degre the motor need to be pointed
4) Sending data for the PC about the degere the joystick is pointing and what stage the pointer need to be
5) Geting from the PC up to 3 text fiels that have commands and save them into the flash memory
6) Geting from the PC which file(from the 3) to read and run the commands in the text 

The PC side need to able a GUI for the user the give 4 options:

1) Reseting the motor and geting data about the motor
2) Enable motor control with the joystick
3) Enable using the joystick to draw in a pinter(Used turtle) with 3 option draw ,erase and just moving the pointer
4) Uploading up to 3 text files and enable exucate after uploading 
