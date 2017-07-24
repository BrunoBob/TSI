clear all;
close all;

[signal,Fe] = audioread('NyanCat.wav');

%Etude fréquentielle
% 
% %signalF = fft(signal);
% %moduleSignal = abs(signalF);
% %plot(signal);
% 
% %Partie 1
% 
size = 10000;
mod = zeros(size,1);
phase = zeros(size,1);
fFe = zeros(size, 1);

for i = 1 : size
    fFe(i) = i/Fe;
    mod(i) = abs(transfertPassebas(fFe(i), Fe/485 -1));
    phase(i) = angle(transfertPassebas(fFe(i), Fe/485 -1));
end

figure();
plot(fFe,mod);
title('Module passe bas');
% figure();
% plot(fFe,phase);
% title('Phase passe bas');
% 
% passeBastest = passebas(signal, 500);
% %soundsc(passeBastest, Fe);
% 
% %Partie 2 
% size = 10000;
% mod = zeros(size,1);
% phase = zeros(size,1);
% fFe = zeros(size, 1);
% 
% for i = 1 : size
%     fFe(i) = i / Fe;
%     mod(i) = abs(transfertPeigne(fFe(i), 20));
%     phase(i) = angle(transfertPeigne(fFe(i), 20));
% end
% 
% figure();
% plot(fFe,mod);
% title('Module peigne');
% figure();
% plot(fFe,phase);
% title('Phase peigne');
% 
% peigneTest = peigne(signal, 2000);
% %soundsc(peigneTest, Fe);
% 
% 
% %Partie 3
% size = 10000;
% mod = zeros(size,1);
% phase = zeros(size, 1);
% fFe = zeros(size, 1);
% 
% for i = 1 : size
%     fFe(i) = i / Fe;
%     mod(i) = abs(transfertPassTout(fFe(i), 20, 0.5));
%     phase(i) = angle(transfertPassTout(fFe(i), 20, 0.5));
% end
% 
% figure();
% plot(fFe,mod);
% title('module passe tout');
% figure();
% plot(fFe,phase);
% title('phase passe tout');
% 
% passeToutTest = passeTout(signal,5000, 0.5);
% % soundsc(passeToutTest, Fe);
% 
% %Partie 4
% 
% rever = reverberation(signal, 0.);
% %soundsc(rever, Fe);

%Partie 5
size = 10000;
mod = zeros(size,1);
phase = zeros(size,1);
fFe = zeros(size, 1);

for i = 1 : size
    fFe(i) = i/Fe;
    mod(i) = abs(transfertPassehaut(fFe(i), Fe/485 -1));
    phase(i) = angle(transfertPassehaut(fFe(i), 500));
end

figure();
plot(fFe,mod);
title('Module passe bas');
% figure();
% plot(fFe,phase);
% title('Phase passe bas');

passeHauttest = passehaut(signal, 500);
soundsc(passeHauttest, Fe);
