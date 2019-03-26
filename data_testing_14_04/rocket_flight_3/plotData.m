filename = 'DATAFILE.TXT';
recFilename = 'RECFILE.TXT';
delimiterIn = ',';
headerlinesIn = 0;
data = importdata(filename,delimiterIn,headerlinesIn);
recData = importdata(recFilename,delimiterIn,headerlinesIn);

startInterval = 796;
endInterval = 802;

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
Average_Height = recData(:,4);

figure(1);
%{
%Plotting Linear Acceleration
subplot(5,1,1);

plot(timestamp/1000, IMU_lin_accel_x,'r');
hold on;
plot(timestamp/1000, IMU_lin_accel_y,'g');
plot(timestamp/1000, IMU_lin_accel_z,'b');
grid on;
xlabel('seconds [s]');
ylabel('acceleration [m/s^2]');
l = legend('Lin\_Accel_x','Lin\_Accel_y','Lin\_Accel_z');
xlim([startInterval, endInterval]);
title('Accelerations without gravity');

%plot total Linear Acceleration
subplot(5,1,2);
IMU_total_mag = sqrt(IMU_mag_x.^2 + IMU_mag_y.^2 +IMU_mag_z.^2);
plot(timestamp/1000, IMU_mag_y,'r');
hold on;
grid on;
xlabel('seconds [s]');
ylabel('Something Tesla [xT]');
l = legend('Total\_Mag\_field\_strength_x');
xlim([startInterval,endInterval]);
title('Total magnetic field strength');
%}


%plot Acceleration
subplot(5,1,2);

plot(timestamp/1000, IMU_acc_x,'r');
hold on;
plot(timestamp/1000, -1*IMU_acc_y,'g');
plot(timestamp/1000, IMU_acc_z,'b');
grid on;
xlabel('seconds [s]');
ylabel('acceleration [m/s^2]');
l = legend('Accel_x','Accel_y','Accel_z');
xlim([startInterval,endInterval]);
title('Accelerations with gravity');

%plot total Acceleration
subplot(5,1,3);
IMU_total_accel = sqrt(IMU_acc_x.^2 + IMU_acc_y.^2 +IMU_acc_z.^2);
plot(timestamp/1000, IMU_total_accel,'r');
hold on;
grid on;
xlabel('seconds [s]');
ylabel('acceleration [m/s^2]');
l = legend('Total\_Accel_x');
xlim([startInterval,endInterval]);
title('Total accelerations with gravity');


%plot total Acceleration
subplot(5,1,1);
IMU_total_lin_accel = sqrt(IMU_lin_accel_x.^2 + IMU_lin_accel_y.^2 +IMU_lin_accel_z.^2);
plot(timestamp/1000, IMU_total_lin_accel,'r');
hold on;
grid on;
xlabel('seconds [s]');
ylabel('acceleration [m/s^2]');
l = legend('Total\_Lin\_Accel_x');
xlim([startInterval,endInterval]);
title('Total accelerations without gravity');

%plot altitude
subplot(5,1,4);
plot(timestamp/1000, BME_altitude);
xlabel('seconds [s]');
grid on;
ylabel('height [m]');
xlim([startInterval,endInterval]);
l = legend('Altitude');
l.FontSize = 16;
title('Altitude');

%plot states
subplot(5,1,5);
plot(timestamp/1000, states);
xlabel('seconds [s]');
ylabel('state');
grid on;
xlim([startInterval,endInterval]);
l = legend('states [1=armed,2=burnout,3=airbrakes,4=apogee,5=drogue,6=chute,7=landed]');
l.FontSize = 16;
title('State transitions');
%Plot states
