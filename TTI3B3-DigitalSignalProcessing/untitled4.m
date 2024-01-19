fs=200;                  % frekuensi sampling
t=(0:fs-1)/fs;
s1 =sin(2*pi*t*4);

stem(t, s1, 'filled');
axis([0 1 -1.2 1.2]);
grid on;