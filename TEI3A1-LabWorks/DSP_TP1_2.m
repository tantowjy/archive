% DSP TP Modul 1
% Soal Nomor 2

n = [-1 0 2];
xn = [2 -1 1];

figure(2);

stem(n, xn, 'filled');
axis([-3, 4, -2, 3]);
grid on;
xlabel('Waktu (n)');
ylabel('Nilai x(n)');
title('Sinyal Diskrit');
