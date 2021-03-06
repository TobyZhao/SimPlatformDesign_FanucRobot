%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%@Copyright(c),Googol Shenzhen Tech. Ltd
%@File Name: EfDynCAD.m
%@Author: Dai Dan
%@Version: 1.0
%@Date: 09/03/2014
%
%@Description: To calculate dynamic parameters based CAD model
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [Param_a,rParam_a]=EfDynCAD()

%%%%DH parameters, unit:m %%%%%%%%%
DH=[0       0       0       504;
        -pi/2   170     -pi/2    0;
        0       780     0       0;
        -pi/2   140    0       760;
        pi/2    0       0       0;
        -pi/2   0       0       0;
        0       0       0       125]';
DH(2,:) = DH(2,:)/1000;
DH(4,:) = DH(4,:)/1000;
Ld=[504 170 780 140 760]/1000;

ez = [0;0;1];
ex = [1;0;0];
eo = [0;0;0];
g01_0 = expWre([ex;eo],DH(2,1))*expWre([eo;ex],DH(1,1))*expWre([ez;eo],DH(4,1))*expWre([eo;ez],DH(3,1));
g12_0 = expWre([ex;eo],DH(2,2))*expWre([eo;ex],DH(1,2))*expWre([ez;eo],DH(4,2))*expWre([eo;ez],DH(3,2));
g23_0 = expWre([ex;eo],DH(2,3))*expWre([eo;ex],DH(1,3))*expWre([ez;eo],DH(4,3))*expWre([eo;ez],DH(3,3));
g34_0 = expWre([ex;eo],DH(2,4))*expWre([eo;ex],DH(1,4))*expWre([ez;eo],DH(4,4))*expWre([eo;ez],DH(3,4));
g45_0 = expWre([ex;eo],DH(2,5))*expWre([eo;ex],DH(1,5))*expWre([ez;eo],DH(4,5))*expWre([eo;ez],DH(3,5));
g56_0 = expWre([ex;eo],DH(2,6))*expWre([eo;ex],DH(1,6))*expWre([ez;eo],DH(4,6))*expWre([eo;ez],DH(3,6));


%%%%Actual Dynamic Parameters%%%%%%%%%%%%%
%%%%%% Mass: kg  Inertia: kg/m^2  Center: m
ma1 = 77.75;
in1 = [0.54  -0.01 0.23;
       -0.01 0.79  -0.02;
       0.23  -0.02 0.62];
cen1 = [0.1 0.04 0.454];


ma2 = 32.31;
in2 = [0.1    0.01       -0.02;
       0.01   1.73       0;
       -0.02    0       1.75];
cen2 = [0.17 0 0.974];


ma3 = 18.61;
in3 = [0.16   0.05   -0.02;
       0.05   0.21    -0.01;
       -0.02  -0.01   0.25];
cen3 = [0.28 0.13 1.404];


ma4 = 15.65;
in4 = [0.5   0     0;
       0     0.47  0;
       0     0     0.09];
cen4 = [0.7 0 1.424];



ma5 = 3.32;
in5 = [0.01    0       0;
       0       0.01    0;
       0       0       0.01];
cen5 = [0.94  0.01 1.424];

ma6 = 0.6;
in6 = [0.0012   0        0;
        0       0.0007   0;
        0       0        0.0007];
cen6 = [1.045 0 1.424];

%%%%%%%%%%%%%
R_x=[1 0 0;
    0  0 -1;
    0 1  0];
R_y=[0 0 1;
    0 1 0;
    -1 0 0];
R_z=[0 -1 0;
     1 0 0;
     0 0 1];
 Rz = [-1 0 0;
       0 -1 0;
       0 0 1];
in2=(R_x*R_z)*in2*(R_x*R_z)';
in3=(R_x*R_z)*in3*(R_x*R_z)';
in4=(R_y*Rz)*in4*(R_y*Rz)';
in5=(R_x*R_y)*in5*(R_x*R_y)';
in6=(R_y*Rz)*in6*(R_y*Rz)';

%%%%%%%%%%%%%%%%%%%%%%%%%%%
Ma = [ma1 ma2 ma3 ma4 ma5 ma6]';
Ie1 = in1(:);
Ie2 = in2(:);
Ie3 = in3(:);
Ie4 = in4(:);
Ie5 = in5(:);
Ie6 = in6(:);

Cen = [cen1,cen2,cen3,cen4,cen5,cen6]';
Ie = [Ie1;Ie2;Ie3;Ie4;Ie5;Ie6];

% %% calculate ri: ith link mass center offset relative to ith joint frame,i=1,2,3,4,5,6
m1  = Ma(1);
I1  = reshape(Ie(1:9),3,3);
m2  = Ma(2);
I2  = reshape(Ie(10:18),3,3);
m3  = Ma(3);
I3  = reshape(Ie(19:27),3,3);
m4  = Ma(4);
I4  = reshape(Ie(28:36),3,3);
m5  = Ma(5);
I5  = reshape(Ie(37:45),3,3);
m6  = Ma(6);
I6  = reshape(Ie(46:54),3,3);

g=g01_0;
r1 = g\[Cen(1:3);1];
r1 = r1(1:3);
g=g*g12_0;
r2 = g\[Cen(4:6);1];
r2 = r2(1:3);
R = g(1:3,1:3);
I2 = R'*I2*R;
g=g*g23_0;
r3 = g\[Cen(7:9);1];
r3 = r3(1:3);
R = g(1:3,1:3);
I3 = R'*I3*R;
g=g*g34_0;
r4 = g\[Cen(10:12);1];
r4 = r4(1:3);
R = g(1:3,1:3);
I4 = R'*I4*R;
g=g*g45_0;
r5 = g\[Cen(13:15);1];
r5 = r5(1:3);
R = g(1:3,1:3);
I5 = R'*I5*R;
g=g*g56_0;
r6 = g\[Cen(16:18);1];
r6 = r6(1:3);
R = g(1:3,1:3);
I6 = R'*I6*R;

% %% calculate momentt of inertia in Ci,i=1,2,3,4,5,6
M1  = [ m1*eye(3),      -m1*hat(r1);
        m1*hat(r1),    I1 - m1*hat(r1)*hat(r1)];


M2  = [ m2*eye(3),      -m2*hat(r2);
        m2*hat(r2),    I2 - m2*hat(r2)*hat(r2)];

M3  = [ m3*eye(3),      -m3*hat(r3);
        m3*hat(r3),    I3 - m3*hat(r3)*hat(r3)];
    

M4  = [ m4*eye(3),      -m4*hat(r4);
        m4*hat(r4),    I4 - m4*hat(r4)*hat(r4)];
    

M5  = [ m5*eye(3),      -m5*hat(r5);
        m5*hat(r5),    I5 - m5*hat(r5)*hat(r5)];
    

M6  = [ m6*eye(3),      -m6*hat(r6);
        m6*hat(r6),    I6 - m6*hat(r6)*hat(r6)];    

%%%%%Acutual Dynamic Parameters for Euler Equation%%%%%%%%%%%%%%%%%%%%%    
Param_a =[M1(1,1);M1(2,6);-M1(1,6);M1(1,5);M1(4,4);M1(5,5);M1(6,6);M1(4,5);M1(4,6);M1(5,6);
         M2(1,1);M2(2,6);-M2(1,6);M2(1,5);M2(4,4);M2(5,5);M2(6,6);M2(4,5);M2(4,6);M2(5,6);
         M3(1,1);M3(2,6);-M3(1,6);M3(1,5);M3(4,4);M3(5,5);M3(6,6);M3(4,5);M3(4,6);M3(5,6);
         M4(1,1);M4(2,6);-M4(1,6);M4(1,5);M4(4,4);M4(5,5);M4(6,6);M4(4,5);M4(4,6);M4(5,6);
         M5(1,1);M5(2,6);-M5(1,6);M5(1,5);M5(4,4);M5(5,5);M5(6,6);M5(4,5);M5(4,6);M5(5,6);
         M6(1,1);M6(2,6);-M6(1,6);M6(1,5);M6(4,4);M6(5,5);M6(6,6);M6(4,5);M6(4,6);M6(5,6)];
     
B=EulerBasis(Ld);
rParam_a=B*Param_a;

