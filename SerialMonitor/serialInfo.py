import serial.tools.list_ports as portsList

ports = portsList.comports()

for port, desc, hwid in sorted(ports):
    print(port, desc, hwid)
