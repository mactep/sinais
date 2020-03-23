import numpy as np
from scipy.io.wavfile import read

fs = 20000  # Sample rate
seconds = 3  # Duration of recording

myrecording = read('input.wav')

print(myrecording[0])
print(myrecording[1].shape)

np.savetxt('input', myrecording[1])
