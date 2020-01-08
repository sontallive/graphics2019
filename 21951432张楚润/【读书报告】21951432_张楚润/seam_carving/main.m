clc; clear all; close all;
%%

image = imread('pic1.png');
image = imresize(image, 0.5);
figure;
imshow(image);
title('Original RGB Image');
fprintf('Size of the Original Image: %d x %d\n',size(image,1), size(image,2));
%%

% ����SeamCarving�������������Ϊͼ���Ҫ�ü�������
OutPut = SeamCarving(image, 50);

%%

% ��ʾ���
figure;
imshow(OutPut);
title('Image After seam Carving');
fprintf('Size of the seam Carved Image: %d x %d\n',size(OutPut,1),size(OutPut,2));