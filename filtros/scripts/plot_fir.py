import sys
import matplotlib.pyplot as plt
import numpy as np

fs = int(sys.argv[1])

_input = np.loadtxt('dados/input')
output = np.loadtxt('dados/output')
coeficiente = np.loadtxt('dados/coeficiente')
resposta = np.loadtxt('dados/resposta')
janela = np.loadtxt('dados/janela')

fig, axes = plt.subplots(nrows=2, ncols=4)
axes[0, 0].set_title("Input")
axes[0, 0].plot(_input)
axes[0, 0].set_xlabel("Amostra")
axes[0, 0].set_ylabel("Amplitude")

axes[0, 1].set_title("Output")
axes[0, 1].plot(output)
axes[0, 1].set_xlabel("Amostra")
axes[0, 1].set_ylabel("Amplitude")

axes[1, 0].magnitude_spectrum(_input, Fs=fs)
axes[1, 0].set_xlabel("Frequencia")
axes[1, 0].set_ylabel("Amplitude")

axes[1, 1].magnitude_spectrum(output, Fs=fs)
axes[1, 1].set_xlabel("Frequencia")
axes[1, 1].set_ylabel("Amplitude")

axes[0, 2].set_title("Coeficiente")
axes[0, 2].plot(coeficiente)
axes[0, 2].set_xlabel("Taps")
axes[0, 2].set_ylabel("Amplitude")

axes[1, 2].magnitude_spectrum(coeficiente, Fs=fs)
axes[1, 2].set_xlabel("Frequencia")
axes[1, 2].set_ylabel("Amplitude")

axes[0, 3].set_title("Resposta ao impulso")
axes[0, 3].plot(resposta)
axes[0, 3].set_xlabel("Taps")
axes[0, 3].set_ylabel("Amplitude")

axes[1, 3].set_title("Hamming")
axes[1, 3].plot(janela)
axes[1, 3].set_xlabel("Taps")
axes[1, 3].set_ylabel("Amplitude")
plt.show()
