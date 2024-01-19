clc;
close all;
clear all;

% Define the transfer function H(z)
num = [1 -1];
den = [1 0 -0.25];
H = tf(num, den);

% Define the input signal x[n]
x = [1 1 1 1 1];

% Calculate the output y[n]
y = filter(H, x);

% Plot the input and output signals
n = 0:length(x)-1;
plot(n, x, n, y);

xlabel('n');
ylabel('x[n]');
title('Input and Output Signals');

legend('x[n]', 'y[n]');