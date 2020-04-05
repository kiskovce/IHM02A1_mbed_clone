#ifndef SERIAL_FUNCTION_H_
#define SERIAL_FUNCTION_H_

#include "mbed.h"
#include "variables.h"
#include "L6470.h"

extern char message[32];
extern RawSerial pci;

int read_serial(void);

void onDataReceived(void);
bool set_message(L6470 **motors);
bool read_message(L6470 **motors);
bool x_movement(L6470 **motors);
bool y_movement(L6470 **motors);
bool xy_movement(L6470 **motors);
bool failure_message(void);

int16_t extract_int(char *input);
StepperMotor::direction_t extract_dir (char *input);
uint8_t extract_motor (char *input);
int16_t extract_num (char *input);
StepperMotor::step_mode_t extract_step_mode (char *input);
uint8_t extract_parameter (char *input);
uint16_t extract_par_value(char *input);


#endif /* SERIAL_FUNCTION_H_ */
