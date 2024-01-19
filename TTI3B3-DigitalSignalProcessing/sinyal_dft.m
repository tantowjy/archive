fs = 8000;
t = 0:(1/fs):0.1;
x1 = 5*cos(2*pi*500*t);
x2 = 5*cos(2*pi*1200*t+0.5*pi);
x3 = 5*cos(2*pi*1800*t+0.5*pi);
x = x1+x2+x3;

%plot x1
figure(1);
plot(t,x1);
axis([0 0.1 -6 6])
title('Signal X1')
xlabel('time (s)')
ylabel('Amplitude')

%plot x2
figure(2);
plot(t,x2);
axis([0 0.1 -6 6])
title('Signal X2')
xlabel('time (s)')
ylabel('Amplitude')

%plot x3
figure(3);
plot(t,x3);
axis([0 0.1 -6 6])
title('Signal X3')
xlabel('time (s)')
ylabel('Amplitude')

%plot x
figure(4);
plot(t,x);
axis([0 0.1 -16 16])
title('Signal X')
xlabel('time (s)')
ylabel('Amplitude')

%implementation fft
Ak = abs(fft(x)/length(x));
fs = 8000;
k = 0:1:length(x)-1;
f = k*fs/length(x);
figure(5);
plot(f(1:length(x)/2),Ak(1:length(x)/2));
title('Signal Spectrum');
xlabel('Frequency (Hz)');
ylabel('Absolute');
