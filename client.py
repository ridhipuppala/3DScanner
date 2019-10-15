#!/usr/bin/env py
from time import sleep
import socket
import serial
ser = serial.Serial('/dev/ttyACM1', 9600) 


TCP_IP = '192.168.1.101'
TCP_PORT = 21000
BUFFER_SIZE = 20
#MESSAGE = "Hello, World!"
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))
while(1):

	#s.send(MESSAGE)
	data = s.recv(BUFFER_SIZE)
	ser.write(data)
	sleep(0.1)
	if(ser.read()):
		a=ser.read();
		print(a);
	print "received data:", data
	sleep(0.1)
s.close()

