function SeamCarvedIm  = SeamCarving( I, cols )
%% 
% ɾ��������ͼ���ָ������

SeamCarvedIm = I; % Assign initial image as SeamCarved Image.
%%
for i = 1:cols    % Ѱ������������
    energy = energyIm(SeamCarvedIm); % ������ͼ
    M = seamImage(energy);%���ۻ�����ֵ
    seam = backTrack(M); %Ѱ�������߾�����λ��
    SeamCarvedIm = removeSeam(SeamCarvedIm,seam); %�Ƴ�������
end