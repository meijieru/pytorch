r"""Importing this file includes common utility methods for checking quantized
tensors and modules.
"""
import numpy as np

def _clip(a, a_min, a_max):
    """Clips the values to min, max."""
    a = copy.deepcopy(a)
    if isinstance(a, Iterable):
        for idx in len(a):
            a[idx] = _clip(a[idx], a_min, a_max)
        return a
    else:
        return min(a_max, max(a_min, a))

def _round(a, ndigits=None):
    """Rounds the values to some (optional) number of digits."""
    a = copy.deepcopy(a)
    if isinstance(a, Iterable):
        for idx in len(a):
            a[idx] = _round(a[idx], ndigits)
        return a
    else:
        return round(a, ndigits)

# Quantization references
def _quantize(x, scale, zero_point, qmin=None, qmax=None, dtype=np.uint8):
    """Quantizes a numpy array."""
    if qmin is None:
        qmin = np.iinfo(dtype).min
    if qmax is None:
        qmax = np.iinfo(dtype).max
    qx = np.round(x / scale + zero_point).astype(np.int64)
    qx = np.clip(qx, qmin, qmax)
    qx = qx.astype(dtype)
    return qx


def _dequantize(qx, scale, zero_point):
    """Dequantizes a numpy array."""
    x = (qx.astype(np.float) - zero_point) * scale
    return x


def _requantize(x, multiplier, zero_point, qmin=0, qmax=255, qtype=np.uint8):
    """Requantizes a numpy array, i.e., intermediate int32 or int16 values are
    converted back to given type"""
    qx = (x * multiplier).round() + zero_point
    qx = np.clip(qx, qmin, qmax).astype(qtype)
    return qx
