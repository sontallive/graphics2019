function x=removeSeam(x,Seam)
[rX, cX, dim] = size(x);
[Sr, Sc, ~] = size(Seam); 

if rX~=Sr
        error('SeamVector and image dimension mismatch');
end
%ReduceImage = zeros(size(x));
if (rX == Sr)
    for k=1:Sc              %ɾ��Sc��������
        for i=1:dim             %����RGBͼ��ɾ���������ÿ��ͨ��ֵif rgb, goes through each channel
            for j=1:rX        %ͼ����rX��
                if Seam(j,k)==1
                    ReduceImage(j,:,i)= x(j,2:cX,i);%������λ�������
                elseif Seam(j,k)==cX
                    ReduceImage(j,:,i)= x(j,1:cX-1,i);%������λ�����Ҳ�
                else
                    ReduceImage(j,:,i)=[x(j,1:Seam(j,k)-1,i) x(j,Seam(j,k)+1:cX,i)];
                end
            end
        end
        x=ReduceImage;
        clear ReduceImage
        [rX, cX, dim]=size(x);
    end
end