#!/usr/bin/env python

import serial
import time
import logging
logging.basicConfig(level=logging.DEBUG)

NSAMP = 250
R = 12.0
DT = 0.02

if __name__ == "__main__":

    print("EW202 lab 5.3 proportional control test program")

    logging.debug("opening serial port") 
    ser = serial.Serial('/dev/ttyUSB0',9600,1)

    logging.debug("sending go command {0},{1}\n".format(NSAMP,R))
    ser.write("{0},{1}\n".format(NSAMP,R))
    
    logging.debug("receiving data")
    for i in range(NSAMP):
        line = ser.readline()
        print(line)
        #time.sleep(DT)

    logging.debug("cleaning up")
    ser.close()
    
