
"""""
import tkinter as tk
from tkinter import *
from tkinter import filedialog
import numpy as np
import matplotlib

matplotlib.use('TkAgg')
import matplotlib.pyplot as plt
from matplotlib.widgets import Button
import serial as serial
import time
import os.path
from matplotlib.widgets import TextBox

global chosie
chosie = 0

import serial as ser
import time
# in this example we send a character, and receive a string in response only if the start character was 'u'

def ShowMenu(): #Creating Menu

    Manual_control_btn = Button(root, text="Manual control of motor based machine", padx=40, pady=20,
                                command=First)
#    Joystick_painter_btn = Button(root, text="Joystick based PC painter", command=Second(root))
#    Stepper_Motor_Calibration_btn = Button(root, text="Stepper Motor Calibration", command=Thired(root))
#    Script_Mode_btn = Button(root, text="Script Mode", command=Forth(root))

    Manual_control_btn.grid(row=1)
#    Joystick_painter_btn.grid(row=2)
#    Stepper_Motor_Calibration_btn(row=3)
 #   Script_Mode_btn.grid(row=4)

def First():
    global root
    chosie = 1
    root.quit()
def main():
    while(1):
        ShowMenu()

    s = ser.Serial('COM13', baudrate=9600, bytesize=ser.EIGHTBITS,
                   parity=ser.PARITY_NONE, stopbits=ser.STOPBITS_ONE,
                   timeout=1)  # timeuout of 1 sec so that the read and write operations are blocking,
    # after the timeout the program continues
    enableTX = True
    WaitForSending = True
    inChar = 's'
    # clear buffers
    s.reset_input_buffer()
    s.reset_output_buffer()

    while (1):
        while (WaitForSending):
            while (s.in_waiting > 0):  # while the input buffer isn't empty
                line = s.read_until('\0')  # read  from the buffer until the terminator is received,
                s.flushInput()
                time.sleep(0.25)  # delay for accurate read/write operations on both ends
                print(line.decode("ascii"))
                if (s.in_waiting == 0):
                    enableTX = True
                    WaitForSending = False
        #ShowMenu(line.decode("ascii"));
        while (s.out_waiting > 0 or enableTX):  # while the output buffer isn't empty
            inChar = input("Enter char:")
            bytesChar = bytes(inChar, 'ascii')
            time.sleep(0.25)  # delay for accurate read/write operations on both ends
            s.write(bytesChar)
            if s.out_waiting == 0 and '8' in inChar:
                enableTX = False
                WaitForSending = True
            if s.out_waiting == 0 and '4' in inChar:
                new_x = input("Enter new X[ms]:")
                bytesChar = bytes(new_x + '\0', 'ascii')
                time.sleep(0.25)  # delay for accurate read/write operations on both ends
                s.write(bytesChar)
                enableTX = False
                WaitForSending = True


from tkinter import *

root = Tk()
root.title('Menu')


def open1():
    global my_img
    top = Toplevel()
    top.title('Manual control of motor based machine')
    btn5 = Button(top, text="close window", command=top.destroy).pack()

def open2():
	global my_img
	top = Toplevel()
	top.title('My Second Window')
	btn5 = Button(top, text="close window", command=top.destroy).pack()

def open3():
    global my_img
    top = Toplevel()
    top.title('My Second Window')
    btn5 = Button(top, text="close window", command=top.destroy).pack()

def open4():
    global my_img
    top = Toplevel()
    top.title('My Second Window')
    btn1 = Button(top, text="c1", command=open1).pack()
    btn2 = Button(top, text="close window", command=open2).pack()
    btn3 = Button(top, text="close window", command=open3).pack()


Manual_control_btn = Button(root, text="Manual control of motor based machine", padx=0, pady=20,
                                command=open1).pack()
Joystick_painter_btn = Button(root, text="Joystick based PC painter", padx=40, pady=20,
                                command=open2).pack()
Stepper_Motor_Calibration_btn = Button(root, text="Stepper Motor Calibration", padx=40, pady=20,
                                command=open3).pack()
Script_Mode_btn = Button(root, text="Script Mode", padx=80, pady=20,
                                command=open3).pack()





mainloop()

"""
import tkinter as tk
import turtle
import tkinter.font as font
from turtle import *
from tkinter import filedialog
import serial as ser
import time
from tkinter.messagebox import showinfo
'''
    while (1):
        while(WaitForSending):
            while (s.in_waiting > 0):  # while the input buffer isn't empty
                line = s.read_until('\0')  # read  from the buffer until the terminator is received,
                s.flushInput()
                time.sleep(0.25)  # delay for accurate read/write operations on both ends
                print(line.decode("ascii"))
                if (s.in_waiting == 0):
                    enableTX = True
                    WaitForSending = False
        while (s.out_waiting > 0 or enableTX):  # while the output buffer isn't empty
            inChar = input("Enter char:")
            bytesChar = bytes(inChar, 'ascii')
            time.sleep(0.25)  # delay for accurate read/write operations on both ends
            s.write(bytesChar)
            if s.out_waiting == 0 and '8' in inChar:
                enableTX = False
                WaitForSending = True
            if s.out_waiting == 0 and '4' in inChar:
                new_x = input("Enter new X[ms]:")
                bytesChar = bytes(new_x + '\0', 'ascii')
                time.sleep(0.25)  # delay for accurate read/write operations on both ends
                s.write(bytesChar)
                enableTX = False
                WaitForSending = True
'''


class Menu:


    def __init__(self, master):
        self.master = master
        self.master.geometry("400x300")
        self.show_widgets()

    def show_widgets(self):
        self.frame = tk.Frame(self.master)
        self.master.title("Menu")
        self.create_button("Manual control of motor based machine ", Win_Motor_Control) #Win2
        self.create_button_for_painter("Joystick based PC painter", Win_Painter)#Win2
        self.create_button("Stepper Motor Calibration", Win_Stepper_Calibration)#Win2
        self.create_button("Script Mode", Win_Script)#Win3
        self.frame.pack()

    def create_button_for_script_mode(self, text, _class):
        "Button that creates a new window"
        tk.Button(
            self.frame, text=text,
            command=lambda: self.open_file()).pack()

    def open_file(self):
        self.root = tk.Tk()
        self.root.withdraw()
        self.file_path = filedialog.askopenfilename()
        print(self.file_path)

    def create_button(self, text, _class):
        "Button that creates a new window"
        tk.Button(
            self.frame, text=text,
            command=lambda: self.new_window(_class)).pack()
    def create_button_for_painter(self, text, _class):
        "Button that creates a new window"
        tk.Button(
            self.frame, text=text,
            command=lambda: self.drawing()).pack()

    def dragging(self,x, y):  # These parameters will be the mouse position
        t = Turtle("turtle")
        t.speed(-1)
        t.ondrag(None)
        t.setheading(t.towards(x, y))
        t.goto(x, y)
        t.ondrag(self.dragging)

    def clickRight(self):
        t = Turtle("turtle")
        t.speed(-1)
        t.clear()

    def drawing(self):  # This will run the program
        screen = Screen()
        t = Turtle("turtle")
        t.speed(-1)
        t.clear()
        t.ondrag(self.dragging)  # When we drag the turtle object call dragging
        turtle.onscreenclick(self.clickRight, 3)

        screen.mainloop()  # This will continue running main()






    def new_window(self, _class):
        global win2, win3, win4, win5

        try:
            if _class == Win_Painter:
                if win2.state() == "normal":
                    win2.focus()
        except:
            win2 = tk.Toplevel(self.master)
            _class(win2)
        try:
            if _class == Win_Motor_Control:
                if win2.state() == "normal":
                    win2.focus()
        except:
            win2 = tk.Toplevel(self.master)
            _class(win2)
        try:
            if _class == Win_Script:
                if win3.state() == "normal":
                    win3.focus()
        except:
            win3 = tk.Toplevel(self.master)
            _class(win3)

        try:
            if _class == Win_Stepper_Calibration:
                if win4.state() == "normal":
                    win4.focus()
        except:
            win4 = tk.Toplevel(self.master)
            _class(win4)

        try:
            if _class == Win_Reset_Motor:
                if win5.state() == "normal":
                    win5.focus()
        except:
            win5 = tk.Toplevel(self.master)
            _class(win5)

        try:
            if _class == Win_steps:
                if motor_flag == 0:
                    if win4.state() == "normal":
                        win4.focus()
        except:
            win4 = tk.Toplevel(self.master)
            _class(win4)


    def close_window(self):
        self.master.destroy()

class Win_Motor_Control(Menu):
    def __init__(self, master):
        self.master = master
        self.master.title("Motor_Control")
        self.master.geometry("400x200+200+200")
        self.show_widgets()

    def show_widgets(self):
        self.frame = tk.Frame(self.master, bg="green")
        self.quit = tk.Button(
        self.frame, text=f"Quit this window",
            command=self.close_window)
        self.quit.pack()
        self.label = tk.Label(
            self.frame, text="Please Calibrate the motor first")
        self.label.pack()
        self.frame.pack()

class Win_Painter(Menu):
    def __init__(self, master):
        self.master = master
        self.master.title("Window n.3")
        self.master.geometry("400x200+200+200")
        self.show_widgets()

    def show_widgets(self):
        self.frame = tk.Frame(self.master, bg="green")
        self.quit = tk.Button(
            self.frame, text=f"Quit this window n. 3",
            command=self.close_window)
        self.quit.pack()
        self.label = tk.Label(
            self.frame, text="THIS IS ONLY IN THE THIRD WINDOW")
        self.label.pack()
        self.frame.pack()

class Win_Stepper_Calibration(Menu):
    def __init__(self, master):
        self.master = master
        self.master.title("Stepper_Calibration")
        self.master.geometry("400x200+200+200")
        self.show_widgets()

    def show_widgets(self):
        self.frame = tk.Frame(self.master, bg="pink")
        #self.label = tk.Label(self.frame, text="You need to calibrate the motor first")
        self.quit = tk.Button(
        self.frame, text=f"Quit this window",
            command=self.close_window)
        self.quit.pack()
        self.create_button("Clibrate the stepper motor", Win_Reset_Motor)  # Win2
        self.create_button("calculate step number and the angle" , Win_steps)  # Win2
        self.label = tk.Label(
            self.frame, text="Need to calibrate the Motor before")
        #self.label.pack()
        self.frame.pack()


class Win_Script(Menu):  #Win3
    def __init__(self, master):

        self.master = master
        self.master.title("Window n.2")
        self.master.geometry("400x100+200+200")
        self.show_widgets()

    def show_widgets(self):
        "A frame with a button to quit the window"
        self.frame = tk.Frame(self.master, bg="red")
        self.quit_button = tk.Button(
            self.frame, text=f"Quit this window n. 2",
            command=self.close_window)
        self.quit_button.pack()
        self.create_button_for_script_mode("Please select a script", Win_Script)
        self.create_button_for_script_mode("Please select a script", Win_Script)
        self.create_button_for_script_mode("Please select a script", Win_Script)
        self.frame.pack()

class Win_Reset_Motor(Menu):
    def __init__(self, master):
        self.master = master
        self.master.title("Reset Motor")
        self.master.geometry("400x200+200+200")
        self.show_widgets()
        enableTX = True
        while (s.out_waiting > 0 or enableTX):
            inChar = '5'
            bytesChar = bytes(inChar, 'ascii')
            time.sleep(0.25)  # delay for accurate read/write operations on both ends
            s.write(bytesChar)
            if s.out_waiting == 0:
                enableTX = False

    def show_widgets(self):
        self.frame = tk.Frame(self.master, bg="green")
        self.quit = tk.Button(
            self.frame, text=f"Quit this window n. 3",
            command=self.close_window)
        tk.Button(
            self.frame, text=f"Click here when the motor is on the blue line",
            command=self.end_calbratione).pack()
        self.quit.pack()
       # self.label.pack()
        self.frame.pack()

    def end_calbratione(self):
        enableTX = True
        while(s.out_waiting > 0 or enableTX):
            inChar = '6'
            bytesChar = bytes(inChar, 'ascii')

            s.write(bytesChar)
            time.sleep(0.25)  # delay for accurate read/write operations on both ends
            enableTX = False
            self.close_window()


class Win_steps(Menu):
    def __init__(self, master):
        self.master = master
        self.master.title("Reset Motor")
        self.master.geometry("400x200+200+200")
        self.show_widgets()

    def show_widgets(self):
        self.frame = tk.Frame(self.master, bg="green")
        self.quit = tk.Button(
            self.frame, text=f"Quit this window n. 3",
            command=self.close_window)
        self.quit.pack()
        self.label = tk.Label(
            self.frame, text="THIS IS ONLY IN THE THIRD WINDOW")
        self.label.pack()
        self.frame.pack()



def exit_menu(root):
    global menu_flag
    menu_flag = 0
    root.destroy()
    root.quit()

def menu_chosie1(root):
    global menu
    menu = 1
    root.destroy()
    root.quit()
def menu_chosie2(root):
    global menu
    menu = 2
    root.destroy()
    root.quit()
def menu_chosie3(root):
    global menu
    menu = 3
    root.destroy()
    root.quit()
def menu_chosie4(root):
    global menu
    menu = 4
    root.destroy()
    root.quit()
# Option 3 at menu chosie
def calabrtion_chosie(root):
    global cal_step_chosie
    cal_step_chosie = 1
    root.destroy()
    root.quit()
def step_chosie(root):
    global cal_step_chosie
    cal_step_chosie = 2
    root.destroy()
    root.quit()

def close_windows(root):
    global flag
    flag = 0
    root.destroy()
    root.quit()
def joystick():
    global  p
    p = p + 1
    root.after(100, joystick())


def checkPostionInfo():
    global s, joyStickInfo, middle, newPhi, penType,old_joyStickInfo
    WaitForSending = True
    enableTX = True
    while (s.out_waiting > 0 or enableTX):
        inChar = '2'
        bytesChar = bytes(inChar, 'ascii')
        s.write(bytesChar)
        time.sleep(0.25)  # delay for accurate read/write operations on both ends
        if s.out_waiting == 0:
            enableTX = False
    while (WaitForSending):  # Wating to get info
        while (s.in_waiting > 0):  # while the input buffer isn't empty
            line = s.read_until('\0')  # read  from the buffer until the terminator is received,
            s.flushInput()
            time.sleep(0.25)  # delay for accurate read/write operations on both ends
            joyStickInfo = line.decode("ascii")
            if (s.in_waiting == 0):
                enableTX = True
        WaitForSending = False
#    if(joyStickInfo != old_joyStickInfo):
    middle = joyStickInfo[0:1]
    penType = joyStickInfo[1:2]
    newPhi = int(joyStickInfo[2:5])
    #old_joyStickInfo = joyStickInfo
    movment()


def movment():
    global middle, newPhi, penType, oldPhi

    if (middle == '1'):
        return
    else:
        if (newPhi != oldPhi):
            turtle.left(oldPhi - newPhi)
            oldPhi = newPhi
        turtle.fd(3)
        if (penType == '1'):
            turtle.color('black')
            turtle.fillcolor('black')
            turtle.pd()
        else:
            if (penType == '2'):
                turtle.color('white')
                turtle.fillcolor('red')
                turtle.pd()
            else:
                turtle.pu()
                turtle.fillcolor('yellow')

def quitTurttle(x, y):
    global stopTurttle
    stopTurttle = False

def fileUpload(root):
    global fileAmount

    filename = filedialog.askopenfilename()
    fileObject = open(filename, 'r')
    script = fileObject.read()
    #script = script.replace("\n", "")
    script = chr(fileAmount +ord('G')) + script
    s.reset_output_buffer()
    for i in range(0, len(script)):
        s.write(bytes(script[i], 'ascii'))
    fileAmount = fileAmount + 1
    fileObject.close()
    root.destroy()

def runFile(fileNum):
    enableTX = True
    while (s.out_waiting > 0 or enableTX):
        inChar = fileNum
        bytesChar = bytes(inChar, 'ascii')
        s.write(bytesChar)
        time.sleep(0.25)  # delay for accurate read/write operations on both ends
        if s.out_waiting == 0:
            enableTX = False


def popUpwindow(msg):
    showinfo(title='', message=msg)


def main():
    global root, menu, menu_flag, cal_step_chosie, flag,p, joyStickInfo, s, stopTurttle,\
        oldPhi, uploadedFile, fileAmount, old_joyStickInfo, middle, newPhi ,penType
    uploadedFile = 0
    enableTX = True
    stopTurttle = True
    s = ser.Serial('COM18', baudrate=9600, bytesize=ser.EIGHTBITS,
                   parity=ser.PARITY_NONE, stopbits=ser.STOPBITS_ONE,
                   timeout=1)   # timeuout of 1 sec so that the read and write operations are blocking,
                                # after the timeout the program continues
    WaitForSending = True
    inChar = 's'
    # clear buffers
    s.flush()
    s.reset_input_buffer()
    s.reset_output_buffer()
    motor_flag = 0
    p = 1
    flag = 1
    menu_flag = 1
    joyStickInfo = 's'
    stepsInfo = 's'
    while(menu_flag):
        root = tk.Tk()
        #app = Menu(root)
        menu = 0
        root.geometry("300x200")
        root.title("Menu")
        root.eval('tk::PlaceWindow . center')
        button = tk.Button(root, text='Manual control of motor based machine',
                  width=120,
                  command=lambda: menu_chosie1(root)).pack(pady = 5)
        tk.Button(root, text='Joystick based PC painter', width=120, command=lambda: menu_chosie2(root)).pack(pady = 5)
        tk.Button(root, text='Stepper Motor Calibration', width=120, command=lambda: menu_chosie3(root)).pack(pady =5)
        tk.Button(root, text='Script Mode', width=120, command=lambda: menu_chosie4(root)).pack(pady =5)
        tk.Button(root, text='Exit menu', width=120, command=lambda: exit_menu(root)).pack(pady =5)
        root.mainloop()

        if menu_flag:
# ------------------Choise 1 in menu --------------------------------------------------------------------------
            if menu==1:

                if motor_flag:
                    enableTX = True
                    while (s.out_waiting > 0 or enableTX):
                        inChar = '1'
                        bytesChar = bytes(inChar, 'ascii')
                        s.write(bytesChar)
                        time.sleep(0.25)  # delay for accurate read/write operations on both ends
                        if s.out_waiting == 0:
                            enableTX = False
                    root = tk.Tk()
                    root.geometry("300x100")
                    root.title("Motor manual control")
                    root.eval('tk::PlaceWindow . center')
                    labelframe = tk.LabelFrame(root, text="",background='green')
                    labelframe.pack(fill="both", expand="yes")
                    tk.Label(labelframe, text="You can now control the motor").pack(pady = 20)
                    tk.Button(root, text='End controling', command=lambda: close_windows(root)).pack()
                    root.mainloop()
                    enableTX = True
                    while (s.out_waiting > 0 or enableTX):
                        inChar = '6'
                        bytesChar = bytes(inChar, 'ascii')
                        s.write(bytesChar)
                        time.sleep(0.25)  # delay for accurate read/write operations on both ends
                        if s.out_waiting == 0:
                            enableTX = False
                else:
                    root = tk.Tk()
                    root.geometry("300x300")
                    root.title("Motor manual control")
                    tk.Label(root, text='You first need to calbriate the motor').pack()
                    root.mainloop()
#------------------Choise 2 in menu --------------------------------------------------------------------------
            if menu==2:
                middle = '1'
                oldPhi = 0
                flag = 0
                newPhi = 0
                penType = '1'
                stopTurttle = True
                joyStickInfo = '0'
                old_joyStickInfo = '0'
                drawing_area = turtle.Screen()
                drawing_area.setup(width=1200, height=600)
                drawing_area.onclick(quitTurttle)
                #if middle:
                turtle.pensize(4)
                turtle.speed(0)
                #turtle.shape('arrow')
                #turtle.color('black')
                turtle.ht()
                turtle.left(180)
                turtle.st()
                turtle.color('black')
                turtle.fillcolor('black')
                while stopTurttle:
                    checkPostionInfo()
                drawing_area.bye()
                enableTX = True
                while (s.out_waiting > 0 or enableTX):
                    inChar = '9'
                    bytesChar = bytes(inChar, 'ascii')
                    s.write(bytesChar)
                    time.sleep(0.25)  # delay for accurate read/write operations on both ends
                    if s.out_waiting == 0:
                        enableTX = False
#------------------Choise 3 in menu --------------------------------------------------------------------------
            if menu==3:
                motor_flag = 1
                cal_step_chosie = 0
                root = tk.Tk()
                root.geometry("300x100")
                root.title("Menu")
                root.eval('tk::PlaceWindow . center')
                tk.Button(root, text='Calabrtion', width=120, command=lambda: calabrtion_chosie(root)).pack(pady = 10)
                if motor_flag:
                    tk.Button(root, text='Steper', width=120, command=lambda: step_chosie(root)).pack(pady = 10)
                else:
                    tk.Button(root, text='Steper', width=120, background='red'
                              ,command=lambda:popUpwindow('You first need to calibrate the motor')).pack(pady=10)
                root.mainloop()
                if cal_step_chosie==1:
                    enableTX = True
                    while (s.out_waiting > 0 or enableTX):
                        inChar = '5'
                        bytesChar = bytes(inChar, 'ascii')
                        s.write(bytesChar)
                        time.sleep(0.25)  # delay for accurate read/write operations on both ends
                        if s.out_waiting == 0:
                            enableTX = False
                    root = tk.Tk()
                    root.geometry("200x100")
                    root.title("Menu")
                    root.eval('tk::PlaceWindow . center')
                    labelframe = tk.LabelFrame(root, text="", background='')
                    labelframe.pack(fill="both", expand="yes")
                    tk.Label(labelframe, text="Click the button when the motor\n is ont the blue line").pack(pady=5)
                    tk.Button(root, text='Click here', width=120, background='green', command=lambda: close_windows(root)).pack(pady = 10)
                    root.mainloop()
                    enableTX = True
                    while (s.out_waiting > 0 or enableTX):
                        inChar = '9'
                        bytesChar = bytes(inChar, 'ascii')
                        s.write(bytesChar)
                        time.sleep(0.25)  # delay for accurate read/write operations on both ends
                        enableTX = False
                    motor_flag = 1
                if cal_step_chosie==2:
                    enableTX = True
                    while (s.out_waiting > 0 or enableTX):
                        inChar = '3'
                        bytesChar = bytes(inChar, 'ascii')
                        s.write(bytesChar)
                        time.sleep(0.25)  # delay for accurate read/write operations on both ends
                        if s.out_waiting == 0:
                            enableTX = False
                    root = tk.Tk()
                    root.geometry("200x100")
                    root.title("Menu")
                    root.eval('tk::PlaceWindow . center')
                    labelframe = tk.LabelFrame(root, text="", background='')
                    labelframe.pack(fill="both", expand="yes")
                    tk.Label(labelframe, text="Click the button when the motor\n doing a full circle").pack(pady=5)
                    tk.Button(root, text='Click here', width=120, background='green', command=lambda: close_windows(root)).pack(pady=10)
                    root.mainloop()
                    enableTX = True
                    while (s.out_waiting > 0 or enableTX):
                        inChar = '6'
                        bytesChar = bytes(inChar, 'ascii')
                        s.write(bytesChar)
                        time.sleep(0.25)  # delay for accurate read/write operations on both ends
                        enableTX = False
                    while (WaitForSending):  # Wating to get info
                        while (s.in_waiting > 0):  # while the input buffer isn't empty
                            #time.sleep(0.40)  # delay for accurate read/write operations on both ends
                            line = s.read_until('\0')  # read  from the buffer until the terminator is received,
                            s.flushInput()
                            stepsInfo = line.decode("ascii")
                            if (s.in_waiting == 0):
                                WaitForSending = False
                    stepsPhi = stepsInfo[0:1] + '.' + stepsInfo[1:3]
                    steps = stepsInfo[3:]
                    popUpwindow('The amount of steps in full circle: ' + steps +'\n The angal is: ' + stepsPhi)
                    enableTX = True
                    while (s.out_waiting > 0 or enableTX):
                        inChar = '9'
                        bytesChar = bytes(inChar, 'ascii')
                        s.write(bytesChar)
                        time.sleep(0.25)  # delay for accurate read/write operations on both ends
                        enableTX = False
#------------------Choise 4 in menu --------------------------------------------------------------------------
            if menu==4:
                fileAmount = 0
                enableTX = True
                while (s.out_waiting > 0 or enableTX):
                    inChar = '4'
                    bytesChar = bytes(inChar, 'ascii')
                    s.write(bytesChar)
                    time.sleep(0.25)  # delay for accurate read/write operations on both ends
                    if s.out_waiting == 0:
                        enableTX = False
                root = tk.Tk()
                root.geometry("300x300")
                root.title("Menu")
                root.eval('tk::PlaceWindow . center')
                tk.Button(root, text='Upload file #1', command=lambda: fileUpload(root)).pack()
                tk.Button(root, text='Done Upload', command=lambda: root.destroy()).pack()
                root.mainloop()
                root = tk.Tk()
                root.geometry("300x300")
                root.title("Menu")
                root.eval('tk::PlaceWindow . center')
                tk.Button(root, text='Upload file #2', command=lambda: fileUpload(root)).pack()
                tk.Button(root, text='Done Upload', command=lambda: root.destroy()).pack()
                root.mainloop()
                root = tk.Tk()
                root.geometry("300x300")
                root.title("Menu")
                root.eval('tk::PlaceWindow . center')
                tk.Button(root, text='Upload file #3', command=lambda: fileUpload(root)).pack()
                tk.Button(root, text='Done Upload', command=lambda: root.destroy()).pack()
                root.mainloop()
                enableTX = True
                while (s.out_waiting > 0 or enableTX):
                    inChar = 'x'
                    bytesChar = bytes(inChar, 'ascii')
                    s.write(bytesChar)
                    time.sleep(0.25)  # delay for accurate read/write operations on both ends
                    if s.out_waiting == 0:
                        enableTX = False
                root = tk.Tk()
                root.geometry("300x300")
                root.title("Menu")
                root.eval('tk::PlaceWindow . center')
                if fileAmount == 1:
                    tk.Button(root, text='Script 1', command=lambda: runFile('A')).pack()
                elif fileAmount == 2:
                    tk.Button(root, text='Script 1', command=lambda: runFile('A')).pack()
                    tk.Button(root, text='Script 2', command=lambda: runFile('B')).pack()
                elif fileAmount == 3:
                    tk.Button(root, text='Script 1', command=lambda: runFile('A')).pack()
                    tk.Button(root, text='Script 2', command=lambda: runFile('B')).pack()
                    tk.Button(root, text='Script 3', command=lambda: runFile('C')).pack()
                tk.Button(root, text='Done with scripts', command=lambda: root.destroy()).pack()
                root.mainloop()

if __name__ == '__main__':
    main()
#------------------------------------------------------------------------------------------------








'''- adding label to the main menu
if motor_flag=1 we neeed to calibration.
option 1- will not work if motoerflag is not 0.
open just window and label.

option 2- need to be open, not locking. need to open painter.
option 3 - need to fix button names, again, 2 buttons, and label

12:15
'''
