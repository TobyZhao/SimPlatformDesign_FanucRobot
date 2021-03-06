function body_Jacobian_d5_ = body_Jacobian_d5(in1,in2,in3)
%BODY_JACOBIAN_D5
%    BODY_JACOBIAN_D5_ = BODY_JACOBIAN_D5(IN1,IN2,IN3)

%    This function was generated by the Symbolic Math Toolbox version 5.5.
%    15-Aug-2014 15:39:33

A2 = in2(:,2);
A3 = in2(:,3);
A4 = in2(:,4);
A5 = in2(:,5);
Cx5 = in3(:,5);
Cy5 = in3(:,11);
Cz5 = in3(:,17);
L1 = in1(:,1);
L2 = in1(:,2);
L3 = in1(:,3);
L4 = in1(:,4);
L5 = in1(:,5);
t161 = cos(A5);
t162 = sin(A5);
t163 = L1+L3+L4;
t164 = t161-1.0;
t165 = L2+L5;
t166 = sin(A4);
t167 = cos(A4);
t168 = sin(A3);
t169 = cos(A3);
t170 = t162.*t165;
t205 = t163.*t164;
t171 = t170-t205;
t172 = t161.*t171;
t173 = t162.*t163;
t174 = t164.*t165;
t175 = t173+t174;
t206 = t162.*t175;
t176 = Cz5+t172-t206;
t177 = Cy5.*t161.*t167;
t178 = t161.*t163.*t166;
t179 = t177+t178-t166.*t176;
t180 = t167-1.0;
t181 = t163.*t166.*t167;
t216 = t163.*t166.*t180;
t217 = t181-t216;
t182 = t162.*t217;
t215 = Cy5.*t162;
t183 = t182+t215;
t184 = t169-1.0;
t185 = L1+L3;
t186 = sin(A2);
t187 = cos(A2);
t188 = t161.*t168;
t189 = t162.*t167.*t169;
t190 = t188+t189;
t191 = t161.*t169;
t199 = t162.*t167.*t168;
t192 = t191-t199;
t193 = L1.*t186;
t194 = t187-1.0;
t195 = L2.*t194;
t196 = t193+t195;
t197 = L1.*t194;
t227 = L2.*t186;
t198 = t197-t227;
t200 = L2.*t168;
t207 = t184.*t185;
t201 = t200-t207;
t202 = t168.*t185;
t203 = L2.*t184;
t204 = t202+t203;
t208 = t169.*t201;
t253 = t168.*t204;
t209 = t161.*(t208-t253);
t210 = t167.*t176;
t211 = t169.*t204;
t212 = t168.*t201;
t213 = t211+t212;
t214 = Cy5.*t161.*t166;
t218 = Cx5.*t162;
t219 = t166.^2;
t220 = t163.*t219;
t221 = t163.*t167.*t180;
t236 = Cz5.*t161;
t222 = -t170+t205+t218+t220+t221-t236;
t224 = Cx5.*t161;
t225 = Cz5.*t162;
t223 = t173+t174-t224-t225;
t226 = t187.*t196;
t251 = t186.*t198;
t228 = t226-t251;
t229 = t187.*t198;
t230 = t186.*t196;
t231 = t229+t230;
t232 = t168.*(t200-t207);
t233 = t211+t232;
t234 = t166.*t233;
t235 = t166.*(t173+t174-t224-t225);
t237 = t162.*t163.*t166;
t238 = Cy5.*t161;
t239 = t161.*t217;
t240 = t238+t239;
t241 = t161.*t175;
t242 = t162.*t171;
t243 = -Cx5+t241+t242;
t244 = Cy5.*t162.*t167;
t245 = t237+t244-t166.*t243;
t246 = t162.*t168;
t252 = t161.*t167.*t169;
t247 = t246-t252;
t248 = t162.*t169;
t249 = t161.*t167.*t168;
t250 = t248+t249;
t254 = t167.*t243;
t255 = t162.*(t208-t253);
t256 = Cy5.*t162.*t166;
t257 = t161.*t167.*t233;
t258 = t187.*t190;
t259 = t186.*t192;
t260 = t162.*t166;
t261 = t166.*t168.*t186;
t262 = t187.*t247;
t263 = t186.*t250;
body_Jacobian_d5_ = reshape([t186.*(t168.*t179+t169.*t183+t162.*t166.*t201)-t187.*(t169.*t179-t168.*t183+t162.*t166.*t204)-t162.*t166.*t196,-t167.*t196+t186.*(t167.*t201-t169.*t222+t167.*t168.*t223)-t187.*(t167.*t204+t168.*t222+t167.*t169.*t223),-t186.*(t169.*t240-t168.*t245+t161.*t166.*t201)-t187.*(t168.*t240+t169.*t245-t161.*t166.*t204)+t161.*t166.*t196,-t258-t259,-t261+t166.*t169.*t187,-t262-t263,t209+t210+t214-t190.*t228-t192.*t231+L1.*(t186.*t190-t187.*t192)-L2.*(t258+t259)-t161.*t163.*t180-t162.*t167.*t213,t234+t235-L2.*(t261-t166.*t169.*t187)-L1.*(t166.*t168.*t187+t166.*t169.*t186)+t166.*t169.*t228-t166.*t168.*t231,t254+t255+t256+t257-t228.*t247-t231.*t250+L1.*(t186.*t247-t187.*t250)-L2.*(t262+t263)-t162.*t163.*t180,t260,t167,-t161.*t166,t209+t210+t214-L2.*t190-t185.*t192-t161.*t163.*t180-t162.*t167.*t213,t234+t235+L2.*t166.*t169-t166.*t168.*t185,t254+t255+t256+t257-L2.*t247-t185.*t250-t162.*t163.*t180,t260,t167,-t161.*t166,-t182-t215+t237,-t170+t205+t218+t220+t221-t236+t163.*t167,-t178+t238+t161.*(t181-t216),t161,0.0,t162,Cz5-t170+t172-t206-t161.*t163,0.0,-Cx5-t173+t241+t242+t161.*t165,0.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0],[6, 6]);
