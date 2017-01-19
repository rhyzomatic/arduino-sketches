'''
Created on 2011-12-02

@author: Bobby Wood
'''

## import the serial library
import serial

## Boolean variable that will represent 
## whether or not the arduino is connected
connected = False

## open the serial port that your ardiono 
## is connected to.
ser = serial.Serial("COM3", 9600)

## loop until the arduino tells us it is ready
while not connected:
    serin = ser.read()
    connected = True

## Wait until the arduino tells us it 
## is finished blinking

while True:
    print(ord(ser.read()))

## close the port and end the program
ser.close()