function body_Jacobian_d12 = body_Jacobian_d12(in1,in2)
%BODY_JACOBIAN_D12
%    BODY_JACOBIAN_D12 = BODY_JACOBIAN_D12(IN1,IN2)

%    This function was generated by the Symbolic Math Toolbox version 5.5.
%    30-Apr-2013 23:41:52

L2 = in1(:,2);
body_Jacobian_d12 = reshape([0.0,L2,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0],[6, 6]);
