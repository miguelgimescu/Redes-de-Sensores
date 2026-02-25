# Practica Python - Tarea 4
# Acumula datos 5 s, calcula media y desviación y los representa en tiempo real

import time
import serial
import matplotlib.pyplot as plt
import numpy as np
import matplotlib.animation as animation

PORT = "COM4"
baudrate = 115200

ax_data = []
ay_data = []
az_data = []

start_time = time.time()

fig, ax = plt.subplots()
ser = serial.Serial(PORT, baudrate)

def update(frame):
    global ax_data, ay_data, az_data, start_time

    try:
        linea = ser.readline().decode('utf-8').strip()
        values = linea.split(';')
        print(linea)

        if len(values) == 3:
            ax_data.append(float(values[0]))
            ay_data.append(float(values[1]))
            az_data.append(float(values[2]))

        # Cada 5 segundos
        if time.time() - start_time > 5 and len(ax_data) > 0:

            mean_ax = np.mean(ax_data)
            std_ax = np.std(ax_data)

            print("Media AX:", mean_ax)
            print("Desviación AX:", std_ax)

            ax.clear()

            # Señal
            ax.plot(ax_data, label="AX")

            # Media
            ax.axhline(mean_ax, linestyle="--", label="Media")

            # Banda de desviación
            ax.axhline(mean_ax + std_ax, linestyle=":", label="+1σ")
            ax.axhline(mean_ax - std_ax, linestyle=":", label="-1σ")

            ax.set_title("Aceleración eje X (últimos 5 s)")
            ax.legend()

            # Reinicio
            ax_data = []
            ay_data = []
            az_data = []
            start_time = time.time()

    except Exception as e:
        print(e)

ani = animation.FuncAnimation(fig, update, interval=50, cache_frame_data=False)
plt.show()









