A=5;
t=0:0.001:1;
f=3;
s1=A*sin(2*pi*f*t);
%plot(t,s1,'r','LineWidth',2);
%grid('on');


%% Sampling
Fs=30; %Frekuensi sampling
n=(0:Fs-1)/Fs; %Proses Normalisasi
s2=A*sin(2*pi*f*t);
plot(t,s2,'r','LineWidth',2);
hold("on");
grid('on');