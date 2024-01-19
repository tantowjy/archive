t=0:0.001:1;
f=2;
y=sin(2*pi*f*t);

t1=0:1/(10*f):1;
y1=sin(2*pi*f*t1);
plot(t,y,t1,y1,'-o');
title(sprintf('frekuensi sampling = frekuensi sinyal, jumlah data %d', length(y1)))
