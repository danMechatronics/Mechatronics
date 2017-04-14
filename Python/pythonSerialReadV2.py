import serial #Import Serial Library
import socket
import time

addr_info = socket.getaddrinfo("192.168.4.1", 23)
addr = addr_info[0][-1]
s = socket.socket()
s.connect(addr)
arduinoSerialData = serial.Serial('com3',9600) 
#Create Serial port object called arduinoSerialData


while (1==1):
    if (arduinoSerialData.inWaiting()>0):
        myData = arduinoSerialData.readline()
        #myData=str(myData)
        #myData=myData[:-2]
        print (myData)
        #myData=myData + "\n"
        s.send(myData)

