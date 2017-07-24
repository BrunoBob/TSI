function [signal] = peigne(input, D)

[X Y] = size(input);
signal = zeros(X, 1);

for i = 1 : X
    retardD = 0;
    if(i > D)
        retardD = input(i - D);
    end
    signal(i) = input(i) + retardD;
end
end