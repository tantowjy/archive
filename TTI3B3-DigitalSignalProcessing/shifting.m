t = linspace(-5, 5);
y = sinc(t);
subplot(211);
stem(t, y, 'LineWidth', 2)
xlabel('(a) Sinyal Asli');
axis([-5 5 -0.5 1.2]);
subplot(212);
stem(t+3, y);
xlabel('(b) Sinyal Tertunda');
axis([-5 5 -0.5 1.2]);