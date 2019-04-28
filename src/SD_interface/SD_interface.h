#ifndef SD_INTERFACE_H
#define SD_INTERFACE_H

#include <SD.h>

#define DEMO_DATA_FILE "LAUNCH_file_MAINTM.mat"
#define TIMESTEP 0.003


enum fileEnum {
    DATA_FILE, AIRBRAKES_FILE, RECOVERY_FILE, NUM_FILES
};

enum logIntervalEnum {
    DATA_INTERVAL, AIRBRAKES_INTERVAL, DROGUE_INTERVAL, CHUTE_INTERVAL, NUM_INTERVALS
};

enum lastLogEnum {
    DATA_LASTLOG, COMMON_LASTLOG, NUM_LASTLOGS
};

String createDataString(double* data, int len);

void write_SD(int file, double* data, int len);

bool init_SD(int file, const char* fileName);

void closeAll_SD();

unsigned long* getLogInterval(int interval);
unsigned long* getLastLog(int lastLogType);

void setLastLog(unsigned long newLastLog, int lastLogType);

void read_demo_from_SD(File* demo_file, double* data, int len);

#endif
