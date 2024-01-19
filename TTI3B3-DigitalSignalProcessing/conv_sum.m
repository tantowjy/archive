%%%%%%%%%%%%%%%%%%
% Convolution Sum
%%%%%%%%%%%%%%%%%%

%%%
x1 = [0 0 ones(1, 20)]; % unit-step input
n = -2:19; n1 = 0:19;
x2 = [0 0 cos(2*pi*n1/3)]; % cosine input
    h = (1/3)*ones(1, 3); % impulse response
    y = conv(x1, h); y1 = y(1:length(n)); % convolution sums
    y = conv(x2, h); y2 = y(1:length(n));

figure(1);