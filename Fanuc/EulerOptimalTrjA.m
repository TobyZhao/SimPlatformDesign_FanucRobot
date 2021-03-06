%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%@Copyright(c),Googol Shenzhen Tech. Ltd
%@File Name: EulerOptimalTrjA.m
%@Author: Dai Dan
%@Version: 1.0
%@Date: 25/6/2014
%
%@Description: To find optimal trajectory  for Newton Euler Dynamic Algorithm only account for
%acceleration, integral of acceleration to get velocity and position
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear;
clc;

D2R = 1/180*pi;
PosRng(1,:)=[-135,135]*D2R;
PosRng(2,:)=[-45,45]*D2R;
PosRng(3,:)=[-45,45]*D2R;
PosRng(4,:)=[-200,200]*D2R;
PosRng(5,:)=[-100,100]*D2R;
PosRng(6,:)=[-360,360]*D2R;

Vco = 0.8;
VelRng(1,:)=[-190,190]*D2R*Vco;
VelRng(2,:)=[-205,205]*D2R*Vco;
VelRng(3,:)=[-210,210]*D2R*Vco;
VelRng(4,:)=[-400,400]*D2R*Vco;
VelRng(5,:)=[-360,360]*D2R*Vco;
VelRng(6,:)=[-600,600]*D2R*Vco;

Aco = 1;
AccRng(1,:)=[-480,480]*D2R*Aco;
AccRng(2,:)=[-360,360]*D2R*Aco;
AccRng(3,:)=[-360,360]*D2R*Aco;
AccRng(4,:)=[-1200,1200]*D2R*Aco;
AccRng(5,:)=[-720,720]*D2R*Aco;
AccRng(6,:)=[-2400,2400]*D2R*Aco;

N=40;
Acc = zeros(N,6);

Ni=N/8*5;
ti=[0:1:Ni-1]*1/(Ni-1)*pi;

for j=1:6
    Acc(1:Ni,j) = AccRng(j,2)*sin(ti)' ;
    Acc(Ni+1:40,j) = 0;
end

DeltaT = 24*1e-3/2;
t=[0:1:N-1]*DeltaT;
Vel(1,:)=[0,0,0,0,0,0];
for i=2:N
    Vel(i,:) = Vel(i-1,:) + (Acc(i-1,:) + Acc(i,:))/2*DeltaT;
end
Pos(1,:)=[0,0,0,0,pi/2,0];
for i=2:N
    Pos(i,:) = Pos(i-1,:) + (Vel(i-1,:) + Vel(i,:))/2*DeltaT;
end
%%
% t=[0:1:N-1]*DeltaT;
% for i=1:6
%     figure(i);
%     plot(t,Acc(:,i)/D2R);
%     grid on;
% end


%%
X0 = zeros(6*N,1);
for i=1:N
    X0(6*(i-1)+1:6*i) = Acc(i,:)';
end

lb = [AccRng(:,1)];
ub = [AccRng(:,2)];
lb = repmat(lb,N,1);
ub = repmat(ub,N,1);

InitCost = EulerCostFunMA(X0);
disp('Initial Cost: (Before optimization)');
disp(InitCost);
disp('Condition Number: (Before optimization)');
disp(EulerCond(X0));
disp('Start to optimizating...');

options = optimset('Algorithm','active-set','Display','iter','PlotFcns',@optimplotfval,'MaxIter',20);
Optimal = fmincon(@EulerCostFunMA,X0,[],[],[],[],lb,ub,[],options);

%%
for i=1:N
    OptAcc(i,:)= Optimal(6*(i-1)+1:6*i)';
end

Xe = zeros(6*N,1);
for i=1:N
    Xe(6*(i-1)+1:6*i) = OptAcc(i,:)';
end
disp('Condition Number (After optimization):');
disp(EulerCond(Xe));
%%

OptVel(1,:)=[0,0,0,0,0,0];
for i=2:N
    OptVel(i,:) = OptVel(i-1,:) + (OptAcc(i-1,:) + OptAcc(i,:))/2*DeltaT;
end
OptPos(1,:)=[0,0,0,0,pi/2,0];
for i=2:N
    OptPos(i,:) = OptPos(i-1,:) + (OptVel(i-1,:) + OptVel(i,:))/2*DeltaT;
end
%%
% t=[0:1:N-1]*DeltaT;
% for i=1:6
%     figure(i+1);
%     plot(t,Pos(:,i)/D2R,'g','Marker','o');
%     hold on;
%     plot(t,OptPos(:,i)/D2R,'r','Marker','o');
%     grid on;
% end

%%
ActAcc = zeros(8*(N+1),6);
ActAcc(2:N+1,:) = OptAcc;
for i=1:N
    ActAcc(N+1+i,:)= -OptAcc(N+1-i,:);
end
ActAcc(2*(N+1)+1:4*(N+1),:) = -ActAcc(1:2*(N+1),:);
ActAcc(4*(N+1)+1:8*(N+1),:) = -ActAcc(1:4*(N+1),:);


ActVel(1,:)=[0,0,0,0,0,0];
for i=2:(8*(N+1))
    ActVel(i,:) = ActVel(i-1,:) + (ActAcc(i-1,:) + ActAcc(i,:))/2*DeltaT;
end
ActPos(1,:)=[0,0,0,0,pi/2,0];
for i=2:(8*(N+1))
    ActPos(i,:) = ActPos(i-1,:) + (ActVel(i-1,:) + ActVel(i,:))/2*DeltaT;
end
Xa = zeros(18*(8*(N+1)),1);
for i=1:(8*(N+1))
    Xa(18*(i-1)+1:18*(i-1)+6) = ActPos(i,:)';
    Xa(18*(i-1)+7:18*(i-1)+12) = ActVel(i,:)';
    Xa(18*(i-1)+13:18*i) = ActAcc(i,:)';
end
disp('Condition Number (After expansion):');
disp(EulerCond(Xa));
%%
% ActT=[0:1:(8*(N+1)-1)]*DeltaT;
% for i=1:6
%     figure(i);
%     plot(ActT,ActPos(:,i)/D2R,'r','Marker','o');
%     grid on;
% end

%%
tin =[0:1:(8*(N+1)-1)]*DeltaT;
tout = [0:1/3:8*(N+1)-1]*DeltaT;
for i=1:6
    OutPos(:,i) = interp1(tin,ActPos(:,i),tout,'v5cubic');
    OutVel(:,i) = interp1(tin,ActVel(:,i),tout,'v5cubic');
    OutAcc(:,i) = interp1(tin,ActAcc(:,i),tout,'v5cubic');
end
NumOut = size(tout,2);
Xout = zeros(18*NumOut,1);
for i=1:NumOut
    Xout(18*(i-1)+1:18*(i-1)+6) = OutPos(i,:)';
    Xout(18*(i-1)+7:18*(i-1)+12) = OutVel(i,:)';
    Xout(18*(i-1)+13:18*i) = OutAcc(i,:)';
end
disp('Condition Number (After v5cubic interpolation):');
disp(EulerCond(Xout));
for i=1:6
    figure(i);
    plot(tout,OutVel(:,i)/D2R,'r');
    grid on;
end

%%
PosFile = fopen('OptPos.txt','wt');
VelFile = fopen('OptVel.txt','wt');
AccFile = fopen('OptAcc.txt','wt');

for i=1:NumOut
    for j=1:5
        fprintf(PosFile,'%.4f\t',OutPos(i,j));
        fprintf(VelFile,'%.4f\t',OutVel(i,j));
        fprintf(AccFile,'%.4f\t',OutAcc(i,j));
    end
    j=6;
    fprintf(PosFile,'%.4f\n',OutPos(i,j));
    fprintf(VelFile,'%.4f\n',OutVel(i,j));
    fprintf(AccFile,'%.4f\n',OutAcc(i,j));
end
fclose(PosFile);
fclose(VelFile);
fclose(AccFile);

