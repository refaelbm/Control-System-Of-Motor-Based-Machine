# Control-System-Of-Motor-Based-Machine

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
