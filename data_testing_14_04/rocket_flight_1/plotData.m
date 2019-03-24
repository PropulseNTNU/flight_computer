filename = 'DATAFILE.TXT';
delimiterIn = ',';
headerlinesIn = 0;
data = importdata(filename,delimiterIn,headerlinesIn)
startInterval = 430;
endInterval = 445;
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
%plot Acceleration
subplot(5,1,1);
plot(timestamp/1000, IMU_lin_accel_x,'r');
hold on;
plot(timestamp/1000, IMU_lin_accel_y,'g');
plot(timestamp/1000, IMU_lin_accel_z,'b');
xlabel('seconds [s]');
ylabel('acceleration [m/s^2]');
legend('Lin\_Accel_x','Lin\_Accel_y','Lin\_Accel_z');
xlim([startInterval,endInterval]);
title('Linear acceleration');

%plot Acceleration
subplot(5,1,2);
plot(timestamp/1000, IMU_acc_x,'r');
hold on;
plot(timestamp/1000, IMU_acc_y,'g');
plot(timestamp/1000, IMU_acc_z,'b');
xlabel('seconds [s]');
ylabel('Accel [°]');
xlim([startInterval,endInterval]);
legend('Acceleration_z','Acceleration_y','Acceleration_x');

title('Acceleration');

%plot Acceleration
subplot(5,1,3);
totalAcc = sqrt(IMU_acc_x.^2 + IMU_acc_x.^2 + IMU_acc_x.^2)
plot(timestamp/1000, IMU_acc_x,'r');
xlabel('seconds [s]');
ylabel('Accel [°]');
xlim([startInterval,endInterval]);
legend('Total acceleration')

title('Acceleration');

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
xlim([startInterval,endInterval]);
legend('states');
title('Altitude');


