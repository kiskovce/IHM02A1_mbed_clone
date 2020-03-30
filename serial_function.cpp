#include "mbed.h"
#include "DevSPI.h"
#include "XNucleoIHM02A1.h"
#include "variables.h"
#include "L6470_functions.h"
#include "StepperMotor.h"
#include "main.h"
#include "L6470.h"

#define STRING_SIZE 7

RawSerial pci(USBTX, USBRX);

EventQueue *queue = mbed_event_queue();


char message [32];
char message_irq[32];


/*================================================ DECLARATIONS ===================================*/
void read_serial(void);
StepperMotor::direction_t extract_dir (char *input);
int16_t extract_int(char *input);
uint8_t extract_motor (char *input);
int16_t extract_num (char *input);
StepperMotor::step_mode_t extract_step_mode (char *input);
uint8_t extract_parameter (char *input);
uint16_t extract_par_value(char *input);


/*================================================FUNCTIONS========================================*/
void onDataReceived()
{
	pci.attach(NULL, Serial::RxIrq); // detach interrupt
	queue->call(read_serial);		// process in a non ISR context
}

void read_serial() {
	int string_possition;
	char chr;
	char message_irq[32];
	do
	{
	    chr = pci.getc();
		message_irq[string_possition] = chr;
		string_possition++;
	}
	while (chr != '\n');    // end of line character
	memcpy ( message, message_irq, 32 );
	memset(message_irq, '\0', sizeof message_irq);
	pci.attach(&onDataReceived, Serial::RxIrq);	// reattach interrupt
}

bool set_message(L6470 **motors)

{
	int second_char = message[1];
	uint16_t num = extract_int(message);
	uint8_t mtr = extract_motor(message);
	uint8_t parameter;
	int16_t value;
	StepperMotor::step_mode_t step_mode = StepperMotor::STEP_MODE_FULL;

	switch (second_char)
	{
	case 65: //'A' set_step
		pci.printf("_SA_%d_%d\n", mtr, num);
		mtr = extract_motor(message);
		if (mtr == 9)
		{
			set_step_mode(motors, 0, extract_step_mode(message));
			wait_us(100);
			set_step_mode(motors, 1, extract_step_mode(message));
		}
		else
			set_step_mode(motors, mtr, extract_step_mode(message));
	break;

	case 66: //'B' set_max_speed
		mtr = extract_motor(message);
		num = extract_num(message);
		pci.printf("_SB_%d_%d\n", mtr, num);
		if (mtr == 9)
		{
			set_max_speed(motors, 0, num);
			wait_us(100);
			set_max_speed(motors, 1, num);
		}
		else
			set_max_speed(motors, mtr, num);
	break;

	case 67: //'C' set_min_speed
		mtr = extract_motor(message);
		num = extract_num(message);
		pci.printf("_SC_%d_%d\n", mtr, num);
		if (mtr == 9)
		{
			set_min_speed(motors, 0, num);
			wait_us(100);
			set_min_speed(motors, 1, num);
		}
		else
		set_min_speed(motors, mtr, num);
	break;

	case 68: //'D' set_accel
		mtr = extract_motor(message);
		num = extract_num(message);
		pci.printf("_SD_%d_%d\n", mtr, num);
		if (mtr == 9)
		{
			set_accel(motors, 0, num);
			wait_us(100);
			set_accel(motors, 1, num);
		}
		else
		set_accel(motors, mtr, num);
	break;

	case 69: //'E' set_decel
		mtr = extract_motor(message);
		num = extract_num(message);
		pci.printf("_SE_%d_%d\n", mtr, num);
		if (mtr == 9)
		{
			set_deccel(motors, 0, num);
			wait_us(100);
			set_deccel(motors, 1, num);
		}
		else
		set_deccel(motors, mtr, num);
	break;

	case 70: //'F' set mark
		mtr = extract_motor(message);
		num = extract_num(message);
		pci.printf("_SF_%d\n", mtr);
		if (mtr == 9)
		{
			set_mark(motors, 0);
			wait_us(100);
			set_mark(motors, 1);
		}
		else
		set_mark(motors, mtr);
	break;

	case 71: //'G' set home
		mtr = extract_motor(message);
		num = extract_num(message);
		pci.printf("_SG_%d\n", mtr);
		if (mtr == 9)
		{
			set_home(motors, 0);
			wait_us(100);
			set_home(motors, 1);
		}
		else
		set_home(motors, mtr);
	break;

	case 72: //'H' set parameter    //SH_a_24_265
		mtr = extract_motor(message);
		parameter = extract_parameter(message);
		value = extract_par_value(message);
		uint16_t parameter;
		uint16_t value;
		pci.printf("_SH0\n");
		if (mtr == 9)
		{
			set_parameter(motors, 0, parameter, value);
			wait_us(100);
			set_parameter(motors, 1, parameter, value);
		}
		else
			set_parameter(motors, mtr, parameter, value);
		set_parameter(motors, mtr, 2, 5);
	break;

	case 73: //'I' set kval hold
		mtr = extract_motor(message);
		num = extract_num(message);
		pci.printf("_SI_%d_%d\n", mtr, num);
		if (mtr == 9)
		{
			set_kval_hold(motors, 0, num);
			wait_us(100);
			set_kval_hold(motors, 1, num);
		}
		else
		set_kval_hold(motors, mtr, num);
	break;

	case 74: //'J' set kval run
		mtr = extract_motor(message);
		num = extract_num(message);
		pci.printf("_SJ_%d_%d\n", mtr, num);
		if (mtr == 9)
		{
			set_kval_run(motors, 0, num);
			wait_us(100);
			set_kval_run(motors, 1, num);
		}
		else
		set_kval_run(motors, mtr, num);
	break;

	case 75: //'K' set kval accel
		mtr = extract_motor(message);
		num = extract_num(message);
		pci.printf("_SK_%d_%d\n", mtr, num);
		if (mtr == 9)
		{
			set_kval_accel(motors, 0, num);
			wait_us(100);
			set_kval_accel(motors, 1, num);
		}
		else
		set_kval_accel(motors, mtr, kval_accel);
	break;

	case 76: //'L' set kval deccel
		mtr = extract_motor(message);
		num = extract_num(message);
		pci.printf("_SL_%d_%d\n", mtr, num);
		if (mtr == 9)
		{
			set_kval_decel(motors, 0, num);
			wait_us(100);
			set_kval_decel(motors, 1, num);
		}
		else
		set_kval_decel(motors, mtr, kval_decel);
	break;

	case 81: //'Q' set max voltage
		mtr = extract_motor(message);
		num = extract_num(message);
		if (mtr == 9)
		{
			//set_min_speed(motors, 0, num);
			wait_us(100);
			//set_min_speed(motors, 1, num);
		}
		else
		pci.printf("_SQ_%d_%d\n", mtr, num);
	break;

	case 82: //'R' set max current
		mtr = extract_motor(message);
		num = extract_num(message);
		if (mtr == 9)
		{
			set_parameter(motors, 0, parameter, value);
			wait_us(100);
			set_parameter(motors, 1, parameter, value);
		}
		else
			set_parameter(motors, mtr, parameter, value);
		pci.printf("_SR_%d_%d\n", mtr, num);
	break;

	default:
		pci.printf("-------NON OF IT----------------\n");
	break;

	}

	return true;
}

bool read_message(L6470 **motors)
{
 int second_char = message[1];
	 uint16_t sf_speed;
	 uint16_t sf_max_speed;
	 uint16_t sf_min_speed;
	 uint16_t sf_accel;
	 uint16_t sf_deccel;
	 uint8_t sf_direction;
	 uint16_t sf_status;
	 uint16_t sf_parameter = 3;
	 uint16_t sf_parameter_value;
	 uint16_t sf_position;
	 uint16_t sf_mark;
 	 uint8_t sf_step_mode;
 	 uint16_t sf_max_voltage;
 	 uint16_t sf_max_current;
 	 uint16_t sf_kval_hold;
 	 uint16_t sf_kval_run;
 	 uint16_t sf_kval_accel;
 	 uint16_t sf_kval_decel;

 	uint16_t num = extract_int(message);
 	uint8_t mtr = extract_motor(message);

 switch (second_char)
 {
 case 65: //'A'  -get step mode    //SA_a_1 = full step   SA_b_9 = 1/256
	 mtr = extract_motor(message);
	 sf_step_mode = get_step_mode(motors, mtr);
  	 pci.printf("_RA_%d_%d\n",mtr, sf_step_mode);
  break;

 case 66: //'B'  -get max speed
	 mtr = extract_motor(message);
	 sf_max_speed = get_max_speed(motors, mtr);
	 pci.printf("_RB_%d_%d\n",mtr,sf_max_speed);
  break;

 case 67: //'C'  -get min speed
	 mtr = extract_motor(message);
	 sf_min_speed = get_min_speed(motors, mtr);
	 pci.printf("_RC_%d_%d\n",mtr, sf_min_speed);
  break;

 case 68: //'D'  -get acceleration
	 mtr = extract_motor(message);
	 sf_accel = get_accel(motors, mtr);
	 pci.printf("_RD_%d_%d\n",mtr, sf_accel);
  break;

 case 69: //'E'  -get deceleration
	 mtr = extract_motor(message);
	 sf_deccel = get_deccel(motors, mtr);
	 pci.printf("_RE_%d_%d\n",mtr, sf_deccel);
  break;

 case 70: //'F'  -get mark
	 mtr = extract_motor(message);
	 sf_mark = get_mark(motors, mtr);
 	 pci.printf("_RF_%d_%d\n",mtr, sf_mark);
  break;

 case 72: //'H'  -get parameter
	 mtr = extract_motor(message);
	 //sf_parameter_value = get_paraeter(motors, mtr, sf_parameter);
 	 pci.printf("_RH%d_%d", sf_parameter, sf_parameter_value);
  break;

 case 73: //'I'  -get kval hold
	 mtr = extract_motor(message);
	 sf_direction = get_direction(motors, mtr);
	 pci.printf("_RI_%d_%d\n",mtr, sf_kval_hold);
  break;

 case 74: //'J'  -get kval run
	 mtr = extract_motor(message);
	 sf_direction = get_direction(motors, mtr);
 	 pci.printf("_RJ_%d_%d\n",mtr, sf_kval_run);
   break;

 case 75: //'K'  -get kval accel
	 mtr = extract_motor(message);
	 sf_direction = get_direction(motors, mtr);
 	 pci.printf("_RK_%d_%d\n",mtr, sf_kval_hold);
   break;

 case 76: //'L'  -get kval deccel
	 mtr = extract_motor(message);
	 sf_direction = get_direction(motors, mtr);
  	 pci.printf("_RL_%d_%d\n",mtr, sf_kval_hold);
 break;

 case 77: //'M'  -get speed
	 mtr = extract_motor(message);
	 sf_speed = get_speed(motors, mtr);
	 pci.printf("_RM_%d_%d\n",mtr,sf_speed);
 break;

 case 78: //'N'  -get direction
	 mtr = extract_motor(message);
	 sf_direction = get_direction(motors, mtr);
	 pci.printf("_RN_%d_%d\n",mtr, sf_direction);
  break;

 case 79: //'O'  -get status
	 mtr = extract_motor(message);
	 sf_status = get_status(motors, mtr);
 	 pci.printf("_RO_%d_%d\n",mtr, sf_status);
  break;


 case 80: //'P'  -get position
	 mtr = extract_motor(message);
	 sf_position = get_position(motors, mtr);
 	 pci.printf("_RP_%d_%d\n",mtr, sf_position);
  break;

 case 81: //'Q'  -get max voltage
	 mtr = extract_motor(message);
	 pci.printf("_RQ_%d_%d\n",mtr, sf_max_voltage);
   break;

 case 82: //'R'  -get max current
	 mtr = extract_motor(message);
	 pci.printf("_RR_%d_%d\n",mtr, sf_max_current);
   break;

 case 86: //'V'  -get all
	 //sf_max_speed = get_max_speed(mtr);
	 //sf_min_speed = get_min_speed(mtr);
	 //sf_accel     = get_accel(mtr);
  	 //sf_deccel    = get_deccel(mtr);
  	 //sf_step_mode = get_step_mode(mtr);
   break;
 }

	return true;
}

bool x_movement(L6470 **motors)
{

	motors[0]->move(extract_dir(message), extract_num(message));
	motors[0]->wait_while_active();
	x_position = motors[0]->get_position();
	pci.printf("_X:%d", x_position);

	return true;
}

bool y_movement(L6470 **motors)
{

	motors[1]->move(extract_dir(message), extract_num(message));
	motors[1]->wait_while_active();
	y_position = motors[0]->get_position();
	pci.printf("_Y:%d", x_position);
	return true;
}

bool xy_movement(L6470 **motors)
{
	pci.printf("xy_movement\n");

	return true;
}

bool failure_message(void)
{

	pci.printf("failure_mesage\n");
	return true;
}

int16_t extract_int(char *input)
{
    char numbers[STRING_SIZE];
    int16_t number_pos = 0;
    for (uint16_t i = 0; i < STRING_SIZE; i++) {
        if ((input[i] > 47) and (input[i] < 58)) { //ACSI set of numbers
            numbers[number_pos] = input[i];
            number_pos++;
        }
    }
    return atoi(numbers);
}

int16_t extract_num (char *input)
{
	uint8_t str_position = 5;
	uint8_t vl_position = 0;
	char value[(STRING_SIZE - 5)];
	while (input[str_position] > 47 && input[str_position] < 58)
	{
		value[vl_position] = input[str_position];
		vl_position++;
		str_position++;
	}
	return atoi(value);
}

uint8_t extract_motor (char *input)
{
	uint8_t motor_num;
	if (input[3] == 'a')
		motor_num = 0;
	else if (input[3] == 'b')
		motor_num = 1;
	else if (input[3] == 'X')
		motor_num = 9;
	return motor_num;
}

StepperMotor::direction_t extract_dir (char *input)
{
	StepperMotor::direction_t retVal;
	if (message[2] == 'f')
		retVal == StepperMotor::FWD;
	else if (message[2] == 'b')
		retVal == StepperMotor::BWD;
	else
		pci.printf("non of it\n");
	return retVal;
}


StepperMotor::step_mode_t extract_step_mode (char *input)
{
	StepperMotor::step_mode_t retVal;
	if (input[5] == 1)
		retVal = StepperMotor::STEP_MODE_FULL;
	else if (input[5] == 2)
		retVal = StepperMotor::STEP_MODE_HALF;
	else if (input[5] == 3)
		retVal = StepperMotor::STEP_MODE_1_4;
	else if (input[5] == 4)
		retVal = StepperMotor::STEP_MODE_1_8;
	else if (input[5] == 5)
		retVal = StepperMotor::STEP_MODE_1_16;
	else if (input[5] == 6)
		retVal = StepperMotor::STEP_MODE_1_32;
	else if (input[5] == 7)
		retVal = StepperMotor::STEP_MODE_1_64;
	else if (input[5] == 8)
		retVal = StepperMotor::STEP_MODE_1_128;
	else if (input[5] == 9)
		retVal = StepperMotor::STEP_MODE_1_256;
}

uint8_t extract_parameter (char *input)
{
	char parameter_str[2] = {0,0};
	parameter_str[0] = input[5];
	parameter_str[1] = input[6];

	return atoi(parameter_str);
}

uint16_t extract_par_value(char *input)
{
	uint8_t str_position = 8;
		uint8_t vl_position = 0;
		char value[(STRING_SIZE - 5)];
		while (input[str_position] > 47 && input[str_position] < 58)
		{
			value[vl_position] = input[str_position];
			vl_position++;
			str_position++;
		}
		return atoi(value);
}
