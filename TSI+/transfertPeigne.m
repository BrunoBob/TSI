function [Hf] = transfertPeigne(fFe, D)
    Hf = 1 + exp(-2 * pi * i * fFe * D);
end