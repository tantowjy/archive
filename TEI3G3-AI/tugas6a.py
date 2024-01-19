# importing dependancies
import numpy as np

# The activation function
def activation(x):
    return 1 / (1 + np.exp(-x))

# A 2 x 1 matrix of randomly generated weights in the range -1 to 1
weights = np.random.uniform(-1,1,size = (2, 1))

# The training set divided into input and output. Notice that
# we are trying to train our neural network to predict the output
# of the logical OR.
training_inputs = np.array([[0, 0, 1, 1, 0, 1]]).reshape(3, 2)
training_outputs = np.array([[0, 1, 1]]).reshape(3,1)

for i in range(15000):
    # forward pass
    dot_product = np.dot(training_inputs, weights)
    output = activation(dot_product)
    # backward pass.
    temp2 = -(training_outputs - output) * output * (1 - output)
    adj = np.dot(training_inputs.transpose(), temp2)
    # 0.5 is the learning rate.
    weights = weights - 0.5 * adj
    
# The testing set
test_input = np.array([1, 0])
test_output = activation(np.dot(test_input, weights))
# OR of 1, 0 is 1
print(test_output)