function body_Jacobian_d6_ = body_Jacobian_d6(in1,in2,in3)
%BODY_JACOBIAN_D6
%    BODY_JACOBIAN_D6_ = BODY_JACOBIAN_D6(IN1,IN2,IN3)

%    This function was generated by the Symbolic Math Toolbox version 5.5.
%    15-Aug-2014 15:39:31

A2 = in2(:,2);
A3 = in2(:,3);
A4 = in2(:,4);
A5 = in2(:,5);
A6 = in2(:,6);
Cx6 = in3(:,6);
Cy6 = in3(:,12);
Cz6 = in3(:,18);
L1 = in1(:,1);
L2 = in1(:,2);
L3 = in1(:,3);
L4 = in1(:,4);
L5 = in1(:,5);
t2 = cos(A5);
t3 = sin(A5);
t4 = L1+L3+L4;
t5 = t2-1.0;
t6 = L2+L5;
t7 = cos(A6);
t8 = sin(A4);
t9 = sin(A6);
t10 = Cy6.*t7;
t11 = t4.*t9;
t27 = Cz6.*t9;
t12 = t10+t11-t27;
t13 = cos(A4);
t14 = sin(A3);
t15 = cos(A3);
t16 = t3.*t6;
t55 = t4.*t5;
t17 = t16-t55;
t18 = t17.*t2;
t19 = t3.*t4;
t20 = t5.*t6;
t21 = t19+t20;
t22 = Cz6.*t7;
t23 = Cy6.*t9;
t24 = t7-1.0;
t56 = t21.*t3;
t57 = t24.*t4;
t25 = t18+t22+t23-t56-t57;
t26 = t2.*t4.*t8;
t28 = t12.*t13.*t2;
t29 = t26+t28-t25.*t8;
t30 = t13-1.0;
t31 = t13.*t4.*t8;
t67 = t30.*t4.*t8;
t68 = t31-t67;
t32 = t3.*t68;
t66 = t12.*t3;
t33 = t32+t66;
t34 = t15-1.0;
t35 = L1+L3;
t36 = sin(A2);
t37 = cos(A2);
t38 = t14.*t2;
t39 = t13.*t15.*t3;
t40 = t38+t39;
t41 = t15.*t2;
t49 = t13.*t14.*t3;
t42 = t41-t49;
t43 = L1.*t36;
t44 = t37-1.0;
t45 = L2.*t44;
t46 = t43+t45;
t47 = L1.*t44;
t95 = L2.*t36;
t48 = t47-t95;
t50 = L2.*t14;
t58 = t34.*t35;
t51 = t50-t58;
t52 = t14.*t35;
t53 = L2.*t34;
t54 = t52+t53;
t59 = t15.*t51;
t112 = t14.*t54;
t113 = t112-t59;
t60 = -t113.*t2;
t61 = t13.*t25;
t62 = t12.*t2.*t8;
t63 = t15.*t54;
t64 = t14.*t51;
t65 = t63+t64;
t69 = t9.^2;
t70 = t4.*t69;
t71 = t24.*t4.*t7;
t72 = -Cz6+t70+t71;
t73 = t13.*t7;
t94 = t2.*t8.*t9;
t74 = t73-t94;
t75 = Cx6.*t9;
t76 = t2.*t21;
t77 = t17.*t3;
t78 = t76+t77;
t104 = t78.*t9;
t79 = -t104+t75;
t80 = t79.*t8;
t81 = t21.*t7;
t82 = t3.*t72;
t105 = Cx6.*t2.*t7;
t83 = -t105+t81+t82;
t84 = t13.*t83;
t85 = t3.*t4.*t8.*t9;
t86 = t80+t84+t85;
t87 = t2.*t72;
t88 = t8.^2;
t89 = t4.*t88;
t90 = t13.*t30.*t4;
t91 = t89+t90;
t92 = t7.*t91;
t93 = Cx6.*t3.*t7;
t96 = t37.*t48;
t97 = t36.*t46;
t98 = t96+t97;
t99 = t7.*t8;
t100 = t13.*t2.*t9;
t101 = t100+t99;
t102 = t37.*t46;
t148 = t36.*t48;
t103 = t102-t148;
t106 = t101.*t14;
t107 = t15.*t3.*t9;
t108 = t106+t107;
t109 = t101.*t15;
t111 = t14.*t3.*t9;
t110 = t109-t111;
t114 = t14.*(t50-t58);
t115 = t114+t63;
t116 = t101.*t115;
t117 = t8.*t83;
t118 = t2.*t9.*(t31-t67);
t119 = t4.*t7.*t9;
t127 = t24.*t4.*t9;
t120 = Cy6+t119-t127;
t121 = t13.*t9;
t122 = t2.*t7.*t8;
t123 = t121+t122;
t124 = Cx6.*t7;
t138 = t7.*t78;
t125 = t124-t138;
t126 = t125.*t8;
t128 = t120.*t3;
t129 = Cx6.*t2.*t9;
t139 = t21.*t9;
t130 = t128+t129-t139;
t131 = t13.*t130;
t132 = t3.*t4.*t7.*t8;
t133 = t126+t131+t132;
t134 = t17.*t9;
t135 = t120.*t2;
t136 = t2.*t68.*t7;
t151 = t9.*t91;
t152 = Cx6.*t3.*t9;
t137 = t134+t135+t136-t151-t152;
t140 = t8.*t9;
t142 = t13.*t2.*t7;
t141 = t140-t142;
t143 = t141.*t15;
t144 = t14.*t3.*t7;
t145 = t143+t144;
t146 = t14.*t141;
t149 = t15.*t3.*t7;
t147 = t146-t149;
t150 = t130.*t8;
t153 = t37.*t40;
t154 = t36.*t42;
t155 = t3.*t8;
t156 = t108.*t36;
t157 = t147.*t36;
t158 = t157-t145.*t37;
t159 = -t121-t122;
body_Jacobian_d6_ = reshape([t36.*(t14.*t29+t15.*t33+t3.*t51.*t8)-t37.*(t15.*t29-t14.*t33+t3.*t54.*t8)-t3.*t46.*t8,t36.*(t14.*t86+t51.*t74-t15.*(t118+t87+t92+t93-t17.*t7))-t46.*t74-t37.*(t15.*t86+t54.*t74+t14.*(t87+t92+t93-t17.*t7+t2.*t68.*t9)),-t36.*(-t133.*t14+t137.*t15+t123.*t51)-t37.*(t137.*t14+t133.*t15-t123.*t54)+t123.*t46,-t153-t154,-t156+t110.*t37,t158,t60+t61+t62-t103.*t40-t42.*t98+L1.*(t36.*t40-t37.*t42)-L2.*(t153+t154)-t2.*t30.*t4-t13.*t3.*t65,t116+t117+t103.*t110-t13.*t79-t108.*t98-L1.*(t110.*t36+t108.*t37)-L2.*(t156-t110.*t37)-t113.*t3.*t9-t3.*t30.*t4.*t9,t150+t147.*(t96+t97)+L2.*t158-t103.*t145-t125.*t13-t115.*t141+L1.*(t145.*t36+t147.*t37)-t113.*t3.*t7-t3.*t30.*t4.*t7,t155,t74,t159,t60+t61+t62-L2.*t40-t35.*t42-t2.*t30.*t4-t13.*t3.*t65,t116+t117+L2.*t110-t108.*t35-t13.*t79-t113.*t3.*t9-t3.*t30.*t4.*t9,t150-L2.*t145-t125.*t13-t115.*t141+t147.*t35-t113.*t3.*t7-t3.*t30.*t4.*t7,t155,t74,t159,-t32-t66+t3.*t4.*t8,t118+t87+t92+t93-t17.*t7+t4.*t74,t134+t135-t151-t152-t123.*t4+t2.*t7.*(t31-t67),t2,t3.*t9,t3.*t7,-t16+t18+t22+t23-t56-t57-t2.*t4,t104-t75-t3.*t4.*t9+t2.*t6.*t9,-t124+t138-t3.*t4.*t7+t2.*t6.*t7,0.0,t7,-t9,0.0,-Cz6+t70+t71+t4.*t7,Cy6-t11+t119-t127,1.0,0.0,0.0],[6, 6]);
