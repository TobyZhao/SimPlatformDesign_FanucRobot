%%
close all;
clear all;
clc;
% l1 = 700;
% l2 = 210;
% l3 = 600;
% l4 = 100;
% l5 = 550;
% l6 = 100;
% l7 = 50;
% l8 = 0;
% l9 = -50;
l1 = 566;
l2 = 150;
l3 = 870;
l4 = 170;
l5 = 1016;
l6 = 154;
l7 = 20;
l8 = 0;
l9 = 0;
l = [l1 l2 l3 l4 l5 l6 l7 l8 l9];
%% forward kinemactic test
a1 = 0;
a2 = 0;
a3 = 0;
a4 = 0;
a5 = 30;
a6 = 0;
a = [a1 a2 a3 a4 a5 a6] / 180 *pi;


% figure(1)
% ShowConfig(l,a);
% 
% a1 = 0;
% a2 = 30;
% a3 = 45;
% a4 = 180;
% a5 = -30;
% a6 = -90;
% a = [a1 a2 a3 a4 a5 a6] / 180 *pi;
% figure(2)
% ShowConfig(l,a);

%% inverse kinematic test

% gd = fwd_kin(l,a);
% gd1 = gd(:,4);
% 
% [theta,Num] = inv_kin(gd,l);
% if Num>0    
%     for i = 1:Num
%         figure(i);
%         ShowConfig(l,theta(:,i)');
% 
%     end
% end
% disp(theta/pi*180);
% view([135 30]);

%% Drawing a circle in the plan; Pos control
% a1 = 0;
% a2 = 0;
% a3 = 0;
% a4 = 0;
% a5 = 0;
% a6 = 0;
% a = [a1 a2 a3 a4 a5 a6] / 180 *pi;
% 
% r = 80;
% cen = [l2+l5+l6+l7+r l8 l1+l3+l4+l9]';
% 
% gd(:,1)=[l2+l5+l6+l7 l8 l1+l3+l4+l9 1]';
% figure;
% p = zeros(360,3);
% N=360;
% for i = 1:N
%     phi = i/180*pi;
%     gd(1,1) = cen(1) - r*cos(phi);
%     gd(2,1) = cen(2) - r*sin(phi);
%     gd(3,1) = cen(3);
%     
%     theta = inv_kin(gd,l);
%     ShowConfig(l,theta(:,1)');
%     %disp(theta(:,1)/pi*180);
%     
%     g = fwd_kin(l,theta(:,1)');
%     p(i,:) = g(1:3,4)';
%     
%     hold on;
%     plot3(p(1:i,1),p(1:i,2),p(1:i,3),'r.');
%     hold off;
%     
%     drawnow;
% end
%  figure(2);
%  plot(p(1:N,1),p(1:N,2),'r.');

%% Jacobian Control Test, with angluar velocity controled

% a1 = 0;
% a2 = 0;
% a3 = 0;
% a4 = 0;
% a5 = 30; % in order to avoid singular situation where joint 6 and joint 4 are collinear
% a6 = 0;
% a = [a1 a2 a3 a4 a5 a6] / 180 *pi;
% 
% 
% r = 60;
% N = 360;
% p = zeros(N,3);
% daM =zeros(N,6);
% da = [0 0 0 0 0 0];
% dt =0.1;
% 
% cen = [l2+l5+l6+l7-r l8 l1+l3+l4+l9]'; 
% gd = fwd_kin(l,a);
% 
% 
% for i = 1:N
%     
%     ang = i/180*pi;
%     
%     gd(1,4) = cen(1) + r*cos(ang);
%     gd(2,4) = cen(2) - r*sin(ang);
%     gd(3,4) = cen(3);
% 
%     a = inv_kin(gd,l);
%     Showconfig(l,a(:,2)');
%     
%     V = r*[-sin(ang) cos(ang) 0 0 0 0]';
%    
%     g = fwd_kin(l,a(:,2)');
%     p(i,:) = g(1:3,4)';
%     hold on;
%     plot3(p(1:i,1),p(1:i,2),p(1:i,3),'r.');
%     hold off;
%     drawnow;   
% 
%     
%     Jb = body_Jacobian(l,a(:,2)');
%     Adg_inv = double(AdjointInv(g));
%     da = double((Jb \ Adg_inv* V)');
%     daM(i,:)=da;
%     
% end
% figure(2);
% plot(p(1:N,1),p(1:N,2),'r.');
% figure(3);
% plot([1:1:N],daM(:,1),'b');
% hold on;
% plot([1:1:N],daM(:,2),'g');
% hold on;
% plot([1:1:N],daM(:,3),'r');
% hold on;
% plot([1:1:N],daM(:,4),'b.');
% hold on;
% plot([1:1:N],daM(:,5),'g.');
% hold on;
% plot([1:1:N],daM(:,6),'r.');
% hold on;


%% Trajectory Test 1D
% qo=30;qf=120;vo=0;vf=0;ao=0;af=0;
% vm=10;am=5;jm=5;
% [Flag,Ta,Tv,Td,Tj1,Tj2,qt,vt,at,jt]=doubleS(qo,qf,vo,vf,ao,af,vm,am,jm);
% 
% t=[0:0.1:Ta+Tv+Td]';
% if Flag
%     figure(1);
%     plot(t,qt);
%     figure(2);
%     plot(t,vt);
%     figure(3);
%     plot(t,at);
%     figure(4);
%     plot(t,jt);
% else
%     diplay('Error!')
% end

%% Trajectory Test 2D
% qo_x=0;qf_x=0;vo_x=10;vf_x=-10;ao_x=0;af_x=0;
% vm_x=20;am_x=5;jm_x=5;
% [Flag,Ta_x,Tv_x,Td_x,Tj1_x,Tj2_x,qt_x,vt_x,at_x,jt_x]=doubleS(qo_x,qf_x,vo_x,vf_x,ao_x,af_x,vm_x,am_x,jm_x);
% t_x=[0:0.1:Ta_x+Tv_x+Td_x]';
% 
% 
% qo_y=0;qf_y=20;vo_y=0;vf_y=0;ao_y=0;af_y=0;
% vm_y=20;am_y=5;jm_y=5;
% [Flag,Ta_y,Tv_y,Td_y,Tj1_y,Tj2_y,qt_y,vt_y,at_y,jt_y]=doubleS(qo_y,qf_y,vo_y,vf_y,ao_y,af_y,vm_y,am_y,jm_y);
% t_y=[0:0.1:Ta_y+Tv_y+Td_y]';
% 
% figure(1);
% plot(t_x,qt_x);
% figure(2);
% plot(t_y,qt_y);
% 
% Num = max(length(qt_x),length(qt_y));
% if length(qt_x)>length(qt_y)
%     vt_y = [vt_y;ones(length(qt_x)-length(qt_y),1)*vf_y];
%     qt_y = [qt_y;ones(length(qt_x)-length(qt_y),1)*qf_y];
%    
%     t_y = t_x;
%     t=t_x;
% else
%     vt_x = [vt_x;ones(length(qt_y)-length(qt_x),1)*vf_x];
%     qt_x = [qt_x;ones(length(qt_y)-length(qt_x),1)*qf_x];    
%     t_x = t_y;
%     t=t_y;
% end
% 
% figure(3);
% plot(qt_x,qt_y);
% figure(4);
% v=sqrt(vt_x.^2+vt_y.^2);
% plot(t,v);

%% Trajectory Test 1D multiple points
% qo=[30  70 90 110 130;];
% qf=[70 90 110 130 150;];
% vo=[0 10 10 10 10];
% vf=[10 10 10 10 0];
% ao=[0 0 0 0 0];
% af=[0 0 0 0 0];
% vm=20; am=5; jm=5;
% qt=cell(5,1);
% vt=cell(5,1);
% at=cell(5,1);
% jt=cell(5,1)
% 
% for k=1:5
%     [Flag(:,k),Ta(:,k),Tv(:,k),Td(:,k),Tj1(:,k),Tj2(:,k),qt{k},vt{k},at{k},jt{k}]=doubleS(qo(k),qf(k),vo(k),vf(k),ao(k),af(k),vm,am,jm);
% end
% 
% qall=cell2mat(qt);
% vall=cell2mat(vt);
% aall=cell2mat(at);
% jall=cell2mat(jt);
% 
% len=length(qall);
% t=[0:0.1:(len-1)*0.1];
% figure(1);
% plot(t,qall);
% figure(2);
% plot(t,vall);
% figure(3);
% plot(t,aall);
% figure(4);
% plot(t,jall);

%% Trajectory Test 3D multiple points
qo=[-20 30 80 50 120;
    30  70 90 115 130;
    5  -30 -5 50 60; ];
qf=[30 80 50 120 90;
    70 90 115 130 160;
    -30 -5 50 60 120;];
deltaq = (qf-qo);
ratio = bsxfun(@rdivide,deltaq,deltaq(1,:));
vo=10*ones(3,5);
vo(:,1)=0;
vo=vo.*ratio;
vf=10*ones(3,5);
vf(:,end)=0;
vf=vf.*ratio;
ao=zeros(3,5);
af=zeros(3,5);
ratio = abs(ratio);
vm=15*ones(3,5).*ratio; 
am=5*ones(3,5).*ratio; 
jm=5*ones(3,5).*ratio;
qt=cell(5,3);
vt=cell(5,3);
at=cell(5,3);
jt=cell(5,3);
for j=1:3
    for k=1:5

        [Flag,Ta,Tv,Td,Tj1,Tj2,qt{k,j},vt{k,j},at{k,j},jt{k,j}]=doubleS(qo(j,k),qf(j,k),vo(j,k),vf(j,k),ao(j,k),af(j,k),vm(j,k),am(j,k),jm(j,k));
    end
end


len1=length(cell2mat(qt(:,1)));
len2=length(cell2mat(qt(:,2)));
len3=length(cell2mat(qt(:,3)));
len = max(max(len1,len2),len3);
qall=zeros(len,3);
vall=zeros(len,3);

if len==len1
    qall(:,1)=cell2mat(qt(:,1));
    qall(:,2)=[cell2mat(qt(:,2));ones(len-len2,1)*qf(2,5)];
    qall(:,3)=[cell2mat(qt(:,3));ones(len-len3,1)*qf(3,5)];
else if len ==len2
        qall(:,2)=cell2mat(qt(:,2));
        qall(:,1)=[cell2mat(qt(:,1));ones(len-len1,1)*qf(1,5)];
        qall(:,3)=[cell2mat(qt(:,3));ones(len-len3,1)*qf(3,5)];
    else
        qall(:,3)=cell2mat(qt(:,3));
        qall(:,2)=[cell2mat(qt(:,2));ones(len-len2,1)*qf(2,5)];
        qall(:,1)=[cell2mat(qt(:,1));ones(len-len1,1)*qf(1,5)]; 
    end
end

vall(:,1)=cell2mat(vt(:,1));
vall(:,2)=cell2mat(vt(:,2));
vall(:,3)=cell2mat(vt(:,3));

t=[0:0.1:(len-1)*0.1];
figure(1);
plot3(qall(:,1),qall(:,2),qall(:,3));
grid on;
hold on;
plot3(qo(1,:),qo(2,:),qo(3,:),'r.');
hold on;
plot3(qf(1,5),qf(2,5),qf(3,5),'r.');
figure(2);
plot(t,qall(:,1));
figure(3);
plot(t,qall(:,2));
figure(4);
plot(t,qall(:,3));
figure(5);
plot(t,vall(:,1));
figure(6);
plot(t,vall(:,2));
figure(7);
plot(t,vall(:,3));
figure(8);
plot(t,sqrt(vall(:,1).^2+vall(:,2).^2+vall(:,3).^2));

%% JointViaPoint Test
JointPts = [-20 30 80 50 120 90;
            30  70 90 115 130 60;
            5  -30 -5 50 60 120; ];

V = 10;
Vm = 15;
Am = 5;
Jm = 5;

[qall,vall,aall,jall,len]=JointViaPoint(JointPts,V,Vm,Am,Jm);

t=[0:0.1:(len-1)*0.1];
figure(1);
plot3(qall(:,1),qall(:,2),qall(:,3));
grid on;
hold on;
plot3(JointPts(1,:),JointPts(2,:),JointPts(3,:),'r.');

figure(2);
plot(t,qall(:,1));
figure(3);
plot(t,qall(:,2));
figure(4);
plot(t,qall(:,3));
figure(5);
plot(t,vall(:,1));
figure(6);
plot(t,vall(:,2));
figure(7);
plot(t,vall(:,3));
% figure(8);
% plot(t,sqrt(vall(:,1).^2+vall(:,2).^2+vall(:,3).^2));
