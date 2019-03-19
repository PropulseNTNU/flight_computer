#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <SPI.h>
#include <RF24.h>
#include "sensorsFromPayload.h"

#define LED_pin 13
#define SCK_PIN 27
#define CE_PIN 6
#define CSN_PIN 7


void initMessage(double* data, int NUM_SENSORS);

int setupBle(double* data, int NUM_SENSORS);

char* retriveMessageBle();

void sendMessage(const char message);

/* Inerts data from payload(ble) in data array. */
int messageFromPayload(double* data);

void updateDataFromBle(double* data);

#endif
