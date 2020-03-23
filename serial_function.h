#ifndef SERIAL_FUNCTION_H_
#define SERIAL_FUNCTION_H_

#include "mbed.h"
#include "variables.h"

extern char message[32];
extern RawSerial pci;

int read_serial(void);

void onDataReceived(void);
bool set_message(L6470 **motors);
bool read_message(L6470 **motors);
bool x_movement(void);
bool y_movement(void);
bool xy_movement(void);
bool failure_message(void);

int16_t extract_int(char *input);

#endif /* SERIAL_FUNCTION_H_ */
