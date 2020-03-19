#include "functions.h"
#include "mbed.h"
#include "L6470.h"
#include "StepperMotor.h"
#include "variables.h"
#include "serial_function.h"

uint16_t get_speed(uint8_t mtr)
{
	uint16_t speed;
	if (mtr == 0)
	{
		speed = motors[0]->get_speed();
		pci.printf("motor_0\n");
	}
	else if (mtr == 1)
	{
		speed = motors[1]->get_speed();
		pci.printf("motor_1\n");
	}
	//else
	//	pc.printf("Error Code\n");
	return speed;
}

uint16_t get_max_speed(uint8_t mtr)
{
	return motors[mtr]->get_max_speed();
}

uint16_t get_min_speed(uint8_t mtr)
{
	uint16_t min_speed;
	if (mtr == 0)
	{
		min_speed = motors[0]->get_min_speed();
		pci.printf("motor_0\n");
	}
	else if (mtr == 1)
	{
		min_speed = motors[1]->get_min_speed();
		pci.printf("motor_1\n");
	}
	//else
		//pc.printf("Error Code\n");
	return min_speed;
}

uint16_t get_accel(uint8_t mtr)
{
	uint16_t accel;
	if (mtr == 0)
	{
		accel = motors[0]->get_acceleration();
		pci.printf("motor_0\n");
	}
	else if (mtr == 1)
	{
		accel = motors[1]->get_acceleration();
		pci.printf("motor_1\n");
	}
	//else
		//pc.printf("Error Code\n");
	return accel;
}

uint16_t get_deccel(uint8_t mtr)
{
	uint16_t deccel;
	if (mtr == 0)
	{
		deccel = motors[0]->get_deceleration();
		pci.printf("motor_0\n");
	}
	else if (mtr == 1)
	{
		deccel = motors[1]->get_deceleration();
		pci.printf("motor_1\n");
	}
	//else
		//pc.printf("Error Code\n");
	return deccel;
}

uint8_t get_step_mode(uint8_t mtr)
{
	uint8_t step_mode;
	if(mtr == 0)
	{
		step_mode = init[0].step_sel;
		pci.printf("motor_0\n");
	}
	else if (mtr == 1)
	{
		step_mode = init[1].step_sel;
		pci.printf("motor_1\n");
	}
	//else
		//pc.printf("Error code\n");
	return step_mode;
}

StepperMotor::direction_t get_direction(uint8_t mtr)
{
	StepperMotor::direction_t direction;
	if (mtr == 0)
	{
		direction = motors[0]->get_direction();
		pci.printf("motor_0\n");
	}
	else if (mtr == 1)
	{
		direction = motors[1]->get_direction();
		pci.printf("motor_1\n");
	}
	//else
		//pc.printf("Error Code\n");
	return direction;
}

uint16_t get_status(uint8_t mtr)
{
	uint16_t status;
	if (mtr == 0)
	{
		status = motors[0]->get_status();
		pci.printf("motor_0\n");
	}
	else if (mtr == 1)
	{
		status = motors[1]->get_status();
		pci.printf("motor_1\n");
	}
	//else
		//pc.printf("Error Code\n");
	return status;
}

uint16_t get_parameter(uint8_t mtr, uint16_t parameter)
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

int16_t get_position(uint8_t mtr)
{
	int16_t position;
	if (mtr == 0)
	{
		position = motors[0]->get_position();
		pci.printf("motor_0\n");
	}
	else if (mtr == 1)
	{
		position = motors[1]->get_position();
		pci.printf("motor_1\n");
	}
	//else
		//pc.printf("Error Code\n");
	return position;
}

int16_t get_mark(uint8_t mtr)
{
	int16_t mark;
	if (mtr == 0)
	{
		mark = motors[0]->get_mark();
		pci.printf("motor_0\n");
	}
	else if (mtr == 1)
	{
		mark = motors[1]->get_mark();
		pci.printf("motor_1\n");
	}
	//else
		//pc.printf("Error Code\n");
	return mark;
}

void set_max_speed(L6470 **motors, uint8_t mtr, uint16_t max_speed)
{
	if (mtr == 0)
		{
		motors[0]->set_max_speed(300);
		}
	else if (mtr == 1)
		{
		motors[1]->set_max_speed(max_speed);
		}
}

void set_min_speed(uint8_t mtr, uint16_t min_speed)
{
	if (mtr == 0)
		{
		motors[0]->set_min_speed(min_speed);
		pci.printf("motor_0\n");
		}
	else if (mtr == 1)
		{
		motors[1]->set_max_speed(min_speed);
		pci.printf("motor_1\n");
		}
	//else
		//pc.printf("Error code\n");
}

void set_accel(uint8_t mtr, uint16_t accel)
{
	if (mtr == 0)
		{
		motors[0]->set_acceleration(accel);
		pci.printf("motor_0\n");
		}
	else if (mtr == 1)
		{
		motors[1]->set_acceleration(accel);
		pci.printf("motor_1\n");
		}
	//else
		//pc.printf("Error code\n");
}

void set_deccel(uint8_t mtr, uint16_t deccel)
{
	if (mtr == 0)
		{
		motors[0]->set_deceleration(deccel);
		pci.printf("motor_0\n");
		}
	else if (mtr == 1)
		{
		motors[1]->set_deceleration(deccel);
		pci.printf("motor_1\n");
		}
	//else
		//pc.printf("Error code\n");
}

void set_step_mode(uint8_t mtr, StepperMotor::step_mode_t step_mode)
{
if (mtr == 0)
	{
	motors[0]->set_step_mode(step_mode);
	pci.printf("motor_0\n");
	}
else if (mtr == 1)
	{
	motors[1]->set_step_mode(step_mode);
	pci.printf("motor_1\n");
	}
//else
	//pc.printf("Error code\n");
}

void set_parameter(uint8_t mtr, uint16_t parameter, uint16_t value)
{
	if (mtr == 0)
	{
		motors[0]->set_parameter(parameter, value);
		pci.printf("motor_0\n");
	}
	else if (mtr == 1)
	{
		motors[1]->set_parameter(parameter, value);
		pci.printf("motor_1\n");
	}
	//else
		//pc.printf("Error Code\n");
}

void set_home(uint8_t mtr)
{
	motors[mtr]->set_home();
	pci.printf("motor_%d\n", mtr);
}

void set_mark(uint8_t mtr)
{
	motors[mtr]->set_mark();
	pci.printf("motor_%d\n", mtr);
}

void set_kval_run(uint8_t mtr, float kval_run)
{
	init[mtr].kvalrun = kval_run;
	pci.printf("motor_%d\n", mtr);
}

void set_kval_hold(uint8_t mtr, float kval_hold)
{
	init[mtr].kvalhold = kval_hold;
	pci.printf("motor_%d\n", mtr);
}

void set_kval_accel(uint8_t mtr, float kval_accel)
{
	init[mtr].kvalacc = kval_accel;
	pci.printf("motor_%d\n", mtr);
}

void set_kval_decel(uint8_t mtr, float kval_decel)
{
	init[mtr].kvaldec = kval_decel;
	pci.printf("motor_%d\n", mtr);
}

