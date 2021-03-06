%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%@Copyright(c),Googol Shenzhen Tech. Ltd
%@File Name: EulerComapre.m
%@Author: Dai Dan
%@Version: 1.0
%@Date: 05/08/2014
%
%@Description: To qualitatively analyse and compare the performance of 
% identified model and simulated model given specific trajectory 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear all;
clc;
format short g;


%%
DH=[
    0       430     0       0       700     0        88;
    0       0       -pi/2   0       pi      pi       0;
    0       100     650     0       0       0        0;
    0       -pi/2   0       -pi/2   -pi/2    -pi/2   0;];
DH(1,:) = DH(1,:)/1000;
DH(3,:) = DH(3,:)/1000;

ez = [0;0;1];
ex = [1;0;0];
eo = [0;0;0];
g01_0= expg([eo;ez],DH(2,1))*expg([ez;eo],DH(1,1))*expg([eo;ex],DH(4,1))*expg([ex;eo],DH(3,1));
g12_0= expg([eo;ez],DH(2,2))*expg([ez;eo],DH(1,2))*expg([eo;ex],DH(4,2))*expg([ex;eo],DH(3,2));
g23_0= expg([eo;ez],DH(2,3))*expg([ez;eo],DH(1,3))*expg([eo;ex],DH(4,3))*expg([ex;eo],DH(3,3));
g34_0= expg([eo;ez],DH(2,4))*expg([ez;eo],DH(1,4))*expg([eo;ex],DH(4,4))*expg([ex;eo],DH(3,4));
g45_0= expg([eo;ez],DH(2,5))*expg([ez;eo],DH(1,5))*expg([eo;ex],DH(4,5))*expg([ex;eo],DH(3,5));
g56_0= expg([eo;ez],DH(2,6))*expg([ez;eo],DH(1,6))*expg([eo;ex],DH(4,6))*expg([ex;eo],DH(3,6));


%%%%Actual Dynamic Parameters%%%%%%%%%%%%%
%%%%%% Mass: kg  Inertia: kg/m^2  Center: m
ma1 = 170.31;
in1 = [5.2954 -0.2565 -0.6366;-0.2565 4.7000 0.2830;-0.6366 0.2829 5.8635];
cen1 = [0.0407 -0.0528 0.4702];

ma2 = 63.74;
in2 = [5.8840 0.0072 0.0135;0.0072 6.0178 -0.1907;0.0135 -0.1907 0.3374];
cen2 = [0.1510 0.1746 0.9687];

ma3 = 98.98;
in3 = [1.8201 -0.2274 -0.3112;-0.2274 2.2537 -0.1441;-0.3112 -0.1441 1.9485];
cen3 = [0.1568 -0.0318 1.5191];

ma4 = 24.46;
in4 = [0.0607 -0.0922 0;-0.0922 1.4493 0;0 0,1.4620];
cen4 = [0.8245 -0.0110 1.606];

ma5 = 5.24;
in5 = [0.0191 0.0032 0;0.0032 0.0228 0;0 0 0.0291];
cen5 = [1.2407 0.0180 1.606];

ma6 = 0.6;
in6 = [0.0012 0 0;0 0.0007 0;0 0 0.0007];
cen6 = [1.330 0 1.606];

Ma = [ma1 ma2 ma3 ma4 ma5 ma6]';
Ie1 = in1(:)';
Ie2 = in2(:)';
Ie3 = in3(:)';
Ie4 = in4(:)';
Ie5 = in5(:)';
Ie6 = in6(:)';

Cen = [cen1,cen2,cen3,cen4,cen5,cen6]';
Ie = [Ie1;Ie2;Ie3;Ie4;Ie5;Ie6];

% %% calculate ri: ith link mass center offset relative to ith joint frame,i=1,2,3,4,5,6

g=g01_0;
r1 = g\[Cen(1:3);1];
r1 = r1(1:3);
g=g*g12_0;
r2 = g\[Cen(4:6);1];
r2 = r2(1:3);
g=g*g23_0;
r3 = g\[Cen(7:9);1];
r3 = r3(1:3);
g=g*g34_0;
r4 = g\[Cen(10:12);1];
r4 = r4(1:3);
g=g*g45_0;
r5 = g\[Cen(13:15);1];
r5 = r5(1:3);
g=g*g56_0;
r6 = g\[Cen(16:18);1];
r6 = r6(1:3);

% %% calculate momentt of inertia in Ci,i=1,2,3,4,5,6
m1  = Ma(1);
I1  = reshape(Ie(1:9),3,3);
M1  = [ m1*eye(3),      -m1*hat(r1);
        m1*hat(r1),    I1 - m1*hat(r1)*hat(r1)];

m2  = Ma(2);
I2  = reshape(Ie(10:18),3,3);
M2  = [ m2*eye(3),      -m2*hat(r2);
        m2*hat(r2),    I2 - m2*hat(r2)*hat(r2)];

m3  = Ma(3);
I3  = reshape(Ie(19:27),3,3);
M3  = [ m3*eye(3),      -m3*hat(r3);
        m3*hat(r3),    I3 - m3*hat(r3)*hat(r3)];
    
m4  = Ma(4);
I4  = reshape(Ie(28:36),3,3);
M4  = [ m4*eye(3),      -m4*hat(r4);
        m4*hat(r4),    I4 - m4*hat(r4)*hat(r4)];
    
m5  = Ma(5);
I5  = reshape(Ie(37:45),3,3);
M5  = [ m5*eye(3),      -m5*hat(r5);
        m5*hat(r5),    I5 - m5*hat(r5)*hat(r5)];
    
m6  = Ma(6);
I6  = reshape(Ie(46:54),3,3);
M6  = [ m6*eye(3),      -m6*hat(r6);
        m6*hat(r6),    I6 - m6*hat(r6)*hat(r6)];    

%%%%%Acutual Dynamic Parameters for Euler Equation%%%%%%%%%%%%%%%%%%%%%    
Param_a =[M1(1,1);M1(2,6);-M1(1,6);M1(1,5);M1(4,4);M1(5,5);M1(6,6);M1(4,5);M1(4,6);M1(5,6);
         M2(1,1);M2(2,6);-M2(1,6);M2(1,5);M2(4,4);M2(5,5);M2(6,6);M2(4,5);M2(4,6);M2(5,6);
         M3(1,1);M3(2,6);-M3(1,6);M3(1,5);M3(4,4);M3(5,5);M3(6,6);M3(4,5);M3(4,6);M3(5,6);
         M4(1,1);M4(2,6);-M4(1,6);M4(1,5);M4(4,4);M4(5,5);M4(6,6);M4(4,5);M4(4,6);M4(5,6);
         M5(1,1);M5(2,6);-M5(1,6);M5(1,5);M5(4,4);M5(5,5);M5(6,6);M5(4,5);M5(4,6);M5(5,6);
         M6(1,1);M6(2,6);-M6(1,6);M6(1,5);M6(4,4);M6(5,5);M6(6,6);M6(4,5);M6(4,6);M6(5,6)];

     
%%
LoadIdn = load('Param_c.mat');
Param_ = LoadIdn.Param_c;
Param_c = Param_(1:60);

%%
% Acc = importdata('OptAcc.txt');
% Vel = importdata('OptVel.txt');
% Pos = importdata('OptPos.txt');
% D2R = 1/180*pi;
% PosRng(1,:)=[-135,135]*D2R;
% PosRng(2,:)=[-45,45]*D2R;
% PosRng(3,:)=[-45,45]*D2R;
% PosRng(4,:)=[-200,200]*D2R;
% PosRng(5,:)=[-100,100]*D2R;
% PosRng(6,:)=[-360,360]*D2R;
% 
% Vco = 0.75;
% VelRng(1,:)=[-190,190]*D2R*Vco;
% VelRng(2,:)=[-205,205]*D2R*Vco;
% VelRng(3,:)=[-210,210]*D2R*Vco;
% VelRng(4,:)=[-400,400]*D2R*Vco;
% VelRng(5,:)=[-360,360]*D2R*Vco;
% VelRng(6,:)=[-600,600]*D2R*Vco;
% 
% Aco = 0.5;
% AccRng(1,:)=[-180,180]*D2R*Aco;
% AccRng(2,:)=[-180,180]*D2R*Aco;
% AccRng(3,:)=[-540,540]*D2R*Aco;
% AccRng(4,:)=[-1600,1600]*D2R*Aco;
% AccRng(5,:)=[-1200,1200]*D2R*Aco;
% AccRng(6,:)=[-2400,2400]*D2R*Aco;
% 
% N=100;
% Pos = zeros(N,6);
% Vel = zeros(N,6);
% Acc = zeros(N,6);
% 
%  t=[0:1:N-1]*0.1*pi;
% for j=1:6
%     Acc(:,j) = 0.8*PosRng(j,2)/(2*pi) * sin(t)';
%     Vel(:,j) = 0.8*PosRng(j,2)/(2*pi)*(1 - cos(t)');
%     Pos(:,j) = 0.8*PosRng(j,2)/(2*pi)*(t' - sin(t)');
% end
ControlFile = 'C:\Users\DAI Dan\Desktop\Dynamic Debug\ActualData\20140611\ControlData.txt';
ConData = importdata(ControlFile);
D2R = pi/180;
Pos = ConData(:,1:6)*D2R;
Vel = ConData(:,7:12)*D2R;
Acc = ConData(:,13:18)*D2R;
Nc = size(ConData,1);
t=[0:1:Nc-1];
SmpT=t'*4e-3;
SimPos=[SmpT,Pos];
SimVel=[SmpT,Vel];
SimAcc=[SmpT,Acc];

% for i=1:6
%     figure(i);
%     plot(t,Vel(:,i));
%     grid on;
% end
%%
clear Wdv_N Trq_a Trq_c;

Ft =[0;0;0;0;0;0];
Ld = [DH(1,1) DH(1,2) DH(3,2) DH(3,3) DH(1,4) DH(3,4) DH(1,5) DH(1,6)];
K = [-145.7;140;-173.5;104.7;-100;-51.5];
VelThre = [0.0005,0.0005,0.0005,0.0008,0.0008,0.002];


Nv =  size(Acc,1);
for i=1:Nv
    
    Wdv = EulerWd(Ld,Pos(i,:),Vel(i,:),Acc(i,:));
    Wdv_N(6*(i-1)+1:6*i,1:60) = Wdv;
        
%     Wfvvp=zeros(6,6);
%     Wfvvn=zeros(6,6);
%     Wfsvp=zeros(6,6);
%     Wfsvn=zeros(6,6);
%     for j=1:6
%         if Vel(i,j)>=0
%             Wfvvp(j,j) = Vel(i,j);
%             Wfvvn(j,j) = 0;
%             if abs(Vel(i,j))>VelThre(j) 
%                 Wfsvp(j,j) = sign(Vel(i,j));
%             else
%                 Wfsvp(j,j)=0;
%             end
%         else
%             Wfvvp(j,j) = 0;
%             Wfvvn(j,j) = Vel(i,j);
%             if abs(Vel(i,j))>VelThre(j) 
%                 Wfsvn(j,j) = sign(Vel(i,j));
%             else
%                 Wfsvn(j,j)=0;
%             end
%         end
% 
%     end
        
 
%     Wdv_N(6*(i-1)+1:6*i,61:66) = Wfvvp;
%     Wdv_N(6*(i-1)+1:6*i,67:72) = Wfsvp;
%     Wdv_N(6*(i-1)+1:6*i,73:78) = Wfvvn;
%     Wdv_N(6*(i-1)+1:6*i,79:84) = Wfsvn; 

end

Trq_a = Wdv_N*Param_a;
Trq_c = Wdv_N*Param_c;

%%
t = [0:1:Nv-1];
for i=1:6
    figure(i);
    plot(t,Trq_a(i:6:end)/max(abs(Trq_a(i:6:end))),'g');
    hold on;    
    plot(t,Vel(:,i)/max(abs(Vel(:,i))),'b');
    hold on;
    plot(t,Trq_c(i:6:end)/max(abs(Trq_c(i:6:end))),'r');
    axis([0 900 -1.2 1.2]);
    hold off;
    grid on;
end

