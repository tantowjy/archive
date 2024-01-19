nvalues = -3:8;
yvalues = x(nvalues + 2);

stem(nvalues, yvalues, 'filled');
axis([-10, 10, -2, 8]);
grid on;