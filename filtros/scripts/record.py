import sys
import numpy as np
import sounddevice as sd
from scipy.io.wavfile import write

fs = int(sys.argv[1])  # Sample rate
seconds = int(sys.argv[2])  # Duration of recording

myrecording = sd.rec(int(seconds * fs), samplerate=fs, channels=1)
sd.wait()  # Wait until recording is finished
write('dados/input.wav', fs, myrecording)  # Save as WAV file

np.savetxt('dados/input', myrecording)
