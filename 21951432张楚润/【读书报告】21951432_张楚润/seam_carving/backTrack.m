function seam = backTrack(x)
%������С�������ϸ����λ������
[rows,cols] = size(x);

%��������һ�����ص�����Ѱ��������
for i=rows:-1:1 
    if i==rows
        [~,j]=min(x(rows,:));  %Ѱ��������һ�е���С������
    else %�ҳ���ǰһ����С���������ڵ��������ص�
        if seam(i+1)==1
            vec=[Inf x(i,seam(i+1)) x(i,seam(i+1)+1)];%λ�������һ��
        elseif seam(i+1)==cols
            vec=[x(i,seam(i+1)-1) x(i,seam(i+1)) Inf];%λ�����Ҳ�һ��
        else
            vec=[x(i,seam(i+1)-1) x(i,seam(i+1)) x(i,seam(i+1)+1)];
        end
        
        %����ǰһ����С���ص����ڵ��������ص��У��ҳ�����ֵ��С�ģ�������������
        [~,Inx]=min(vec);%����1��2��3
        IndexInc=Inx-2;%-1��0��1
        j=seam(i+1)+IndexInc;%ǰһ�У���ǰ�л��һ��
    end
    seam(i,1) = j;%��i����С���ص��λ��Ϊ(i, j)
end

end