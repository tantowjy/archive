clc;

t = 0:0.001:1; %time vector
x = sin(2*pi*30*t)+sin(2*pi*60*t);
k = 4; % interpilasi with factor 4
y = interp(x, k);
subplot(211);
gbatas = 30;
stem(x(1:gbatas));
xlabel('(a) Sinyal Asli');
subplot(212);
stem(y(1:gbatas*k));
xlabel('(b) Hasil Interpolasi');