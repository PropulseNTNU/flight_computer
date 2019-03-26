function [est_h , est_v] = Kalman_kopi(barometer , acc, time, lengde, init_h, init_v, dt)

C_d = [1 0];

E_d = [0.01 0; 0 0.01];
Q = [90 0; 0 10^(3)];
R = 1;%6.066603283607384e-07/0.1;
I = eye(2);

P_k_bar=[1 0; 0 0.1];
x_hat_bar=[init_h init_v]';

est_h=[];
est_v=[];
for i=1:lengde
    A_d =[1 dt(i); 0 1];
    B_d = [0 dt(i)];
    % Compute  Kalman  gain
    K_k = P_k_bar*C_d'*inv(C_d*P_k_bar*C_d'+R);
    % Update  estimate  with  measurement
    x_hat = x_hat_bar + K_k*(barometer(i) -C_d*x_hat_bar);
    %est_h=append(est_h, x_hat(1));
    est_h=[est_h, x_hat(1)];
    %est_v=append(est_v, x_hat(2));
    est_v=[est_v, x_hat(2)];
    
    % Compute  error  covariance  for  updated  estimate
    P_k = (I - K_k*C_d)*P_k_bar*(I-K_k*C_d)' + K_k*R*K_k';
    % Project  ahead
    x_hat_bar = A_d * x_hat + B_d * (acc(i));
    P_k_bar = A_d * P_k * A_d'+E_d * Q * E_d';
    
end