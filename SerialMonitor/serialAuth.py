import serial
import numpy as np
import serial.tools.list_ports as portList

ports = portList.comports()

for port,desc,hwid in sorted(ports):
    if 'USB VID:PID=0403:6001 SER=A10KQPQ2A' in hwid:
        print("Device Authorized")
        COM = port
        print("Authorized Device Connected at: ",port)
    
