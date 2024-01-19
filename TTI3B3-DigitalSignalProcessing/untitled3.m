clear all;clf
syms x y t
x = cos(2*pi*t); theta=0;
figure(1)
for k = 1:4,
    y = cos(2*pi*k*t + theta);
    if k == 1, subplot(221)
        elseif k == 2, subplot(222)
        elseif k == 3, subplot(223)
        else subplot(224)
    end
    ezplot(x, y);grid;hold on
end
hold off