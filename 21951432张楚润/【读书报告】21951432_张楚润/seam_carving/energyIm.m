% ����ͼ
function res = energyIm(I)
%��RGB����ͨ��������ֵ�������
    res = energyGrey(I(:, :, 1)) + energyGrey(I(:, :, 2)) ...
        + energyGrey(I(:, :, 3));%Ϊ�˼򻯼��㣬��ת���ɻҶ�ͼ��
end

function res = energyGrey(I)
%��ͼ����ݶ�ģֵ������ͼһ����ͼ�����ص��ݶ�ģֵ��
res = abs(imfilter(I, [-1,0,1], 'replicate')) + ...
        abs(imfilter(I, [-1;0;1], 'replicate'));%�ٿ������ݶ�ֵ��ʵ�֡�����...
end