fs = 8000;
t = 0:(1/fs):0.1;
x1 = 5*cos(2*pi*500*t);
x2 = 5*cos(2*pi*1200*t+0.5*pi);
x3 = 5*cos(2*pi*1800*t+0.5*pi);
x = x1+x2+x3;
x_sam = x(1:241);
figure(6)
plot(t(1:241),x_sam);
axis([0 0.1 -6 6])
title('Signal X1')
xlabel('time (s)')
ylabel('Amplitude')

% Rectangular Windowing
A = abs(fft(x_sam))/length(x_sam);
fs = 8000;
k=0:1:length(x_sam)-1;
f=k*fs/length(x_sam);
figure(7);
plot(f(1:241/2), A(1:241/2));
title('Signal Spectrum with 240 data of signal X');
xlabel('Freq (Hz)');
ylabel('Absolut');

L = length(x_sam);
x_rect = x_sam * rectwin(L) ;
A = abs(fft(x_rect))/length(x_rect);
fs = 8000;
k=0:1:length(x_rect)-1;
f=k*fs/length(x_rect);

figure(13);
plot(f(1:length(x_rect)/2), A(1:length(x_rect)/2));
title('Rectangular Windowing (Domain Freq)')
xlabel('freq (Hz)');
ylabel('Absolut');