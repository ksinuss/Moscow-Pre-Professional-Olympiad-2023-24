#!/usr/bin/env python3
from serial import Serial
import time
if __name__ == '__main__':
    ser = Serial('/dev/ttyUSB0', 9600, timeout=1)
    ser.flush()
    while True:
        #if ser.in_waiting > 0:
            #line = ser.readline().decode('utf-8').rstrip()
            #print(line)
        ser.write(b'1')
        line = ser.readline().decode('utf-8').rstrip()
        print(line)
        time.sleep(1)