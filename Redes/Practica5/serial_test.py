# Practica Pyton tarea 2
# acceder puerto serie y mostrar por pantalla
# from datetime import time

import serial
import time
PORT = "COM4"
baudrate = 115200

try:
    ser = serial.Serial(PORT, baudrate)
    time.sleep(2)
    print("Serial opened")
    while True:
        linea=ser.readline()
        print("dato recibido",linea)
except serial.SerialException as e:
    print(f"Error de conexión: {e}")
