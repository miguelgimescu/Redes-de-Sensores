import socket
import threading
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from collections import deque

# ─── CONFIGURACIÓN ───────────────────────────────────────────
HOST = ''       # escucha en todas las interfaces
PORT = 455      # tiene que coincidir con el port del ESP32
MAX_PUNTOS = 50 # puntos visibles en la gráfica
# ─────────────────────────────────────────────────────────────

ax_data = deque([0.0] * MAX_PUNTOS, maxlen=MAX_PUNTOS)
ay_data = deque([0.0] * MAX_PUNTOS, maxlen=MAX_PUNTOS)
az_data = deque([0.0] * MAX_PUNTOS, maxlen=MAX_PUNTOS)

conn_global = None  # socket del cliente conectado

def servidor():
    """Hilo que acepta conexión y lee datos del ESP32."""
    global conn_global
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind((HOST, PORT))
    s.listen(1)
    print(f"[SERVER] Escuchando en puerto {PORT}...")

    while True:
        conn, addr = s.accept()
        conn_global = conn
        print(f"[SERVER] ESP32 conectado desde {addr}")

        # Nada más conectar, mandamos start automáticamente
        # (o puedes quitarlo y mandarlo a mano desde teclado)
        conn.sendall(b"start\n")

        buffer = ""
        while True:
            try:
                data = conn.recv(1024).decode('utf-8', errors='ignore')
                if not data:
                    print("[SERVER] ESP32 desconectado")
                    conn_global = None
                    break
                buffer += data
                while '\n' in buffer:
                    linea, buffer = buffer.split('\n', 1)
                    linea = linea.strip()
                    if not linea:
                        continue
                    # Líneas de texto (mensajes del ESP32)
                    if ';' not in linea:
                        print(f"[ESP32] {linea}")
                        continue
                    # Línea de datos: "ax;ay;az"
                    partes = linea.split(';')
                    if len(partes) == 3:
                        try:
                            ax_data.append(float(partes[0]))
                            ay_data.append(float(partes[1]))
                            az_data.append(float(partes[2]))
                            print(f"ax={partes[0]:>7}  ay={partes[1]:>7}  az={partes[2]:>7}")
                        except ValueError:
                            pass
            except Exception as e:
                print(f"[SERVER] Error: {e}")
                conn_global = None
                break

def enviar_comando(cmd):
    """Manda un comando al ESP32 si hay conexión activa."""
    if conn_global:
        conn_global.sendall((cmd + '\n').encode())
        print(f"[TX] {cmd}")
    else:
        print("[SERVER] Sin conexión activa")

# ─── GRÁFICA EN TIEMPO REAL ───────────────────────────────────
fig, ax = plt.subplots()
fig.patch.set_facecolor('#1e1e1e')
ax.set_facecolor('#1e1e1e')
ax.tick_params(colors='white')
ax.yaxis.label.set_color('white')
ax.xaxis.label.set_color('white')
ax.set_title("Acelerómetro ESP32 (datos simulados)", color='white')
ax.set_ylim(-1.5, 1.5)
ax.set_ylabel("Aceleración (g)")
ax.set_xlabel("Muestras")
ax.grid(True, color='#444444')

linea_ax, = ax.plot([], [], color='#ff4d4d', label='ax')
linea_ay, = ax.plot([], [], color='#4dff88', label='ay')
linea_az, = ax.plot([], [], color='#4da6ff', label='az')
ax.legend(facecolor='#2e2e2e', labelcolor='white')

def actualizar(frame):
    x = list(range(MAX_PUNTOS))
    linea_ax.set_data(x, list(ax_data))
    linea_ay.set_data(x, list(ay_data))
    linea_az.set_data(x, list(az_data))
    ax.set_xlim(0, MAX_PUNTOS - 1)
    return linea_ax, linea_ay, linea_az

ani = animation.FuncAnimation(fig, actualizar, interval=200, blit=True, cache_frame_data=False)

# Hilo del servidor en background
hilo = threading.Thread(target=servidor, daemon=True)
hilo.start()

print("Escribe 'start' o 'stop' y pulsa Enter para controlar el ESP32.")
print("Cierra la ventana de la gráfica para salir.\n")

# Hilo de entrada de teclado
def teclado():
    while True:
        try:
            cmd = input()
            if cmd.strip() in ('start', 'stop'):
                enviar_comando(cmd.strip())
        except EOFError:
            break

hilo_teclado = threading.Thread(target=teclado, daemon=True)
hilo_teclado.start()

plt.show()
