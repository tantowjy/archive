t = 0:.00025:1;
x = sin(2*pi*30*t)+sin(2*pi*60*t);
k = 6; %factor decimation
y = decimate(x, k);
subplot(211);
gbatas = 120;
stem(x(1:gbatas)), axis([0 120 -2 2]); % Original Signal
xlabel('(a) Batas Sinyal Asli');
subplot(212);
stem(y(1:gbatas/k));  % Decimal signal
xlabel('(b) Hasil time scaling, down sampling');