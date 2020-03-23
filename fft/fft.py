import numpy as np

def fft(x, constants=None):
    N = len(x)
    x = np.asarray(x, dtype=float)

    if constants is None:
        constants = [np.e ** (-2j * np.pi * k / N) for k in range(N // 2)]

    if N <= 1:
        return x

    even = fft(x[0::2], constants[0::2])
    odd = fft(x[1::2], constants[0::2])

    T = [constants[k] * odd[k] for k in range(N // 2)]

    right = [even[k] + T[k] for k in range(N // 2)]
    left = [even[k] - T[k] for k in range(N // 2)]

    return right + left
