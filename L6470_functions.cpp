#include "functions.h"
#include "mbed.h"
#include "L6470.h"
#include "StepperMotor.h"
#include "variables.h"
#include "serial_function.h"


uint16_t get_speed(L6470 **motors, uint8_t mtr)
{
	return motors[mtr]->get_speed();
}

uint16_t get_max_speed(L6470 **motors, uint8_t mtr)
{
	return motors[mtr]->get_max_speed();
}

uint16_t get_min_speed(L6470 **motors, uint8_t mtr)
{
	return motors[mtr]->get_min_speed();
}

uint16_t get_accel(L6470 **motors, uint8_t mtr)
{
	return motors[mtr]->get_acceleration();
}

uint16_t get_deccel(L6470 **motors, uint8_t mtr)
{
	return motors[mtr]->get_deceleration();
}

uint8_t get_step_mode(L6470 **motors, uint8_t mtr)
{
	return init[mtr].step_sel;
}

StepperMotor::direction_t get_direction(L6470 **motors, uint8_t mtr)
{
	return motors[mtr]->get_direction();
}

uint16_t get_status(L6470 **motors, uint8_t mtr)
{
	return motors[mtr]->get_status();
}

uint16_t get_parameter(L6470 **motors, uint8_t mtr, uint16_t parameter)
{
	uint16_t parameter_value;
	if (mtr == 0)
	{
		parameter_value = motors[0]->get_parameter(parameter);
		pci.printf("motor_0\n");
	}
	else if (mtr == 1)
	{
		parameter_value = motors[1]->get_parameter(parameter);
		pci.printf("motor_1\n");
	}
	//else
		//pc.printf("Error Code\n");
	return parameter_value;
}

int16_t get_position(L6470 **motors, uint8_t mtr)
{
	return  motors[mtr]->get_position();
}

int16_t get_mark(L6470 **motors, uint8_t mtr)
{
	return motors[mtr]->get_mark();
}

void set_max_speed(L6470 **motors, uint8_t mtr, uint16_t max_speed)
{
	motors[mtr]->set_max_speed(max_speed);
}

void set_min_speed(L6470 **motors, uint8_t mtr, uint16_t min_speed)
{
	motors[mtr]->set_max_speed(min_speed);
}

void set_accel(L6470 **motors, uint8_t mtr, uint16_t accel)
{
		motors[mtr]->set_acceleration(accel);
}

void set_deccel(L6470 **motors, uint8_t mtr, uint16_t deccel)
{
		motors[mtr]->set_deceleration(deccel);
}

void set_step_mode(L6470 **motors, uint8_t mtr, StepperMotor::step_mode_t step_mode)
{
	motors[mtr]->set_step_mode(step_mode);
}

void set_parameter(L6470 **motors, uint8_t mtr, uint16_t parameter, uint16_t value)
{
	motors[mtr]->set_parameter(parameter, value);
}

void set_home(L6470 **motors, uint8_t mtr)
{
	motors[mtr]->set_home();
}

void set_mark(L6470 **motors, uint8_t mtr)
{
	motors[mtr]->set_mark();
}

void set_kval_run(L6470 **motors, uint8_t mtr, float kval_run)
{
	init[mtr].kvalrun = kval_run;
}

void set_kval_hold(L6470 **motors, uint8_t mtr, float kval_hold)
{
	init[mtr].kvalhold = kval_hold;
}

void set_kval_accel(L6470 **motors, uint8_t mtr, float kval_accel)
{
	init[mtr].kvalacc = kval_accel;
}

void set_kval_decel(L6470 **motors, uint8_t mtr, float kval_decel)
{
	init[mtr].kvaldec = kval_decel;
}

void set_parameter(L6470  **motors, uint8_t mtr, uint8_t parameter, uint16_t value)
{
	motors[mtr]->set_parameter(parameter, value);
}

