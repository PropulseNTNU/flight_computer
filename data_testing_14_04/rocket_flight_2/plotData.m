filename = 'DATAFILE.TXT';
delimiterIn = ',';
headerlinesIn = 0;
data = importdata(filename,delimiterIn,headerlinesIn);

startInterval = 1440;
endInterval = 1500;

%%TODO: IMU_temp = IMU_YAW

timestamp = data(:,1)-data(1,1);
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

figure(1);
%plot Linear Acceleration
subplot(5,1,1);
plot(timestamp/1000, IMU_lin_accel_x,'r');
hold on;
plot(timestamp/1000, IMU_lin_accel_y,'g');
plot(timestamp/1000, IMU_lin_accel_z,'b');
xlabel('seconds [s]');
ylabel('acceleration [m/s^2]');
legend('Lin\_Accel_x','Lin\_Accel_y','Lin\_Accel_z');
xlim([startInterval,endInterval]);
title('Linear Accelerations');

%plot Acceleration
subplot(5,1,2);

plot(timestamp/1000, IMU_acc_x,'r');
hold on;
plot(timestamp/1000, IMU_acc_y,'g');
plot(timestamp/1000, IMU_acc_z,'b');
xlabel('seconds [s]');
ylabel('acceleration [m/s^2]');
xlim([startInterval,endInterval]);
legend('Acceleration_x','Acceleration_y','Acceleration_z');

title('Acceleration');

%plot Total Acceleration
subplot(5,1,3);
total_lin_acc = sqrt(IMU_lin_accel_x.^2 + IMU_lin_accel_y.^2 + IMU_lin_accel_z.^2);
total_acc = sqrt(IMU_acc_x.^2 + IMU_acc_y.^2 + IMU_acc_z.^2);
plot(timestamp/1000, total_acc,'r');
xlabel('seconds [s]');
ylabel('acceleration [m/s^2]');
xlim([startInterval,endInterval]);
legend('Total\_Acceleration');

title('Total Acceleration');

%{
%plot Total Linear Acceleration
subplot(5,1,3);
total_lin_acc = sqrt(IMU_lin_accel_x.^2 + IMU_lin_accel_y.^2 + IMU_lin_accel_z.^2);
plot(timestamp/1000, total_lin_acc,'r');
xlabel('seconds [s]');
ylabel('acceleration [m/s^2]');
xlim([startInterval,endInterval]);
legend('Total\_Linear\_Acceleration');

title('Total Linear Acceleration');
%}

%plot altitude
subplot(5,1,4);
plot(timestamp/1000, BME_altitude);
xlabel('seconds [s]');
ylabel('height [m]');
xlim([startInterval,endInterval]);
legend('Altitude');
title('Altitude');

%plot states
subplot(5,1,5);
plot(timestamp/1000, states);
xlabel('seconds [s]');
ylabel('state');
xlim([0,20]);
legend('states');
title('State transitions');

