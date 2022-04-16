import serial
import serial.tools.list_ports

for info in serial.tools.list_ports.comports():
    print(info.hwid)
