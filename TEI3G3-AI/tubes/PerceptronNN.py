# Identitas Mahasiswa
print("NIM : 1102213211")
print("Nama: Tanto Wijaya")
print("PROBLEM 1")

import random

# Inisialisasi bobot dan bias secara acak
w = random.uniform(0, 1)
b = random.uniform(0, 1)
learning_rate = 0.1
epochs = 100

# Data training
# inputs = [0, 1, 2, 3]
# targets = [0, 2, 4, 6]

# creating an empty list
inputs = []
targets= []

# number of elements as input
n = int(input("Enter number of elements : "))
m = n

# inputs list
for i in range(0, n):
    print('Input {}:'.format(i+1))
    ele = int(input())
    inputs.append(ele)

# targets list
for i in range(0, m):
    print('Target output {}:'.format(i+1))
    ele = int(input())
    targets.append(ele)

# Fungsi aktivasi perceptron
def perceptron(input):
    return input * w + b

# Pelatihan perceptron
for epoch in range(epochs):
    for i in range(len(inputs)):
        input_data = inputs[i]
        target = targets[i]

        # Hitung output perceptron
        output = perceptron(input_data)

        # Hitung error
        error = target - output

        # Update bobot dan bias
        w += learning_rate * error * input_data
        b += learning_rate * error

# Print input dan target output
print("Input        :", inputs)
print("Target Output:", targets)

# Bobot weight terbaik
print('Bobot terbaik adalah {:.2f}'.format(w))

# Uji perceptron dengan data baru
new_input = 2
predicted_output = perceptron(new_input)
print('Input: {}, Predicted Output: {:.2f}'.format(new_input, predicted_output))