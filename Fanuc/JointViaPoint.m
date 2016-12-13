function [qall,vall,aall,jall,len] = JointViaPoint(JointPts,V,Vm,Am,Jm)

[dim,num]=size(JointPts);

qo = JointPts(:,1:end-1);
qf = JointPts(:,2:end);
deltaq = qf-qo;
ratio = bsxfun(@rdivide,deltaq,deltaq(1,:));

vo=V*ones(dim,num-1);
vo(:,1)=0;
vo=vo.*ratio;
vf=V*ones(dim,num-1);
vf(:,end)=0;
vf=vf.*ratio;

ao=zeros(dim,num-1);
af=zeros(dim,num-1);
ratio = abs(ratio);
vm=Vm*ones(dim,num-1).*ratio; 
am=Am*ones(dim,num-1).*ratio; 
jm=Jm*ones(dim,num-1).*ratio;
qt=cell(num-1,dim);
vt=cell(num-1,dim);
at=cell(num-1,dim);
jt=cell(num-1,dim);
for j=1:dim
    for k=1:num-1

        [Flag,Ta,Tv,Td,Tj1,Tj2,qt{k,j},vt{k,j},at{k,j},jt{k,j}]=doubleS(qo(j,k),qf(j,k),vo(j,k),vf(j,k),ao(j,k),af(j,k),vm(j,k),am(j,k),jm(j,k));
    end
end

len1=length(cell2mat(qt(:,1)));
len2=length(cell2mat(qt(:,2)));
len3=length(cell2mat(qt(:,3)));
len = max(max(len1,len2),len3);

qall=zeros(len,dim);
vall=zeros(len,dim);
aall=zeros(len,dim);
jall=zeros(len,dim);

for j=1:dim
qall(:,j)=cell2mat(qt(:,j));
vall(:,j)=cell2mat(vt(:,j));
aall(:,j)=cell2mat(at(:,j));
jall(:,j)=cell2mat(jt(:,j));

end

