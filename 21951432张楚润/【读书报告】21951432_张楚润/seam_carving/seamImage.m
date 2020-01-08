%�����ۻ�����ֵ
function seamimage = seamImage(E)

sz = size(E); % Get the size of the Energy map.

seamimage = zeros(sz(1),sz(2));
seamimage(1,:) = E(1,:);%ȡ��������ĵ�һ��Ԫ��

for i=2:sz(1)
    for j=1:sz(2)
        % ���ƺñ�Ե��
        if j-1<1
            seamimage(i,j)= E(i,j)+min([seamimage(i-1,j),seamimage(i-1,j+1)]);%λ�������
        elseif j+1>sz(2)
            seamimage(i,j)= E(i,j)+min([seamimage(i-1,j-1),seamimage(i-1,j)]);%λ�����Ҳ�
        else
            seamimage(i,j)= E(i,j)+min([seamimage(i-1,j-1),seamimage(i-1,j),seamimage(i-1,j+1)]);
        end
    end
end