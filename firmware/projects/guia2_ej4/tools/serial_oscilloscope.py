"""
Serial oscilloscope helper

Uso:
  - Instalar dependencias: pip install pyserial matplotlib
  - Ejecutar: python tools\serial_oscilloscope.py COM3

El script abre el puerto serie, lee líneas con números (mV o ADC) y los grafica en tiempo real.
"""
import sys
import collections
import serial
import matplotlib.pyplot as plt
import matplotlib.animation as animation

if len(sys.argv) < 2:
    print("Uso: python serial_oscilloscope.py <PORT> [BAUD]")
    sys.exit(1)

PORT = sys.argv[1]
BAUD = int(sys.argv[2]) if len(sys.argv) > 2 else 115200

try:
    ser = serial.Serial(PORT, BAUD, timeout=1)
except Exception as e:
    print(f"Error abriendo {PORT}: {e}")
    sys.exit(1)

BUFFER = 500
data = collections.deque([0]*BUFFER, maxlen=BUFFER)

fig, ax = plt.subplots()
line, = ax.plot(range(BUFFER), data)
ax.set_ylim(0, 4096)
ax.set_title('Osciloscopio serial')
ax.set_xlabel('Muestras')
ax.set_ylabel('ADC / mV')

def update(frame):
    try:
        raw = ser.readline().decode(errors='ignore').strip()
        if not raw:
            return line,
        # intentar parsear como entero
        try:
            v = int(raw)
        except ValueError:
            # si la línea contiene más texto, intentar extraer número
            import re
            m = re.search(r"(-?\d+)", raw)
            if m:
                v = int(m.group(1))
            else:
                return line,
        data.append(v)
        line.set_ydata(data)
    except Exception as e:
        print('Error lectura serial:', e)
    return line,

ani = animation.FuncAnimation(fig, update, interval=20, blit=True)
plt.show()
ser.close()
