import pyaudio
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation

# from fft import fft
from numpy.fft import fft

def init_line():
    plot.set_data(r, [-1000]*l)
    return (plot,)

def update_line(i):
    data = np.fromstring(stream.read(BUFFER), dtype=np.float32)

    # Filtro
    ######################################################
    M = 10  # ordem do filtro

    hamming = np.zeros(M)
    for i in range(M):
        hamming[i] = 0.54 - 0.46 * np.cos(2 * np.pi * i / M)

    fc = 3100  # frequência de corte em 3100 Hz

    ######################################################

    plot.set_data(r, fft(data))
    return (plot,)

RATE = 30000
BUFFER = 1024

RATE = RATE // BUFFER * BUFFER

p = pyaudio.PyAudio()
stream = p.open(
    format = pyaudio.paFloat32,
    channels = 1,
    rate = RATE,
    input = True,
    output = False,
    frames_per_buffer = BUFFER
)

fig = plt.figure()
plot = plt.plot([],[])[0]

r = range(0,int(RATE),int(RATE/BUFFER))
l = len(r)

plt.xlim(0, RATE/2)
plt.ylim(0, 10)
plt.xlabel('Frequencia')
plt.ylabel('Energia')
plt.grid()

matplotlib.animation.FuncAnimation(fig, update_line, init_func=init_line, interval=0, blit=True)
plt.show()
