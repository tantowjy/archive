% *** filter FIR ***
N = 31; % orde filter
omegac=0.5;
m = (N-1)/2;
% frekuensi cutoff digital
% penggeseran fase
n=0:2*m+10; % penetapan titik untuk plot
h = omegac/pi* sinc(omegac* (n-m)/pi);
%w = [ones(1,N) zeros(1, length (n)-N)]; % window
w=0.54-(0.46*cos((2* 3.14*n)/N-1)); %Hamming
hd = h.* w;
[Hd, omega1] = freqz(hd, 1);
phase = 180/pi* unwrap(angle(Hd));
subplot(211); plot(omega1,0.707,omega1,abs(Hd)).grid;
title('respon frekuensi filter FIR');
xlabel('frekuensi (rad/sampel)');
ylabel('magnitude');
subplot(212); plot(omega1, phase), grid;
xlabel('frekuensi (rad/sampel)');
ylabel('sudut fase (der)');