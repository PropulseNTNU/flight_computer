clear all; close all;
filename = 'DATAFILE.TXT';
delimiterIn = ',';
headerlinesIn = 0;
data = importdata(filename,delimiterIn,headerlinesIn);

%%TODO: IMU_temp = IMU_YAW
timestamp = data(:,1)-data(1,1);
time_est=timestamp(25545:25673)/1000; 
BME_temp = data(:,2);
IMU_temp = data(:,3);
BME_pressure = data(:,4);
BME_altitude = data(:,5);
IMU_acc_x = data(:,6);
IMU_acc_y = data(:,7);
IMU_acc_z = data(:,8);
IMU_roll = data(:,9);
IMU_pitch = data(:,10);
IMU_yaw = data(:,11);
IMU_mag_x = data(:,12);
IMU_mag_y = data(:,13);
IMU_mag_z = data(:,14);
IMU_roll_rate = data(:,15);
IMU_pitch_rate = data(:,16);
IMU_yaw_rate = data(:,17);
IMU_g_accel_x = data(:,18);
IMU_g_accel_y = data(:,19);
IMU_g_accel_z = data(:,20);
IMU_lin_accel_x = data(:,21);
IMU_lin_accel_y = data(:,22);
IMU_lin_accel_z = data(:,23);
IMU_quaternion_x = data(:,24);
IMU_quaternion_y = data(:,25);
IMU_quaternion_z = data(:,26);
IMU_quaternion_w = data(:,27);
states = data(:,28);
%--------------------------------------------------------------------------------
h_init=93.46;
a_init=-1.34;
v_init=50.0;
lengde= (25673-25545);
%Kalman_kopi;
dt=[];
est_v2=[];
height=BME_altitude(25545:25673);
time=0;
a=0;
for i =1:lengde
    %dt=append(dt,(time(i+1)-time(i)));
    time=(time_est(i+1)-time_est(i));
    %dif_h=height(i+1)-height(i);
    if i < lengde-2
        est_v2=[est_v2, (height(i+3)-height(i))/(time_est(i+3)-time_est(i))];
        a=a+1;
    elseif i < size(lengde)-1
        est_v2=[est_v2, (height(i+2)-height(i))/(time_est(i+2)-time_est(i))];
    else
        est_v2=[est_v2, (height(i)-height(i+1))/(time_est(i+1)-time_est(i))];
    end
            
    dt=[dt,time];
    %est_v2=[est_v2, height];
    
end
[est_h, est_v]= Kalman_kopi(height,IMU_lin_accel_y(25545:25673), time_est, lengde , h_init, v_init, dt);
%--------------------------------------------------------------------------------





figure(1);
%plot Acceleration
%subplot(5,1,1);
plot(timestamp/1000, IMU_lin_accel_x,'r');
hold on;
plot(timestamp/1000, IMU_lin_accel_y,'g');
plot(timestamp/1000, IMU_lin_accel_z,'b');
xlabel('seconds [s]');
ylabel('acceleration [m/s^2]');
legend('Lin\_Accel_x','Lin\_Accel_y','Lin\_Accel_z');
xlim([1430,1520]);
title('Accelerations');

%plot ROLL/PITCH/YAW
%subplot(5,1,2);
figure(2)
plot(timestamp/1000, IMU_roll,'r');
hold on;
plot(timestamp/1000, IMU_pitch,'g');
plot(timestamp/1000, IMU_yaw,'b');
xlabel('seconds [s]');
ylabel('degrees [°]');
xlim([1440,1450]);
legend('Roll_z','Pitch_y','Yaw_x');

title('Euler angles in body frame');

%plot altitude
% subplot(5,1,3);
figure(3);
plot(timestamp(25545:25672)/1000, BME_altitude(25545:25672));
hold on;
plot(timestamp(25545:25672)/1000, est_h);
xlabel('seconds [s]');
ylabel('height [m]');
xlim([1443,1450.5]);
ylim([80,315]);
legend('Altitude', 'Kalman-estimat');
title('Altitude');

%plot states
subplot(5,1,4);
plot(timestamp/1000, states);
xlabel('seconds [s]');
ylabel('state');
xlim([0,20]);
l = legend('states [1=armed,2=burnout,3=airbrakes,4=apogee,5=drogue,6=chute,7=landed]');
l.FontSize = 16;
title('State transitions');


%plot temperature
subplot(5,1,5);
plot(timestamp/1000, BME_temp);
hold on;
plot(timestamp(25545:25672)/1000, est_v);
legend('h_derivert', 'kalman-estimat');
ylim([0,65]);
xlim([1443,1451]);
% %plot states
% subplot(5,1,4);
% plot(timestamp/1000, states);
% xlabel('seconds [s]');
% ylabel('state');
% xlim([0,20]);
% legend('states');
% title('State transitions');
% 
% 
% %plot temperature
% subplot(5,1,5);
% plot(timestamp/1000, BME_temp);
% hold on;
% plot(timestamp/1000, IMU_temp);
% xlabel('seconds [s]');
% ylabel('deg celsius [°/C]');
% legend('BME Temperature','IMU Temperature');
% xlim([1430,1520]);
% title('Temperature');

%Plot states
