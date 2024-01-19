L = input("Panjang Gelombang (>=10):");
P = input("Lebar pulsa (lebih kecil dari L):");

%% first signal
for n=1:L
    if n <= P
        x(n) = 1;
    else 
        x(n) = 0;
    end
end
t=1:L;
subplot(3,1,1);
stem(t,x, 'filled');
% axis([0, L+1, -0.3, 1.2]);

%% second signal
for n=1:L
    if n <= P
        v(n)=1;
    else
        v(n)=0;
    end
end
t=1:L;
subplot(3,1,2);
stem(t,v, 'filled');
% axis([0, L+1, -0.3, 1.2]);

%% convolution
subplot(3,1,3);
stem(conv(x,v), 'filled');
% axis([0, L+1, -0.3, 1.2]);
