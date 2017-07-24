function [signal] = passeTout(input, D, g)

[X Y] = size(input);
signal = zeros(X, 1);

for i = 1 : X
    recur = 0;
    retardD = 0;
    if(i > D)
        retardD = input(i - D );
        recur = g * signal((i - D));
    end
    signal(i) = ((-g * input(i)) + retardD + recur);
end

end