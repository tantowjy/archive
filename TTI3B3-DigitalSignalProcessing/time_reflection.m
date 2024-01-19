clc;

clear all;
close all;

x = [1 2 3 4 5 6 7 5 3 1];
x_max = length(x);
for i = 1:x_max,
    k = x_max-i+1;
    y(i) = x(1,k);
end

n = 1:x_max;
subplot(211);
stem(n, x); 
axis([-10 11 -1 10]);
xlabel('(a) Sinyal Asli');
subplot(212);
stem(n-(x_max+1), y);
axis([-10 11 -1 10]);
xlabel('(b) Hasil Refleksi');