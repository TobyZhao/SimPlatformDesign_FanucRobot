%%%%%%%%%%%2014/12/04 Equivalent Inertial to Motor%%%%%%%%%
syms Ld1 Ld2 Ld3 Ld4 Ld5 Ld6 Ld7 Ld8
syms th1 th2 th3 th4 th5 th6

DH=[Ld1     Ld2     0           Ld5     Ld7         0           Ld8;
    0       0       -pi/2       0       pi          pi          0;
    0       Ld3     Ld4         Ld6     0           0           0;
    0       -pi/2   0           -pi/2   -pi/2       -pi/2       0;];


%%%%%Link Center relative to Spatial Frame%%%%%%%%
syms Cx1 Cx2 Cx3 Cx4 Cx5 Cx6
syms Cy1 Cy2 Cy3 Cy4 Cy5 Cy6
syms Cz1 Cz2 Cz3 Cz4 Cz5 Cz6

Pc1=[Cx1;Cy1;Cz1;1];
Pc2=[Cx2;Cy2;Cz2;1];
Pc3=[Cx3;Cy3;Cz3;1];
Pc4=[Cx4;Cy4;Cz4;1];
Pc5=[Cx5;Cy5;Cz5;1];
Pc6=[Cx6;Cy6;Cz6;1];

ez = [0;0;1];
ex = [1;0;0];
eo = [0;0;0];

g01_0= expWre([eo;ez],DH(2,1))*expWre([ez;eo],DH(1,1))*expWre([eo;ex],DH(4,1))*expWre([ex;eo],DH(3,1));
g12_0= expWre([eo;ez],DH(2,2))*expWre([ez;eo],DH(1,2))*expWre([eo;ex],DH(4,2))*expWre([ex;eo],DH(3,2));
g23_0= expWre([eo;ez],DH(2,3))*expWre([ez;eo],DH(1,3))*expWre([eo;ex],DH(4,3))*expWre([ex;eo],DH(3,3));
g34_0= expWre([eo;ez],DH(2,4))*expWre([ez;eo],DH(1,4))*expWre([eo;ex],DH(4,4))*expWre([ex;eo],DH(3,4));
g45_0= expWre([eo;ez],DH(2,5))*expWre([ez;eo],DH(1,5))*expWre([eo;ex],DH(4,5))*expWre([ex;eo],DH(3,5));
g56_0= expWre([eo;ez],DH(2,6))*expWre([ez;eo],DH(1,6))*expWre([eo;ex],DH(4,6))*expWre([ex;eo],DH(3,6));
g67_0= expWre([eo;ez],DH(2,7))*expWre([ez;eo],DH(1,7))*expWre([eo;ex],DH(4,7))*expWre([ex;eo],DH(3,7));

syms Ma1 Ma2 Ma3 Ma4 Ma5 Ma6 
%%%%%Inertial relative to center frame%%%%%%%%%%%%
%%%%%Orientation of center frame is the same with spatial frame%%%%%%%%% 
syms I1_11 I1_12 I1_13 I1_21 I1_22 I1_23 I1_31 I1_32 I1_33 
syms I2_11 I2_12 I2_13 I2_21 I2_22 I2_23 I2_31 I2_32 I2_33 
syms I3_11 I3_12 I3_13 I3_21 I3_22 I3_23 I3_31 I3_32 I3_33 
syms I4_11 I4_12 I4_13 I4_21 I4_22 I4_23 I4_31 I4_32 I4_33 
syms I5_11 I5_12 I5_13 I5_21 I5_22 I5_23 I5_31 I5_32 I5_33 
syms I6_11 I6_12 I6_13 I6_21 I6_22 I6_23 I6_31 I6_32 I6_33 

I1=[I1_11 I1_12  I1_13;
    I1_21 I1_22  I1_23;
    I1_31 I1_32  I1_33;];

I2=[I2_11 I2_12  I2_13;
    I2_21 I2_22  I2_23;
    I2_31 I2_32  I2_33;];

I3=[I3_11 I3_12  I3_13;
    I3_21 I3_22  I3_23;
    I3_31 I3_32  I3_33;];

I4=[I4_11 I4_12  I4_13;
    I4_21 I4_22  I4_23;
    I4_31 I4_32  I4_33;];

I5=[I5_11 I5_12  I5_13;
    I5_21 I5_22  I5_23;
    I5_31 I5_32  I5_33;];

I6=[I6_11 I6_12  I6_13;
    I6_21 I6_22  I6_23;
    I6_31 I6_32  I6_33;];

g=g01_0;
r1 = g\Pc1;
r1 = r1(1:3);
R = g(1:3,1:3);
I1 = R.'*I1*R;
g=g*g12_0;
r2 = g\Pc2;
r2 = r2(1:3);
R = g(1:3,1:3);
I2 = R.'*I2*R;
g=g*g23_0;
r3 = g\Pc3;
r3 = r3(1:3);
R = g(1:3,1:3);
I3 = R.'*I3*R;
g=g*g34_0;
r4 = g\Pc4;
r4 = r4(1:3);
R = g(1:3,1:3);
I4 = R.'*I4*R;
g=g*g45_0;
r5 = g\Pc5;
r5 = r5(1:3);
R = g(1:3,1:3);
I5 = R.'*I5*R;
g=g*g56_0;
r6 = g\Pc6;
r6 = r6(1:3);
R = g(1:3,1:3);
I6 = R.'*I6*R;

%%%%%%%%%%%%Initial Generalized Inertia Matrix Relative to Joint Frame%%%%%%%%%
M1  = [ Ma1*eye(3),      -Ma1*skew(r1);
        Ma1*skew(r1),    I1 - Ma1*skew(r1)*skew(r1)];

M2  = [ Ma2*eye(3),      -Ma2*skew(r2);
        Ma2*skew(r2),    I2 - Ma2*skew(r2)*skew(r2)];

M3  = [ Ma3*eye(3),      -Ma3*skew(r3);
        Ma3*skew(r3),    I3 - Ma3*skew(r3)*skew(r3)]; 

M4  = [ Ma4*eye(3),      -Ma4*skew(r4);
        Ma4*skew(r4),    I4 - Ma4*skew(r4)*skew(r4)];    

M5  = [ Ma5*eye(3),      -Ma5*skew(r5);
        Ma5*skew(r5),    I5 - Ma5*skew(r5)*skew(r5)];
    
M6  = [ Ma6*eye(3),      -Ma6*skew(r6);
        Ma6*skew(r6),    I6 - Ma6*skew(r6)*skew(r6)];    

%%%%%%%%%%%%%Consider Rotation of Each Joint%%%%%%%%%%%%%    
DH=[Ld1     Ld2     0           Ld5     Ld7         0           Ld8;
    0       th1     th2-pi/2    th3     th4+pi      th5+pi      th6;
    0       Ld3     Ld4         Ld6     0           0           0;
    0       -pi/2   0           -pi/2   -pi/2       -pi/2       0;];

g01= expWre([eo;ez],DH(2,1))*expWre([ez;eo],DH(1,1))*expWre([eo;ex],DH(4,1))*expWre([ex;eo],DH(3,1));
g12= expWre([eo;ez],DH(2,2))*expWre([ez;eo],DH(1,2))*expWre([eo;ex],DH(4,2))*expWre([ex;eo],DH(3,2));
g23= expWre([eo;ez],DH(2,3))*expWre([ez;eo],DH(1,3))*expWre([eo;ex],DH(4,3))*expWre([ex;eo],DH(3,3));
g34= expWre([eo;ez],DH(2,4))*expWre([ez;eo],DH(1,4))*expWre([eo;ex],DH(4,4))*expWre([ex;eo],DH(3,4));
g45= expWre([eo;ez],DH(2,5))*expWre([ez;eo],DH(1,5))*expWre([eo;ex],DH(4,5))*expWre([ex;eo],DH(3,5));
g56= expWre([eo;ez],DH(2,6))*expWre([ez;eo],DH(1,6))*expWre([eo;ex],DH(4,6))*expWre([ex;eo],DH(3,6));
g67= expWre([eo;ez],DH(2,7))*expWre([ez;eo],DH(1,7))*expWre([eo;ex],DH(4,7))*expWre([ex;eo],DH(3,7));

I4=eye(4);
%%%%%%%Motor 6%%%%%%%%%%
g66i=[expRot(ez,th6) zeros(3,1);zeros(1,3) 1];
adig=AdjointInv(g66i);
M6r = adig.'*M6*adig;
Iz6 = M6r(6,6);

%%%%%%%Motor 5%%%%%%%%%
g56i=g56*g66i;
g55i=[expRot(ez,th5) zeros(3,1);zeros(1,3) 1];
adig=AdjointInv(g56i);
M5r = adig.'*M6*adig;
adig=AdjointInv(g55i);
M5r = M5r + adig.'*M5*adig;
Iz5 = M5r(6,6);

%%%%%%%Motor 4%%%%%%%%
g46i=g45*g56i;
g45i=g45*g55i;
g44i=[expRot(ez,th4) zeros(3,1);zeros(1,3) 1];
adig=AdjointInv(g46i);
M4r=adig.'*M6*adig;
adig=AdjointInv(g45i);
M4r= M4r + adig.'*M5*adig;
adig=AdjointInv(g44i);
M4r= M4r + adig.'*M4*adig;
Iz4= M4r(6,6);

%%%%%%%Motor 3%%%%%%%%
g36i=g34*g46i;
g35i=g34*g45i;
g34i=g34*g44i;
g33i=[expRot(ez,th3) zeros(3,1);zeros(1,3) 1];
adig=AdjointInv(g36i);
M3r = adig.'*M6*adig;
adig=AdjointInv(g35i);
M3r = M3r + adig.'*M5*adig;
adig=AdjointInv(g34i);
M3r = M3r + adig.'*M4*adig;
adig=AdjointInv(g33i);
M3r = M3r + adig.'*M3*adig;
Iz3=M3r(6,6);

%%%%%%%Motor 2%%%%%%%%
g26i=g23*g36i;
g25i=g23*g35i;
g24i=g23*g34i;
g23i=g23*g33i;
g22i=[expRot(ez,th2) zeros(3,1);zeros(1,3) 1];
adig=AdjointInv(g26i);
M2r=adig.'*M6*adig;
adig=AdjointInv(g25i);
M2r = M2r + adig.'*M5*adig;
adig=AdjointInv(g24i);
M2r = M2r + adig.'*M4*adig;
adig=AdjointInv(g23i);
M2r = M2r + adig.'*M3*adig;
adig=AdjointInv(g22i);
M2r = M2r + adig.'*M2*adig;
Iz2 = M2r(6,6);

%%%%%%%%%Motor 1%%%%%%
g16i=g12*g26i;
g15i=g12*g25i;
g14i=g12*g24i;
g13i=g12*g23i;
g12i=g12*g22i;
g11i=[expRot(ez,th1) zeros(3,1);zeros(1,3) 1];
adig=AdjointInv(g16i);
M1r = adig.'*M6*adig;
adig=AdjointInv(g15i);
M1r = M1r + adig.'*M5*adig;
adig=AdjointInv(g14i);
M1r = M1r + adig.'*M4*adig;
adig=AdjointInv(g13i);
M1r = M1r + adig.'*M3*adig;
adig=AdjointInv(g12i);
M1r = M1r + adig.'*M2*adig;
adig=AdjointInv(g11i);
M1r = M1r + adig.'*M1*adig;
Iz1 = M1r(6,6);

%%%%%%%Generate Funciton File%%%%%%%%%%%%%
theta=[th1 th2 th3 th4 th5 th6];
L=[Ld1 Ld2 Ld3 Ld4 Ld5 Ld6 Ld7 Ld8];
Ma=[Ma1 Ma2 Ma3 Ma4 Ma5 Ma6];
Ie1 = [I1_11 I1_21 I1_31 I1_12 I1_22 I1_32 I1_13 I1_23 I1_33];
Ie2 = [I2_11 I2_21 I2_31 I2_12 I2_22 I2_32 I2_13 I2_23 I2_33];
Ie3 = [I3_11 I3_21 I3_31 I3_12 I3_22 I3_32 I3_13 I3_23 I3_33];
Ie4 = [I4_11 I4_21 I4_31 I4_12 I4_22 I4_32 I4_13 I4_23 I4_33];
Ie5 = [I5_11 I5_21 I5_31 I5_12 I5_22 I5_32 I5_13 I5_23 I5_33];
Ie6 = [I6_11 I6_21 I6_31 I6_12 I6_22 I6_32 I6_13 I6_23 I6_33];
Cen = [Cx1 Cx2 Cx3 Cx4 Cx5 Cx6 Cy1 Cy2 Cy3 Cy4 Cy5 Cy6 Cz1 Cz2 Cz3 Cz4 Cz5 Cz6];

% matlabFunction(Iz1,'file','MotorIz1','vars',{theta,L,Ma,Ie1,Ie2,Ie3,Ie4,Ie5,Ie6,Cen});
% matlabFunction(Iz2,'file','MotorIz2','vars',{theta,L,Ma,Ie1,Ie2,Ie3,Ie4,Ie5,Ie6,Cen});
% matlabFunction(Iz3,'file','MotorIz3','vars',{theta,L,Ma,Ie1,Ie2,Ie3,Ie4,Ie5,Ie6,Cen});
% matlabFunction(Iz4,'file','MotorIz4','vars',{theta,L,Ma,Ie1,Ie2,Ie3,Ie4,Ie5,Ie6,Cen});
% matlabFunction(Iz5,'file','MotorIz5','vars',{theta,L,Ma,Ie1,Ie2,Ie3,Ie4,Ie5,Ie6,Cen});
% matlabFunction(Iz6,'file','MotorIz6','vars',{theta,L,Ma,Ie1,Ie2,Ie3,Ie4,Ie5,Ie6,Cen});

matlabFunction(M1r,'file','MotorM1','vars',{theta,L,Ma,Ie1,Ie2,Ie3,Ie4,Ie5,Ie6,Cen});
disp('MotorM1 Finished!');
matlabFunction(M2r,'file','MotorM2','vars',{theta,L,Ma,Ie1,Ie2,Ie3,Ie4,Ie5,Ie6,Cen});
disp('MotorM2 Finished!');
matlabFunction(M3r,'file','MotorM3','vars',{theta,L,Ma,Ie1,Ie2,Ie3,Ie4,Ie5,Ie6,Cen});
disp('MotorM3 Finished!');
matlabFunction(M4r,'file','MotorM4','vars',{theta,L,Ma,Ie1,Ie2,Ie3,Ie4,Ie5,Ie6,Cen});
disp('MotorM4 Finished!');
matlabFunction(M5r,'file','MotorM5','vars',{theta,L,Ma,Ie1,Ie2,Ie3,Ie4,Ie5,Ie6,Cen});
disp('MotorM5 Finished!');
matlabFunction(M6r,'file','MotorM6','vars',{theta,L,Ma,Ie1,Ie2,Ie3,Ie4,Ie5,Ie6,Cen});
disp('MotorM6 Finished!');



