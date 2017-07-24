function [passeTout1000] = reverberation(input, g)

peigne500 = peigne(input, 500);
peigne1000 = peigne(input, 1000);
peigne1500 = peigne(input, 1500);
peigne2000 = peigne(input, 2000);
peigne2500 = peigne(input, 2500);
peigne3000 = peigne(input, 3000);

total = peigne500 + peigne1000 + peigne1500 + peigne2000 + peigne2500 + peigne3000;

passeTout500 = passeTout(total,500, g);
passeTout750 = passeTout(passeTout500,750, g);
passeTout1000 = passeTout(passeTout750,1000, g);