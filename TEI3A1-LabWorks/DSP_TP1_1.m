% DSP TP Modul 1
% Soal Nomor 1

n = [-1 1 2];
xn = [1 -1 2];

figure(1);

stem(n, xn, 'filled');
axis([-3, 4, -2, 3]);
grid on;
xlabel('Waktu (n)');
ylabel('Nilai x(n)');
title('Sinyal Diskrit');
