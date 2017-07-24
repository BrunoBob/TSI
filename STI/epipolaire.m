clear all;
close all;

im_a = imread('photo.jpg');
im_b = imread('photo2.jpg');

uv_a = importdata('uv.txt',',');
uv_b = importdata('uv2.txt',',');

A = zeros(32,9);

for i=1:32
    A(i,:)=[uv_a(i,1)*uv_b(i,1) uv_a(i,1)*uv_b(i,2) uv_a(i,1) uv_a(i,2)*uv_b(i,1) uv_a(i,2)*uv_b(i,2) uv_a(i,2) uv_b(i,1) uv_b(i,2) 1];
end

[eigenVectors, eigenValues] = eig(A'*A);

minIndex = 1;

for i=1:9
    eigVal=eigenValues(i,i);
    if (abs(eigVal)<=abs(eigenValues(minIndex,minIndex)) && not(eigVal==0))
        minIndex = i;
    end;
end;

F = eigenVectors(:,minIndex);

u_a_1 = 2316;
v_a_1 = 433;
u_a_2 = 2143;
v_a_2 = 506;
for i=1:size(im_b,1)
    ud = (-(F(7,1)+F(8,1)+F(9,1))-(((F(4,1)+F(5,1)+F(6,1))*i)))/(F(1,1)+F(2,1)+F(3,1));
    plot(ud,i,'s');
end
%subplot(1,2,1);
image(im_a);
hold on;
plot(uv_a(:,1),uv_a(:,2),'s');
plot(u_a_1,v_a_1,'md');
plot(u_a_2,v_a_2,'cd');
