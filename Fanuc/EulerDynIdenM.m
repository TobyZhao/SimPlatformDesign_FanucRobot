%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%@Copyright(c),Googol Shenzhen Tech. Ltd
%@File Name: EulerDynIden.m
%@Author: Dai Dan
%@Version: 1.0
%@Date: 13/5/2014
%
%@Description: Simulation of identifing the dynamic parameters,consider motor 
% Identification Trajectory: 1. Optimized  2. High Speed  3. Low Speed
% Add Gaussian Noise into data
% Consider Viscous+Colomb Friction Model instead of true complicate model
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear all;
clc;
%%%%%%%%%Load Data and interpolation (optional)%%%%%%%%%%%%
mode =3;
bMotor = false;
switch mode
    case 1
    LoadPos = load('as_optimal_pos.mat');
    LoadVel = load('as_optimal_vel.mat');
    LoadAcc = load('as_optimal_acc.mat');
    Pos_ = LoadPos.OptPos;
    Vel_ = LoadVel.OptVel;
    Acc_ = LoadAcc.OptAcc;
    case 2
    D2R = 1/180*pi;
    PosRng(1,:)=[-135,135]*D2R;
    PosRng(2,:)=[-45,45]*D2R;
    PosRng(3,:)=[-45,45]*D2R;
    PosRng(4,:)=[-200,200]*D2R;
    PosRng(5,:)=[-100,100]*D2R;
    PosRng(6,:)=[-360,360]*D2R;

    Vco = 0.75;
    VelRng(1,:)=[-190,190]*D2R*Vco;
    VelRng(2,:)=[-205,205]*D2R*Vco;
    VelRng(3,:)=[-210,210]*D2R*Vco;
    VelRng(4,:)=[-400,400]*D2R*Vco;
    VelRng(5,:)=[-360,360]*D2R*Vco;
    VelRng(6,:)=[-600,600]*D2R*Vco;

    Aco = 0.5;
    AccRng(1,:)=[-180,180]*D2R*Aco;
    AccRng(2,:)=[-180,180]*D2R*Aco;
    AccRng(3,:)=[-540,540]*D2R*Aco;
    AccRng(4,:)=[-1600,1600]*D2R*Aco;
    AccRng(5,:)=[-1200,1200]*D2R*Aco;
    AccRng(6,:)=[-2400,2400]*D2R*Aco;

    N=20;
    Pos_ = zeros(N,6);
    Vel_ = zeros(N,6);
    Acc_ = zeros(N,6);
    t=[0:1:N-1]*2*pi/N;
    for j=1:6
        Acc_(:,j) = 0.8*PosRng(j,2)/(2*pi) * sin(t)';
        Vel_(:,j) = 0.8*PosRng(j,2)/(2*pi)*(1 - cos(t)');
        Pos_(:,j) = 0.8*PosRng(j,2)/(2*pi)*(t' - sin(t)');
    end
    case 3
        %Load data from samples 
        DriveFile = 'C:\Users\DAI Dan\Desktop\Dynamic Debug\ActualData\20140613\DriveData.txt';
        IniEnc =[-160924;78898;4682241;82745;695941;-2462336];
        SmpT = 31.25*65*1e-6;
        StartIdx = round([270.156;282.344;164.531;318.906;233.594;239.688]/(31.25*65*1e-3));
        I2T = [0.77;0.77;0.524;0.375;0.375;0.375];
        K = [-145.7;140;-173.5;104.7;-100;-51.5];
        EncRes = 32768*4;
        Num=4;
        RawData = importdata(DriveFile);
        Nd =size(RawData,1);
        for i=1:6
            St(:,i) = RawData(:,Num*i-3)*1e-3;
            %Trq(:,i)=smooth(RawData(:,Num*i-2)*I2T(i)*K(i));
            Vel(:,i)=smooth(RawData(:,Num*i-1)*2*pi/60/K(i));
            Pos(:,i)=smooth((RawData(:,Num*i)-IniEnc(i))/EncRes/K(i)*2*pi); 
        end
        for i=1:Nd-1
            Acc(i+1,:) = (Vel(i+1,:) - Vel(i,:))./(St(i+1,:)-St(i,:));
        end
        for i=1:6
            Acc(:,i) = smooth(Acc(:,i));
        end
        Acc(1,:)=0;
    case 4
        %Generate data to simulate actual trajectory, control of degree of noise
    otherwise
end

switch mode
    case 1,2
    %%%%%%%5th order interpolation%%%%%%%%%%%%%%%
    N = size(Pos_,1);
    t_ = [0:1:N-1]';
    t = [0:0.25:N-1]';
    for i=1:6
        Pos(:,i) = interp1(t_,Pos_(:,i),t,'v5cubic');
        Vel(:,i) = interp1(t_,Vel_(:,i),t,'v5cubic');
        Acc(:,i) = interp1(t_,Acc_(:,i),t,'v5cubic');
    end
    %%%%%%%Group into identify and verify set%%%%%%%%%%%%%
    PosIdn = Pos([1:4,6:9,11:14,16:19,21:24,26:29,31:34,36:39,41:44,46:49,51:54,56:59],:);
    VelIdn = Vel([1:4,6:9,11:14,16:19,21:24,26:29,31:34,36:39,41:44,46:49,51:54,56:59],:);
    AccIdn = Acc([1:4,6:9,11:14,16:19,21:24,26:29,31:34,36:39,41:44,46:49,51:54,56:59],:);

    PosVfy = Pos([5,10,15,20,25,30,35,40,45,50,55,60],:);
    VelVfy = Vel([5,10,15,20,25,30,35,40,45,50,55,60],:);
    AccVfy = Acc([5,10,15,20,25,30,35,40,45,50,55,60],:);
    case 3
    IdnNum = 350;
    IdnStep = 5;
    for i=1:6        
        PosIdn(:,i) = Pos(StartIdx(i):IdnStep:(StartIdx(i)+IdnStep*(IdnNum-1)),i);
        VelIdn(:,i) = Vel(StartIdx(i):IdnStep:(StartIdx(i)+IdnStep*(IdnNum-1)),i);
        AccIdn(:,i) = Acc(StartIdx(i):IdnStep:(StartIdx(i)+IdnStep*(IdnNum-1)),i);
        
        PosVfy(:,i) = Pos(StartIdx(i):(StartIdx(i)+IdnStep*(IdnNum-1)),i);
        VelVfy(:,i) = Vel(StartIdx(i):(StartIdx(i)+IdnStep*(IdnNum-1)),i);
        AccVfy(:,i) = Acc(StartIdx(i):(StartIdx(i)+IdnStep*(IdnNum-1)),i);
    end
    otherwise
end


% figure(1);
% plot(t,Pos);
% hold on;
% plot(t_,Pos_,'.');
% grid on;
% figure(2);
% plot(t,Vel);
% hold on;
% plot(t_,Vel_,'.');
% grid on;
% figure(3);
% plot(t,Acc);
% hold on;
% plot(t_,Acc_,'.');
% grid on;
%%%%%%%%%%Condition Number of Wd matrix%%%%%%%%%%%%%%%
N = size(PosIdn,1);
X0 = zeros(18*N,1);
for i=1:N
    X0(18*(i-1)+1:18*(i-1)+6) = PosIdn(i,:)';
    X0(18*(i-1)+7:18*(i-1)+12) = VelIdn(i,:)';
    X0(18*(i-1)+13:18*i) = AccIdn(i,:)';
end
%Cnd = EulerCondM(X0);
Cnd = EulerCond(X0);
disp('Condition Number of Wd Matrix with Sampled Points');
disp(Cnd);

%%%%%%%%%%%Assume nominal and actual dynamic parameters%%%%%%%%%%%%%%
%%%%DH parameters, unit:m %%%%%%%%%
DH=[266     300     0       0       1016     0      174;
    0       0       -pi/2   0       pi      pi       0;
    0       150     870     170     0       0        0;
    0       -pi/2   0       -pi/2   -pi/2    -pi/2   0;];
DH(1,:) = DH(1,:)/1000;
DH(3,:) = DH(3,:)/1000;

K = [1 1 1 1 1 1];
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
% Motor Inertia
Imz1 = 0.65*1e-3;
Imz2 = 0.65*1e-3;
Imz3 = 0.047*1e-3;
Imz4 = 0.017*1e-3;
Imz5 = 0.017*1e-3;
Imz6 = 0.017*1e-3;

Fv1 =5;
Fv2 =5;
Fv3 =5;
Fv4 =5;
Fv5 =5;
Fv6 =5;

Fs1 =0.3;
Fs2 =0.3;
Fs3 =0.3;
Fs4 =0.3;
Fs5 =0.3;
Fs6 =0.3;

%%%%%Acutual Dynamic Parameters for Euler Equation%%%%%%%%%%%%%%%%%%%%%
if bMotor
Param_a =[M1(1,1);M1(2,6);-M1(1,6);M1(1,5);M1(4,4);M1(5,5);M1(6,6);M1(4,5);M1(4,6);M1(5,6);
         M2(1,1);M2(2,6);-M2(1,6);M2(1,5);M2(4,4);M2(5,5);M2(6,6);M2(4,5);M2(4,6);M2(5,6);
         M3(1,1);M3(2,6);-M3(1,6);M3(1,5);M3(4,4);M3(5,5);M3(6,6);M3(4,5);M3(4,6);M3(5,6);
         M4(1,1);M4(2,6);-M4(1,6);M4(1,5);M4(4,4);M4(5,5);M4(6,6);M4(4,5);M4(4,6);M4(5,6);
         M5(1,1);M5(2,6);-M5(1,6);M5(1,5);M5(4,4);M5(5,5);M5(6,6);M5(4,5);M5(4,6);M5(5,6);
         M6(1,1);M6(2,6);-M6(1,6);M6(1,5);M6(4,4);M6(5,5);M6(6,6);M6(4,5);M6(4,6);M6(5,6);
         Imz1;Imz2;Imz3;Imz4;Imz5;Imz6;
         Fv1;Fv2;Fv3;Fv4;Fv5;Fv6;
         Fs1;Fs2;Fs3;Fs4;Fs5;Fs6];
else
Param_a =[M1(1,1);M1(2,6);-M1(1,6);M1(1,5);M1(4,4);M1(5,5);M1(6,6);M1(4,5);M1(4,6);M1(5,6);
     M2(1,1);M2(2,6);-M2(1,6);M2(1,5);M2(4,4);M2(5,5);M2(6,6);M2(4,5);M2(4,6);M2(5,6);
     M3(1,1);M3(2,6);-M3(1,6);M3(1,5);M3(4,4);M3(5,5);M3(6,6);M3(4,5);M3(4,6);M3(5,6);
     M4(1,1);M4(2,6);-M4(1,6);M4(1,5);M4(4,4);M4(5,5);M4(6,6);M4(4,5);M4(4,6);M4(5,6);
     M5(1,1);M5(2,6);-M5(1,6);M5(1,5);M5(4,4);M5(5,5);M5(6,6);M5(4,5);M5(4,6);M5(5,6);
     M6(1,1);M6(2,6);-M6(1,6);M6(1,5);M6(4,4);M6(5,5);M6(6,6);M6(4,5);M6(4,6);M6(5,6);
     Fv1;Fv2;Fv3;Fv4;Fv5;Fv6;
     Fs1;Fs2;Fs3;Fs4;Fs5;Fs6];
end

     
%%%%%%%Nominal Dynamic Parameters%%%%%%%%%%%%
% ma1 = 170.31;
% in1 = [5.2954 -0.2565 -0.6366;-0.2565 4.7000 0.2830;-0.6366 0.2829 5.8635];
% cen1 = [0.0407 -0.0528 0.4702];
ma1_n = 170;
in1_n = [5 -0.3 -0.6;-0.3 5 0.3;-0.6 0.3 5.9];
cen1_n = [0.04 -0.05 0.48];

% ma2 = 63.74;
% in2 = [5.8840 0.0072 0.0135;0.0072 6.0178 -0.1907;0.0135 -0.1907 0.3374];
% cen2 = [0.1510 0.1746 0.9687];
ma2_n = 60;
in2_n = [6 0 0.01;0 6 -0.2;0.01 -0.2 0.3];
cen2_n = [0.15 0.17 0.97];

% ma3 = 98.98;
% in3 = [1.8201 -0.2274 -0.3112;-0.2274 2.2537 -0.1441;-0.3112 -0.1441 1.9485];
% cen3 = [0.1568 -0.0318 1.5191];
ma3_n = 100;
in3_n = [1.8 -0.2 -0.3;-0.2 2.3 -0.14;-0.3 -0.14 2];
cen3_n = [0.16 -0.03 1.5];

% ma4 = 24.46;
% in4 = [0.0607 -0.0922 0;-0.0922 1.4493 0;0 0,1.4620];
% cen4 = [0.8245 -0.0110 1.606];
ma4_n = 20;
in4_n = [0.06 -0.1 0;-0.1 1.4 0;0 0 1.5];
cen4_n = [0.8 -0.01 1.6];

% ma5 = 5.24;
% in5 = [0.0191 0.0032 0;0.0032 0.0228 0;0 0 0.0291];
% cen5 = [1.2407 0.0180 1.606];
ma5_n = 5;
in5_n = [0.02 0.003 0;0.003 0.02 0;0 0 0.03];
cen5_n = [1.2 0.02 1.6];

% ma6 = 0.6;
% in6 = [0.0012 0 0;0 0.0007 0;0 0 0.0007];
% cen6 = [1.330 0 1.606];
ma6_n = 0.7;
in6_n = [0.001 0 0;0 0.0008 0;0 0 0.0008];
cen6_n = [1.3 0 1.6];

Ma_n = [ma1_n ma2_n ma3_n ma4_n ma5_n ma6_n]';
Ie1_n = in1_n(:)';
Ie2_n = in2_n(:)';
Ie3_n = in3_n(:)';
Ie4_n = in4_n(:)';
Ie5_n = in5_n(:)';
Ie6_n = in6_n(:)';

Cen_n = [cen1_n,cen2_n,cen3_n,cen4_n,cen5_n,cen6_n]';
Ie_n = [Ie1_n;Ie2_n;Ie3_n;Ie4_n;Ie5_n;Ie6_n];

% %% calculate ri: ith link mass center offset relative to ith joint frame,i=1,2,3,4,5,6

g=g01_0;
r1_n = g\[Cen_n(1:3);1];
r1_n = r1_n(1:3);
g=g*g12_0;
r2_n = g\[Cen_n(4:6);1];
r2_n = r2_n(1:3);
g=g*g23_0;
r3_n = g\[Cen_n(7:9);1];
r3_n = r3_n(1:3);
g=g*g34_0;
r4_n = g\[Cen_n(10:12);1];
r4_n = r4_n(1:3);
g=g*g45_0;
r5_n = g\[Cen_n(13:15);1];
r5_n = r5_n(1:3);
g=g*g56_0;
r6_n = g\[Cen_n(16:18);1];
r6_n = r6_n(1:3);

% %% calculate momentt of inertia in Ci,i=1,2,3,4,5,6
m1_n  = Ma_n(1);
I1_n  = reshape(Ie_n(1:9),3,3);
M1_n  = [ m1_n*eye(3),      -m1_n*hat(r1_n);
        m1_n*hat(r1_n),    I1_n - m1_n*hat(r1_n)*hat(r1_n)];

m2_n  = Ma_n(2);
I2_n  = reshape(Ie_n(10:18),3,3);
M2_n  = [ m2_n*eye(3),      -m2_n*hat(r2_n);
        m2_n*hat(r2_n),    I2_n - m2_n*hat(r2_n)*hat(r2_n)];

m3_n  = Ma_n(3);
I3_n  = reshape(Ie_n(19:27),3,3);
M3_n  = [ m3_n*eye(3),      -m3_n*hat(r3_n);
        m3_n*hat(r3_n),    I3_n - m3_n*hat(r3_n)*hat(r3_n)];
    
m4_n  = Ma_n(4);
I4_n = reshape(Ie_n(28:36),3,3);
M4_n  = [ m4_n*eye(3),      -m4_n*hat(r4_n);
        m4_n*hat(r4_n),    I4_n - m4_n*hat(r4_n)*hat(r4_n)];
    
m5_n  = Ma_n(5);
I5_n  = reshape(Ie_n(37:45),3,3);
M5_n  = [ m5_n*eye(3),      -m5_n*hat(r5_n);
        m5_n*hat(r5_n),    I5_n - m5_n*hat(r5_n)*hat(r5_n)];
    
m6_n  = Ma_n(6);
I6_n  = reshape(Ie_n(46:54),3,3);
M6_n  = [ m6_n*eye(3),      -m6_n*hat(r6_n);
        m6_n*hat(r6_n),    I6_n - m6_n*hat(r6_n)*hat(r6_n)];    

% Motor Inertia
% Imz1_n = 0.6*1e-3;
% Imz2_n = 0.6*1e-3;
% Imz3_n = 0.05*1e-3;
% Imz4_n = 0.015*1e-3;
% Imz5_n = 0.015*1e-3;
% Imz6_n = 0.015*1e-3;
Imz1_n = 0.65*1e-3;
Imz2_n = 0.65*1e-3;
Imz3_n = 0.047*1e-3;
Imz4_n = 0.017*1e-3;
Imz5_n = 0.017*1e-3;
Imz6_n = 0.017*1e-3;

Fv1_n =0;
Fv2_n =0;
Fv3_n =0;
Fv4_n =0;
Fv5_n =0;
Fv6_n =0;

Fs1_n =0;
Fs2_n =0;
Fs3_n =0;
Fs4_n =0;
Fs5_n =0;
Fs6_n =0;

%%%%%Acutual Dynamic Parameters for Euler Equation%%%%%%%%%%%%%%%%%%%%%
if bMotor
Param_n =[M1_n(1,1);M1_n(2,6);-M1_n(1,6);M1_n(1,5);M1_n(4,4);M1_n(5,5);M1_n(6,6);M1_n(4,5);M1_n(4,6);M1_n(5,6);
         M2_n(1,1);M2_n(2,6);-M2_n(1,6);M2_n(1,5);M2_n(4,4);M2_n(5,5);M2_n(6,6);M2_n(4,5);M2_n(4,6);M2_n(5,6);
         M3_n(1,1);M3_n(2,6);-M3_n(1,6);M3_n(1,5);M3_n(4,4);M3_n(5,5);M3_n(6,6);M3_n(4,5);M3_n(4,6);M3_n(5,6);
         M4_n(1,1);M4_n(2,6);-M4_n(1,6);M4_n(1,5);M4_n(4,4);M4_n(5,5);M4_n(6,6);M4_n(4,5);M4_n(4,6);M4_n(5,6);
         M5_n(1,1);M5_n(2,6);-M5_n(1,6);M5_n(1,5);M5_n(4,4);M5_n(5,5);M5_n(6,6);M5_n(4,5);M5_n(4,6);M5_n(5,6);
         M6_n(1,1);M6_n(2,6);-M6_n(1,6);M6_n(1,5);M6_n(4,4);M6_n(5,5);M6_n(6,6);M6_n(4,5);M6_n(4,6);M6_n(5,6);
         Imz1_n;Imz2_n;Imz3_n;Imz4_n;Imz5_n;Imz6_n;
         Fv1_n;Fv2_n;Fv3_n;Fv4_n;Fv5_n;Fv6_n;
         Fs1_n;Fs2_n;Fs3_n;Fs4_n;Fs5_n;Fs6_n];
else
Param_n =[M1_n(1,1);M1_n(2,6);-M1_n(1,6);M1_n(1,5);M1_n(4,4);M1_n(5,5);M1_n(6,6);M1_n(4,5);M1_n(4,6);M1_n(5,6);
         M2_n(1,1);M2_n(2,6);-M2_n(1,6);M2_n(1,5);M2_n(4,4);M2_n(5,5);M2_n(6,6);M2_n(4,5);M2_n(4,6);M2_n(5,6);
         M3_n(1,1);M3_n(2,6);-M3_n(1,6);M3_n(1,5);M3_n(4,4);M3_n(5,5);M3_n(6,6);M3_n(4,5);M3_n(4,6);M3_n(5,6);
         M4_n(1,1);M4_n(2,6);-M4_n(1,6);M4_n(1,5);M4_n(4,4);M4_n(5,5);M4_n(6,6);M4_n(4,5);M4_n(4,6);M4_n(5,6);
         M5_n(1,1);M5_n(2,6);-M5_n(1,6);M5_n(1,5);M5_n(4,4);M5_n(5,5);M5_n(6,6);M5_n(4,5);M5_n(4,6);M5_n(5,6);
         M6_n(1,1);M6_n(2,6);-M6_n(1,6);M6_n(1,5);M6_n(4,4);M6_n(5,5);M6_n(6,6);M6_n(4,5);M6_n(4,6);M6_n(5,6);
         Fv1_n;Fv2_n;Fv3_n;Fv4_n;Fv5_n;Fv6_n;
         Fs1_n;Fs2_n;Fs3_n;Fs4_n;Fs5_n;Fs6_n];    
end


%%%%%Identification%%%%%%%%
Ni =  size(PosIdn,1);
Ft =[0;0;0;0;0;0];
Ld = [DH(1,1) DH(1,2) DH(3,2) DH(3,3) DH(1,4) DH(3,4) DH(1,5) DH(1,6)];
ParamNum=size(Param_n,1);
Noise=1;

for i=1:Ni
    Wd = EulerWd(Ld,PosIdn(i,:),VelIdn(i,:),AccIdn(i,:));
    Wm = EulerWm(Ld,K,PosIdn(i,:),VelIdn(i,:),AccIdn(i,:));
    Wfv =[VelIdn(i,1)    0       0       0       0       0;
      0         VelIdn(i,2)  0       0       0       0;
      0         0       VelIdn(i,3)  0       0       0;
      0         0       0       VelIdn(i,4)  0       0;
      0         0       0       0       VelIdn(i,5)  0;
      0         0       0       0       0       VelIdn(i,6)];
    Wfs =[sign(VelIdn(i,1))  0               0               0               0               0;
      0             sign(VelIdn(i,2))    0               0               0               0;
      0             0               sign(VelIdn(i,3))    0               0               0;
      0             0               0               sign(VelIdn(i,4))    0               0;
      0             0               0               0               sign(VelIdn(i,5))    0;
      0             0               0               0               0               sign(VelIdn(i,6))]; 
  
    if bMotor
    Trq_a(6*(i-1)+1:6*i,1) =  Wd*Param_a(1:60) + Wm*Param_a(61:66) + Wfv*Param_a(67:72) + Wfs*Param_a(73:78) + (-Noise+2*Noise*rand());
    else
    Trq_a(6*(i-1)+1:6*i,1) =  Wd*Param_a(1:60) + Wm*[Imz1_n;Imz2_n;Imz3_n;Imz4_n;Imz5_n;Imz6_n] + Wfv*Param_a(61:66) + Wfs*Param_a(67:72) + (-Noise+2*Noise*rand());    
    end
    
    Wd_N(6*(i-1)+1:6*i,1:60) = Wd;
    if bMotor
        Wd_N(6*(i-1)+1:6*i,61:66) = Wm;    
        Wd_N(6*(i-1)+1:6*i,67:72) = Wfv;
        Wd_N(6*(i-1)+1:6*i,73:78) = Wfs;            
    else
        TrqM(6*(i-1)+1:6*i,1) = Wm* [Imz1_n;Imz2_n;Imz3_n;Imz4_n;Imz5_n;Imz6_n];
        Wd_N(6*(i-1)+1:6*i,61:66) = Wfv;
        Wd_N(6*(i-1)+1:6*i,67:72) = Wfs;      
    end
    
end
[Q,R,E] = qr(Wd_N);
Tau = 6*N*(2.2204e-16)*R(1,1);
Num = size(find(diag(R)>Tau),1);
Q1 = Q(:,1:Num);
R1 = R(1:Num,1:Num);
R2 = R(1:Num,Num+1:end);
Wd_ = Q1*R1;

% %%
Pe_n = E\Param_n;
P1_n = Pe_n(1:Num);
P2_n = Pe_n(Num+1:end);
P_n = P1_n+R1\R2*P2_n;

Pe_a = E\Param_a;
P1_a = Pe_a(1:Num);
P2_a = Pe_a(Num+1:end);
P_a = P1_a+R1\R2*P2_a;

if bMotor
    P_c = pinv(Wd_)*Trq_a;
else
    P_c = pinv(Wd_)*(Trq_a-TrqM);
end

Rt = R1\R2;
Rt(find(abs(Rt)<Tau)) = 0;
P2_c = ones(ParamNum-Num,1);
P2_c(~any(Rt,1),:)=0;
P1_c = P_c - R1\R2*P2_c;
Param_c = E*[P1_c;P2_c];

P_  =[P_a,P_n,P_c];
P1_ = [P1_a,P1_n,P1_c];
P2_ = [P2_a,P2_n,P2_c];
Param_ = [Param_a,Param_n,Param_c];


if bMotor
    Trq_c = Wd_N*Param_c;
    Trq_n = Wd_N*Param_n;
else
    Trq_c = Wd_N*Param_c + TrqM;
    Trq_n = Wd_N*Param_n + TrqM;
end
ErrIdn_n = abs(Trq_a - Trq_n);
ErrIdn_c = abs(Trq_a - Trq_c);
disp('Identification Set:');
disp('   NomMax |  NomMean |  IdnMax |  IdnMean');
disp([max(ErrIdn_n),mean(ErrIdn_n),max(ErrIdn_c),mean(ErrIdn_c)]);


% %%%%%%%Verify%%%%%%%%%%%%%%%
Nv =  size(PosVfy,1);
for i=1:Nv
    Wdv = EulerWd(Ld,PosVfy(i,:),VelVfy(i,:),AccVfy(i,:));
    Wmv = EulerWm(Ld,K,PosVfy(i,:),VelVfy(i,:),AccVfy(i,:));
    
    Wfvv =[VelVfy(i,1)    0       0       0       0       0;
      0         VelVfy(i,2)  0       0       0       0;
      0         0       VelVfy(i,3)  0       0       0;
      0         0       0       VelVfy(i,4)  0       0;
      0         0       0       0       VelVfy(i,5)  0;
      0         0       0       0       0       VelVfy(i,6)];
    Wfsv =[sign(VelVfy(i,1))  0               0               0               0               0;
      0             sign(VelVfy(i,2))    0               0               0               0;
      0             0               sign(VelVfy(i,3))    0               0               0;
      0             0               0               sign(VelVfy(i,4))    0               0;
      0             0               0               0               sign(VelVfy(i,5))    0;
      0             0               0               0               0               sign(VelVfy(i,6))]; 
  
    if bMotor
    Trq_av(6*(i-1)+1:6*i,1) =  Wdv*Param_a(1:60) + Wmv*Param_a(61:66) + Wfvv*Param_a(67:72) + Wfsv*Param_a(73:78) + (-Noise+2*Noise*rand());
    else
    Trq_av(6*(i-1)+1:6*i,1) =  Wdv*Param_a(1:60) + Wmv*[Imz1_n;Imz2_n;Imz3_n;Imz4_n;Imz5_n;Imz6_n] + Wfvv*Param_a(61:66) + Wfsv*Param_a(67:72) + (-Noise+2*Noise*rand());    
    end
    
    Wdv_N(6*(i-1)+1:6*i,1:60) = Wdv;
    if bMotor
        Wdv_N(6*(i-1)+1:6*i,61:66) = Wmv;    
        Wdv_N(6*(i-1)+1:6*i,67:72) = Wfvv;
        Wdv_N(6*(i-1)+1:6*i,73:78) = Wfsv;            
    else
        TrqMv(6*(i-1)+1:6*i,1) = Wmv* [Imz1_n;Imz2_n;Imz3_n;Imz4_n;Imz5_n;Imz6_n];
        Wdv_N(6*(i-1)+1:6*i,61:66) = Wfvv;
        Wdv_N(6*(i-1)+1:6*i,67:72) = Wfsv;      
    end
  
end


if bMotor
    Trq_cv = Wdv_N*Param_c;
    Trq_nv = Wdv_N*Param_n;
else
    Trq_cv = Wdv_N*Param_c + TrqMv;
    Trq_nv = Wdv_N*Param_n + TrqMv;
end
ErrVfy_n = abs(Trq_av - Trq_nv);
ErrVfy_c = abs(Trq_av - Trq_cv);

disp('Verification Set:');
disp('   NomMax |  NomMean |  IdnMax |  IdnMean');
disp([max(ErrVfy_n),mean(ErrVfy_n),max(ErrVfy_c),mean(ErrVfy_c)]);

%% Classify parameters into different types
% syms sM1 sIxx1 sIxy1 sIxz1 sIyy1 sIyz1 sIzz1 sMrx1 sMry1 sMrz1
% syms sM2 sIxx2 sIxy2 sIxz2 sIyy2 sIyz2 sIzz2 sMrx2 sMry2 sMrz2
% syms sM3 sIxx3 sIxy3 sIxz3 sIyy3 sIyz3 sIzz3 sMrx3 sMry3 sMrz3
% syms sM4 sIxx4 sIxy4 sIxz4 sIyy4 sIyz4 sIzz4 sMrx4 sMry4 sMrz4
% syms sM5 sIxx5 sIxy5 sIxz5 sIyy5 sIyz5 sIzz5 sMrx5 sMry5 sMrz5
% syms sM6 sIxx6 sIxy6 sIxz6 sIyy6 sIyz6 sIzz6 sMrx6 sMry6 sMrz6
% syms sImz1 sImz2 sImz3 sImz4 sImz5 sImz6 
% syms sFv1 sFv2 sFv3 sFv4 sFv5 sFv6
% syms sFs1 sFs2 sFs3 sFs4 sFs5 sFs6
% 
% sParam = [sM1; sMrx1; sMry1; sMrz1; sIxx1; sIyy1; sIzz1; sIxy1; sIxz1; sIyz1;
%           sM2; sMrx2; sMry2; sMrz2; sIxx2; sIyy2; sIzz2; sIxy2; sIxz2; sIyz2;
%           sM3; sMrx3; sMry3; sMrz3; sIxx3; sIyy3; sIzz3; sIxy3; sIxz3; sIyz3;
%           sM4; sMrx4; sMry4; sMrz4; sIxx4; sIyy4; sIzz4; sIxy4; sIxz4; sIyz4;
%           sM5; sMrx5; sMry5; sMrz5; sIxx5; sIyy5; sIzz5; sIxy5; sIxz5; sIyz5;
%           sM6; sMrx6; sMry6; sMrz6; sIxx6; sIyy6; sIzz6; sIxy6; sIxz6; sIyz6;
%           sImz1; sImz2; sImz3; sImz4; sImz5; sImz6;
%           sFv1;sFv2;sFv3;sFv4;sFv5;sFv6;
%           sFs1;sFs2;sFs3;sFs4;sFs5;sFs6];
% 
% sPe = E\sParam;
% sP1 = sPe(1:Num);
% sP2 = sPe(Num+1:end);
% Rt = R1\R2;
% Rt(find(abs(Rt)<Tau)) = 0;
% sP = (sP1 + Rt*sP2);
% AbsUn = sP2(~any(Rt,1),:)
% AbsId = sP1(~any(Rt,2),:)