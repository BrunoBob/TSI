clear all;
close all;

im=imread('photo.jpg');
xyz=importdata('xyz.txt',',');
uv = importdata('uv.txt',',');
C=zeros(64,12);


for i=1:32
    C(2*i-1,:) = [xyz(i,:) 1 0 0 0 0 -uv(i,1)*xyz(i,1) -uv(i,1)*xyz(i,2) -uv(i,1)*xyz(i,3) -uv(i,1)];
    C(2*i,:) = [0 0 0 0 xyz(i,:) 1 -uv(i,2)*xyz(i,1) -uv(i,2)*xyz(i,2) -uv(i,2)*xyz(i,3) -uv(i,2)];
end

B=C'*C;
[eigenVectors,eigenValues]=eig(B);

minIndice=1;
for i=2:12
    if((eigenValues(i,i)<eigenValues(minIndice,minIndice)) && not(eigenValues(i,i)==0))
        minIndice=i;
    end;
end;

M=eigenVectors(:,minIndice);
xt= 0;
yt= 177;
zt= 151;
ut=(M(1)*xt+M(2)*yt+M(3)*zt+M(4))/(M(9)*xt+M(10)*yt+M(11)*zt+M(12));
vt=(M(5)*xt+M(6)*yt+M(7)*zt+M(8))/(M(9)*xt+M(10)*yt+M(11)*zt+M(12));

image(im);
hold on;
plot(uv(:,1),uv(:,2),'s');
plot(ut,vt,'md');

%Calibration 2éme image

im2 = imread('photo2.jpg');
uv2 = importdata('uv2.txt',',');
C2 = zeros(64,12);

for i=1:32
    C2(2*i-1,:) = [xyz(i,:) 1 0 0 0 0 -uv2(i,1)*xyz(i,1) -uv2(i,1)*xyz(i,2) -uv2(i,1)*xyz(i,3) -uv2(i,1)];
    C2(2*i,:) = [0 0 0 0 xyz(i,:) 1 -uv2(i,2)*xyz(i,1) -uv2(i,2)*xyz(i,2) -uv2(i,2)*xyz(i,3) -uv2(i,2)];
end

B2=C2'*C2;
[eigenVectors2,eigenValues2]=eig(B2);

minIndice2=1;
for i=2:12
    if((eigenValues2(i,i)<eigenValues2(minIndice2,minIndice2)) && not(eigenValues2(i,i)==0))
        minIndice2=i;
    end;
end;

M2=eigenVectors2(:,minIndice2);

ut2=(M2(1)*xt+M2(2)*yt+M2(3)*zt+M2(4))/(M2(9)*xt+M2(10)*yt+M2(11)*zt+M2(12));
vt2=(M2(5)*xt+M2(6)*yt+M2(7)*zt+M2(8))/(M2(9)*xt+M2(10)*yt+M2(11)*zt+M2(12));

figure();
image(im2);
hold on;
plot(uv2(:,1),uv2(:,2),'s');
plot(ut2,vt2,'md');

% stereovision
matA = zeros(4,3);

ud = 2316;
vd = 433;
ug = 2143;
vg = 506;

for i=1:3
    matA(1,i) = M(i)-ud*M(i+8);
    matA(2,i) = M(i+4)-vd*M(i+8);
    matA(3,i) = M2(i)-ug*M2(i+8);
    matA(4,i) = M2(i+4)-vg*M2(i+8);
end

matB = [-(M(4)-ud*M(12)) ; -(M(8)-vd*M(12)) ; -(M2(4)-ug*M2(12)) ; -(M2(8)-vg*M2(12))];


X = pinv(matA)*matB

