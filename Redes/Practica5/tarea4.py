# Practica Pyton tarea 4
# acumule los datos durante 5 segundos, calcule el promedio y desviación estándar y los represente en tiempo real
# from datetime import time

import time
import serial
import matplotlib.pyplot as plt
import numpy as np

import matplotlib.animation as animation

PORT = "COM4"
baudrate = 115200
nombre_fichero = 'pr5tarea3redes'  + '.txt'

ax_data = []
ay_data = []
az_data = []

start_time = time.time()

fig, ax = plt.subplots()

ser = serial.Serial(PORT, baudrate)

def update(frame):
    global ax_data, ay_data, ay_data
    try:
        linea = ser.readline().decode('utf-8').strip()

        values=linea.split(',')
        if(len(values) == 3):
            ax_val= float(values[0])
            ay_val= float(values[1])
            az_val= float(values[2])

            ax_data.append(ax_val)
            ay_data.append(ay_val)
            az_data.append(az_val)

        if(time.time()-start_time > 5):
            mean_ax = np.mean(ax_data)
            mean_ay = np.mean(ay_data)
            mean_az = np.mean(az_data)
            std_ax = np.std(ax_data)
            std_ay = np.std(ay_data)
            std_az = np.std(az_data)
            print("Media AX:", mean_ax)
            print("Desviación AX:", std_ax)
            print("Media AY:", mean_ay)
            print("Desvicion AY:", std_ay)
            print("Media AZ:", mean_az)
            print("Desviacion AZ:", std_az)

            ax.clear()

            ax.plot(ax_data, ay_data)
            ax.set_title("Aceleración eje X (últimos 5 s)")
            ax.legend()

            ax_data = []
            ay_data = []
            az_data = []
            start_time = time.time()
    except:
    pass
ani = animation.FuncAnimation(fig=fig, func=update, frames=40, interval=30)
plt.show()









