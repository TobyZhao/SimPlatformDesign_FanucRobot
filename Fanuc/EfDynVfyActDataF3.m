%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%@Copyright(c),Googol Shenzhen Tech. Ltd
%@File Name: EfDynVfyActDataF3.m
%@Author: Dai Dan
%@Version: 1.0
%@Date: 14/03/2015
%
%@Description: To do dynamic verification for Efort Manipulator, only considering first 3 joints
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear all;
clc;

IniEnc =[109824;-2846557;-2698244;19752;-4211310;-6879];    %To ensure the same for different sampling
                                           
I2T = [0.73;0.73;0.5;0.4;0.4;0.39];
Gear = [-147;-153;153;-76.95;-80;-51];
IniJnt=[0;-pi/2;0;0;pi/2;0];
EncRes = 32768*4;
D2R = pi/180;
R2D = 180/pi;
JntNum=3;


%sctParam=load('EfIdnCndF3NmlLf1.mat');
sctParam=load('EfIdnCndF3NmlNf1.mat');
Param=sctParam.IdnParam;


% File='C:\Users\DAI Dan\Desktop\Learn\Dynamic Control\New Page\Experiment\20150306\ValidTrj1\ValTrj1.txt';
% SmpT = 31.25*230*1e-6;         
% File='C:\Users\DAI Dan\Desktop\Learn\Dynamic Control\New Page\Experiment\20150306\ValidTrj1\ValTrj2.txt';  %%%For Cnd Identification
% SmpT = 31.25*180*1e-6; 
% File='C:\Users\DAI Dan\Desktop\Learn\Dynamic Control\New Page\Experiment\20150306\ValidTrj1\ValTrj3.txt';  %%%For dOpt Identification
% SmpT = 31.25*180*1e-6; 
% File='C:\Users\DAI Dan\Desktop\Learn\Dynamic Control\New Page\Experiment\20150306\ValidTrj2\ValTrj50.txt';
% SmpT = 31.25*180*1e-6;      
File='C:\Users\DAI Dan\Desktop\Learn\Dynamic Control\New Page\Experiment\20150306\ValidTrj2\ValTrj100.txt';
SmpT = 31.25*150*1e-6;  
% File='C:\Users\DAI Dan\Desktop\Learn\Dynamic Control\New Page\Experiment\20150306\ValidTrj2\ValTrjH.txt';
% SmpT = 31.25*110*1e-6;      


%%%%%%%%%Efort Parameters%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%
DH=[0       0       0       504;
    -pi/2   170     -pi/2    0;
    0       780     0       0;
    -pi/2   140    0       760;
    pi/2    0       0       0;
    -pi/2   0       0       0;
    0       0       0       125]';
Ld=[504 170 780]/1000;
Bd=EulerBasis_F3(Ld);
gr=9.8;


%%%%%%%%Data Processing%%%%%%%%%%%%%
d=fdesign.lowpass('Fp,Fst,Ap,Ast',0.1,0.15,1,70);
Hd = design(d,'equiripple');

Data=importdata(File);

for i=1:JntNum
    oTrq(:,i)=Data(:,3*i-2)*I2T(i)*Gear(i);
    Trq(:,i)=filtfilt(Hd.Numerator,1,oTrq(:,i));
    oJnt(:,i)=(Data(:,3*i) - IniEnc(i))/EncRes/Gear(i)*2*pi + IniJnt(i);
    Jnt(:,i)=smooth(oJnt(:,i));
end

Nj=size(Jnt,1);
Pos=Jnt;
if mod(Nj,2)~=0 
    Pos(end,:)=[];
end
fs=1/SmpT;
for i=1:JntNum
    fftPos(:,i)=fft(Pos(:,i));
    Ns=size(Pos(:,i),1);
    fftPos(100:end-100,1)=0;
    Ks=[0:Ns/2-1,0,-Ns/2+1:-1]';
    jw=2j*pi*Ks*fs/Ns;
    fftsVel(:,i)=jw.*fftPos(:,i);
    Vel(:,i)=real(ifft(fftsVel(:,i)));
    
    fftsVel(100:end-100,1)=0;
    fftsAcc(:,i)=jw.*fftsVel(:,i);
    %fftsAcc(:,i)=-Ks.^2.*fftPos(:,i);

    Acc(:,i)=real(ifft(fftsAcc(:,i)));
    
    
    Acc(:,i)=filtfilt(Hd.Numerator,1,Acc(:,i));
end

if mod(Nj,2)~=0
        Vel(end+1,:)=0;
        Acc(end+1,:)=0;
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%Verification%%%%%%%%%%%%%%%%%%
Num=size(Trq,1);


for i=1:Num
   
    Wd = EulerWd_MinF3(Ld,Jnt(i,1:3),Vel(i,1:3),Acc(i,1:3),gr);
    Wd_N(3*(i-1)+1:3*i,1:30) = Wd;
     
    Wfv =[Vel(i,1)    0       0      ;
      0         Vel(i,2)  0       ;
      0         0       Vel(i,3)  ];

%     %%%%%%Method 1: classic coulomb 
%     Wfc =[sign(Vel(i,1))  0               0           ;
%       0             sign(Vel(i,2))    0               ;
%       0             0               sign(Vel(i,3))    ;]; 
    %%%%%%%Method 2: modified coulomb
     Wfc =[nthroot(Vel(i,1),3)    0       0       ;
      0         nthroot(Vel(i,2),3)  0       ;
      0         0       nthroot(Vel(i,3),3)  ;];
  
   Wd_N(3*(i-1)+1:3*i,31:33) = Wfv;
   Wd_N(3*(i-1)+1:3*i,34:36) = Wfc;
   
end
%%%%%%%%%%%To add friction coefficients%%%%%%%%%%%
Basis=[Bd               zeros(15,6);
       zeros(6,30)     eye(6)];
   
Wd_B=Wd_N*Basis'/(Basis*Basis');
Trq_c=Wd_B*Param;
Dyn_c=Wd_B(:,1:15)*Param(1:15);

%%
%%%%%%%%%%To plot actual and computed torque%%%%%%%%
for i=1:3
    figure(i);
    plot([0:1:Num-1]*SmpT, oTrq(:,i),'g');
    hold on;
    plot([0:1:Num-1]*SmpT, Trq(:,i),'b');
    hold on;
    plot([0:1:Num-1]*SmpT, Trq_c(i:3:end),'r');
    hold off;
    grid on;
    str=sprintf('Verification: Torque of Joint %d',i);
    title(str);
end

