%gundul.m
clc
Fs=2000;
t=0:1/Fs:0.25;
c=sin(2*pi*262*t);
d=sin(2*pi*294*t);
e=sin(2*pi*330*t);
f=sin(2*pi*249*t);
g=sin(2*pi*392*t);
a=sin(2*pi*440*t);
b=sin(2*pi*494*t);
cl=sin(2*pi*523*t);
nol=[zeros(size(t))];
nada1 = [c,e,c,e,f,g,g,nol,b,cl,b,cl,b,g,nol,nol];
nada2 = [c,e,c,e,f,g,g,nol,b,cl,b,cl,b,g,nol];
nada3 = [c,nol,e,nol,g,nol,f,f,g,f,e,c,f,e,c,nol];
nada4 = [c,nol,e,nol,g,nol,f,f,g,f,e,c,f,e,c];
lagu = [nada1, nada2, nada3, nada4];
melody = [e d c d e e e d d d e g g e d c d e e e e d d e d c];
% sound(lagu,Fs);
sound(melody,Fs);
