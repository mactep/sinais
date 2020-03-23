import sys
import numpy as np
from scipy.io.wavfile import write

fs = int(sys.argv[1])  # Sample rate
# fs = 20000  # Sample rate

myrecording = np.loadtxt('dados/output')
write('dados/output.wav', fs, myrecording)  # Save as WAV file
