#ifndef SERIAL_FUNCTION_H_
#define SERIAL_FUNCTION_H_

#include "mbed.h"
#include "variables.h"

extern char message[32];
extern RawSerial pci;

int read_serial(void);

void onDataReceived(void);
bool set_message(void);
bool read_message(void);
bool x_movement(void);
bool y_movement(void);
bool xy_movement(void);
bool failure_message(void);

#endif /* SERIAL_FUNCTION_H_ */
