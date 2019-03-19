filename = 'DATAFILE.TXT';
delimiterIn = ',';
headerlinesIn = 0;
data = importdata(filename,delimiterIn,headerlinesIn);

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
xlim([1430,1520]);
title('Accelerations');

%plot ROLL/PITCH/YAW
subplot(5,1,2);
plot(timestamp/1000, IMU_roll,'r');
hold on;
plot(timestamp/1000, IMU_pitch,'g');
plot(timestamp/1000, IMU_yaw,'b');
xlabel('seconds [s]');
ylabel('degrees [°]');
xlim([1430,1520]);
legend('Roll_z','Pitch_y','Yaw_x');

title('Euler angles in body frame');

%plot altitude
subplot(5,1,3);
plot(timestamp/1000, BME_altitude);
xlabel('seconds [s]');
ylabel('height [m]');
xlim([1430,1520]);
legend('Altitude');
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
plot(timestamp/1000, IMU_temp);
xlabel('seconds [s]');
ylabel('deg celsius [°/C]');
legend('BME Temperature','IMU Temperature');
xlim([1430,1520]);
title('Temperature');

%Plot states
