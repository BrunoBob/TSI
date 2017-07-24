im = imread('photo_908.jpg');

xyz = importdata('xyz.txt',',');

uv = importdata('uv.txt',',');

A = reshape(uv', 64, 1);

C = zeros(64, 12);

for i = 1:32
    C(2*i-1) = (xyz(i,:) 1 0 0 0 0 -uv_uv(i,1)