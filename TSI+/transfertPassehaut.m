function [Hf] = transfertPassehaut(fFe, D)
    Hf = (1 - exp(-2 * pi * i * fFe * (D + 1))) * (1 - exp(-2 * i * pi * fFe));
end