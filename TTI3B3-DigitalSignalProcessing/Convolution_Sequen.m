clear;
close all;

% Pembangkitan sekuen konstan pertama
L1=21;
for n=1:L1
    if(n>=2)
        st1(n)=1;
    else
        st1(n)=0;
    end
end

t1=[0:1:(L1-1)];
subplot(3,1,1);
stem(t1,st1, 'filled');
title("Konvolusi 2 sinyal sekuen konstan");

% Pembangkitan sekuen konstan kedua
L2=21;
for n=1:L2
    if(n>=2)
        st2(n)=1;
    else
        st2(n)=0;
    end
end

t2=[0:1:(L2-1)];
subplot(3,1,2);
stem(t2,st2, 'filled');
xlabel("Jumlah Sample");

% Convolution
subplot(3,1,3);
c = conv(st1,st2);
stem(c, 'filled');
