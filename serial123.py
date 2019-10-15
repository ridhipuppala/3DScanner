from time import sleep
import serial
import os
os.system('./lite')
os.system('./back')
ser = serial.Serial('/dev/ttyACM1', 9600) 
sleep(1)
i=0
for i in range (1,202):
	text_file = open("test.txt", "w")
	text_file.write(str(i))
	
	os.system('./cv')
	
	ser.write('a')
	while(1):
		if(ser.read()):
			#print 'q'
			break
#print "Scan is almost done :)"
os.system('./opengl')
#print "Are you satisfied with the scan??"
j=input()
file= open("feedback.txt",a)
file.write(a)
file.close()
#print "thank u for u r feedback :)"
