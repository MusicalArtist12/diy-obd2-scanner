import serial

ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=0.5)

while True:
    data = ser.read()
    string = data.decode("ascii")
    print(string, end="")

ser.close()