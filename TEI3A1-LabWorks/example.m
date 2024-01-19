% Example

t=[45:0.01:135];

xt=2*sin(2*(t*pi/180));

figure (1);

plot(t, xt);
xlabel('Waktu Kontinyu (t)');
ylabel('Nilai x(t)');
title ('Sinyal Kontinyu');