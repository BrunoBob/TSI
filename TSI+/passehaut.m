function [signal] = passehaut(input, D)

[X Y] = size(input);
signal = zeros(X, 1);

for i = 1 : X
    retardD2 = 0;
    retardD = 0;
    retard = 0;
    if(i > 1)
        retard = input((i-1));
    end
    if(i > (1 + D))
        retardD = input((i - D - 1));
    end
    if(i > (2 + D))
        retardD2 = input((i - D - 2));
    end
    signal(i) = input(i) - retardD + retardD2 - retard ;
end
end