num = [1 3];
den = [1 5 20 16 0];
rlocus(num,den);
v = [-6 6 -6 6];
axis(v);
axis('square');
grid;
title('Root-Locus Plot of G(s) = K(s+3)/[s(s+1)(s^2+4s+16)]')
