import serial
import serial.tools.list_ports as portsList


ser = serial.Serial()
key = 'USB VID:PID=0403:6001 SER=A10KQPQ2A'
ports = portsList.comports()

def Authorization():
    for port,desc,hwid in sorted(ports):
        if key in hwid:
            print("Authorized Device Found!")
            print("Authorized Device Connected at:",port)
            print("Opening Serial Port and Recieving Data...")
            return port


def initSerial():
    COM = Authorization()
    ser.port = COM
    ser.baudrate = 115200
    ser.stopbits = serial.STOPBITS_ONE
    ser.bytesize = 8
    ser.parity = serial.PARITY_NONE
    ser.rtscts = 0 
    


def main():
    initSerial()
    ser.open()
    while True:
        mHex = ser.read()
        mHex = mHex.decode("utf-8","ignore")
        if len(mHex)!= 0:
            print(mHex, end = '', flush = True)


if __name__ == "__main__":
    try:
        main()
    except serial.serialutil.SerialException:
        print("Authorized Device Not Found!")

    
