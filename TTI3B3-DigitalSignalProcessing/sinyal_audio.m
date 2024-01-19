clear all;
Fs=1000;
t=0:1/Fs:0.25;
f=100;
x=sin(2*pi*f*t);
sound(x,Fs);