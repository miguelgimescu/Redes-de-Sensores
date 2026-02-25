# Practica Pyton tarea 3
# acceder puerto serie y mostrar por pantalla
# from datetime import time
from base64 import decode

import serial
import time
PORT = "COM4"
baudrate = 115200
nombre_fichero = 'pr5tarea3redes'  + '.txt'
# f = open(nombre_fichero, 'w')
with open(nombre_fichero, 'w') as f:
    print("creando fichero")
    f.write("Aceleracion_X;Aceleracion_Y;Aceleracion_Z\n")
    try:
        ser = serial.Serial(PORT, baudrate)
        time.sleep(2)
        print("Serial opened")
        while True:
            linea=ser.readline().decode('utf-8').strip()
            print("dato recibido",linea)

            f.write(str(linea)+"\n")

    except serial.SerialException as e:
        print(f"Error de conexión: {e}")
