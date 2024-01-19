clc
clear

L=input('panjang gelombang: ');
P=input('panjang sekuen: ');

for n=1:L
    if (n>P)
        step(n)=1;
    else
        step(n)=0;
    end
end

x=1:L
stem(x, step, 'filled');
axis([0, 25, -2, 2])
grid on;