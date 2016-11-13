import serial
import matplotlib.pyplot as plt

ser = serial.Serial('/dev/ttyACM0', 99999)

num_chars = 0
chars = []
while num_chars < 1500:
    chars.append(ser.read())
    num_chars += 1

print("got everything")

def unpack_chars(chunk):
    int_array = []
    offset = 0
    for c in range(4):
        i = ord(chunk[c]) >> offset
        i += ord(chunk[c+1]) >> (10 - offset)
        int_array.append(i)
        offset = (offset + 10) % 8

    return int_array

def unpack_char_array(char_array):
    int_array = []
    for i in range(0, len(char_array), 5):
        int_array.extend(unpack_chars(char_array[i:i+5]))

    return int_array


int_array = unpack_char_array(chars)
plt.plot(int_array)
plt.show()





