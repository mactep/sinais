import sys
from scipy.signal import butter

M = int(sys.argv[1])
fs = int(sys.argv[2])
fc = int(sys.argv[3])

b, a = butter(M, fc/(fs/2))
with open("dados/coeficientes_iir", "w") as f:
    # f.write(str(M) + "\n")
    # f.write(str(fs) + "\n")
    for i in range(M+1):
        f.write(str(a[i]) + "\n")
    for i in range(M+1):
        f.write(str(b[i]) + "\n")
