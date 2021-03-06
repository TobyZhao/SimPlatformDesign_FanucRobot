%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%@Copyright(c),Googol Shenzhen Tech. Ltd
%@File Name: DynEulerTest.m
%@Author: Dai Dan
%@Version: 1.0
%@Date: 05/5/2014
%
%@Description: Testing Newton-Euler Recursion Algorithm, temporary test file
%Trajectory Data: OutAngel1,OutAcc1,OutVel1
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% %% Mass: kg  Inertia: kg/m^2  Center: m
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

Ma = [ma1; ma2; ma3; ma4; ma5; ma6];
Ie1 = in1(:);
Ie2 = in2(:);
Ie3 = in3(:);
Ie4 = in4(:);
Ie5 = in5(:);
Ie6 = in6(:);
Cen = [cen1,cen2,cen3,cen4,cen5,cen6];
Cen = Cen';

% %% Parameters For Newton Euler Dynamics
%DH parameters
%DH parameters: d(z),theta(z),a(z),alpha(x),
%DH(1): Joint 1 Frame ----> Base Frame
%DH(2): Joint 2 Frame ----> Joint 1 Frame
%.......
%DH(6): Joint 6 Frame ----> Joint 5 Frame
%DH(7): Tool Frame    ----> Joint 6 Frame
%For DH parameters, we didn't include tool frame considering different kinds of tools.

DH_EU=[266     300     0       0       1016     0      174;
    0       0       -pi/2   0       pi      pi       0;
    0       150     870     170     0       0        0;
    0       -pi/2   0       -pi/2   -pi/2    -pi/2   0;];
DH_EU(1,:) = DH_EU(1,:)/1000;
DH_EU(3,:) = DH_EU(3,:)/1000;

Ma_EU = Ma;
Cen_EU = Cen;
Ie_EU = [Ie1;Ie2;Ie3;Ie4;Ie5;Ie6];
Ft_EU = [0;0;0;0;0;0];
% Pos_EU = [0;0;0;0;30;0]/180*pi;
% Vel_EU = [0;0;0;0;0;0]/180*pi;
% Acc_EU = [3.9331;0;0;-6.8089;0;7.8622]/180*pi;
for j=1:63
    Pos_EU = OutAngle1.signals.values(j,:);
    Vel_EU = OutOmega1.signals.values(j,:);
    Acc_EU = OutAcc1.signals.values(j,:);

    Torque(:,j) = DynEuler(DH_EU,Ma_EU,Cen_EU,Ie_EU,Ft_EU,Pos_EU,Vel_EU,Acc_EU);
end
for j=1:6
figure(j);
plot([0:0.15:62*0.15],Torque(j,:));
hold on;
plot([0:0.15:62*0.15],OutEnTau.signals.values(:,j),'r');
hold on;
plot([0:0.15:62*0.15],OutCalTau.signals.values(:,j),'g');
grid on;
end



% Pos_EU = OutAngle.signals.values(2,:)/180*pi;
% Vel_EU = OutOmega.signals.values(2,:)/180*pi;
% Acc_EU = OutAcc.signals.values(2,:)/180*pi;
% 
% 
% Torque = DynEuler(DH,Ma_EU,Cen_EU,Ie_EU,Ft,Pos_EU,Vel_EU,Acc_EU)
