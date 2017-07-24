function [signal] = passebas(input, D)

[X Y] = size(input);
signal = zeros(X, 1);

for i = 1 : X
    recur = 0;
    retardD = 0;
    if(i > 1)
        recur = signal((i-1));
    end
    if(i > (1 + D))
        retardD = input((i - D - 1));
    end
    signal(i) = (input(i) - retardD + recur);
end
end