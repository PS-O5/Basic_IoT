import serial as COMMSSerial
import serial as DriveSerial
import serial.tools.list_ports as portsList

COMMS = COMMSSerial.Serial()
Drive = DriveSerial.Serial()

def initSerialCOMMS():
    global COMMS
    COMMS.baudrate = 115200
    COMMS.port = 'COM9'
    COMMS.stopbits = COMMSSerial.STOPBITS_ONE
    COMMS.bytesize = 8
    COMMS.parity = COMMSSerial.PARITY_NONE
    COMMS.rtscts = 0

def initSerialDrive():
    global Drive
    Drive.baudrate = 115200
    Drive.port = 'COM5'
    Drive.stopbits = DriveSerial.STOPBITS_ONE
    Drive.bytesize = 8
    Drive.parity = DriveSerial.PARITY_NONE
    Drive.rtscts = 0

def main():
    initSerialCOMMS()
    initSerialDrive()
    COMMS.open()
    Drive.open()
    while True:
        hexData = COMMS.read()
        hexData = hexData.rstrip()
        hexData = hexData.decode("Ascii", "ignore")
        if len(hexData)!= 0:
            print(hexData, end = '', flush = True)
            Drive.write(hexData.encode())

if __name__ == "__main__":
    main()
