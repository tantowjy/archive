function y = x(n)
    % Set all output to 0
    y = zeros(size(n));

 y(n >= 0 & n <= 6) = n(n >= 0 & n <= 6);
end