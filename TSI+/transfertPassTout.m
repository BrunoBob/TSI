function [Hf] = transfertPassTout(fFe, D, g)

ZD = exp(-2 * pi * i * fFe * D);
Hf = (-g + ZD) / (1 - g*ZD);

end