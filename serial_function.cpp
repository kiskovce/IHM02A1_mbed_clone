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

void read_serial(void);
int16_t extract_int(char *input);
uint8_t extract_motor(char *input);
char message [32];
char message_irq[32];


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
	StepperMotor::step_mode_t step_mode = StepperMotor::STEP_MODE_FULL;

	switch (second_char)
	{
	case 65: //'A' set_step
		pci.printf("_SA_%d_%d\n", mtr, num);
		set_step_mode(motors, mtr, step_mode);
	break;

	case 66: //'B' set_max_speed
		pci.printf("_SB_%d_%d\n", mtr, num);
		set_max_speed(motors, mtr, num);
	break;

	case 67: //'C' set_min_speed
		pci.printf("_SC_%d_%d\n", mtr, num);
		set_min_speed(motors, mtr, num);
	break;

	case 68: //'D' set_accel
		pci.printf("_SD_%d_%d\n", mtr, num);
		set_accel(motors, mtr, num);
	break;

	case 69: //'E' set_decel
		pci.printf("_SE_%d_%d\n", mtr, num);
		set_deccel(motors, mtr, num);
	break;

	case 70: //'F' set mark
		pci.printf("_SF_%d\n", mtr);
		set_mark(motors, mtr);
	break;

	case 71: //'G' set home
		pci.printf("_SG_%d\n", mtr);
		set_home(motors, mtr);
	break;

	case 72: //'H' set parameter
		uint16_t parameter;
		uint16_t value;
		pci.printf("_SH0\n");
		set_parameter(motors, mtr, 2, 5);
	break;

	case 73: //'I' set kval hold
		pci.printf("_SI_%d_%d\n", mtr, num);
		set_kval_hold(motors, mtr, num);
	break;

	case 74: //'J' set kval run
		pci.printf("_SJ_%d_%d\n", mtr, num);
		set_kval_run(motors, mtr, num);
	break;

	case 75: //'K' set kval accel
		pci.printf("_SK_%d_%d\n", mtr, num);
		set_kval_accel(motors, mtr, kval_accel);
	break;

	case 76: //'L' set kval deccel
		pci.printf("_SL_%d_%d\n", mtr, num);
		set_kval_decel(motors, mtr, kval_decel);
	break;

	case 81: //'Q' set max voltage
		pci.printf("_SQ_%d_%d\n", mtr, num);
	break;

	case 82: //'R' set max current
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
 case 65: //'A'  -get step mode
  	 sf_step_mode = get_step_mode(motors, mtr);
  	 pci.printf("_RA_%d_%d\n",mtr, sf_step_mode);
  break;

 case 66: //'B'  -get max speed
	 sf_max_speed = get_max_speed(motors, mtr);
	 pci.printf("_RB_%d_%d\n",mtr,sf_max_speed);
  break;

 case 67: //'C'  -get min speed
	 sf_min_speed = get_min_speed(motors, mtr);
	 pci.printf("_RC_%d_%d\n",mtr, sf_min_speed);
  break;

 case 68: //'D'  -get acceleration
	 sf_accel = get_accel(motors, mtr);
	 pci.printf("_RD_%d_%d\n",mtr, sf_accel);
  break;

 case 69: //'E'  -get deceleration
	 sf_deccel = get_deccel(motors, mtr);
	 pci.printf("_RE_%d_%d\n",mtr, sf_deccel);
  break;

 case 70: //'F'  -get mark
 	 sf_mark = get_mark(motors, mtr);
 	 pci.printf("_RF_%d_%d\n",mtr, sf_mark);
  break;

 case 72: //'H'  -get parameter
	 sf_parameter_value = get_parameter(motors, mtr, sf_parameter);
 	 pci.printf("_RH%d_%d", sf_parameter, sf_parameter_value);
  break;

 case 73: //'I'  -get kval hold
	 sf_direction = get_direction(motors, mtr);
	 pci.printf("_RI_%d_%d\n",mtr, sf_kval_hold);
  break;

 case 74: //'J'  -get kval run
 	 sf_direction = get_direction(motors, mtr);
 	 pci.printf("_RJ_%d_%d\n",mtr, sf_kval_run);
   break;

 case 75: //'K'  -get kval accel
 	 sf_direction = get_direction(motors, mtr);
 	 pci.printf("_RK_%d_%d\n",mtr, sf_kval_hold);
   break;

 case 76: //'L'  -get kval deccel
  	 sf_direction = get_direction(motors, mtr);
  	 pci.printf("_RL_%d_%d\n",mtr, sf_kval_hold);
 break;

 case 77: //'M'  -get speed
	 sf_speed = get_speed(motors, mtr);
	 pci.printf("_RM_%d_%d\n",mtr,sf_speed);
 break;

 case 78: //'N'  -get direction
	 sf_direction = get_direction(motors, mtr);
	 pci.printf("_RN_%d_%d\n",mtr, sf_direction);
  break;

 case 79: //'O'  -get status
	 sf_status = get_status(motors, mtr);
 	 pci.printf("_RO_%d_%d\n",mtr, sf_status);
  break;


 case 80: //'P'  -get position
 	 sf_position = get_position(motors, mtr);
 	 pci.printf("_RP_%d_%d\n",mtr, sf_position);
  break;



 case 81: //'Q'  -get max voltage
  	 pci.printf("_RQ_%d_%d\n",mtr, sf_max_voltage);
   break;

 case 82: //'R'  -get max current
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

bool x_movement(void)
{
	pci.printf("x_mesage\n");

	return true;
}

bool y_movement(void)
{

	pci.printf("y_movement\n");
	return true;
}

bool xy_movement(void)
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

uint8_t extract_motor (char *input)
{
	uint8_t motor_num;
	if (input[4] == 'a')
		motor_num = 0;
	else if (input[4] == 'b')
		motor_num = 1;
	return motor_num;
}
