#include <string>
#include "mbed.h"
#include "DevSPI.h"
#include "XNucleoIHM02A1.h"
#include "variables.h"
#include "L6470_functions.h"
#include "StepperMotor.h"

RawSerial pci(USBTX, USBRX);

EventQueue *queue = mbed_event_queue();

void read_serial(void);


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

bool set_message(void)

{
	int second_char = message[1];
	uint16_t num;
	StepperMotor::step_mode_t step_md;
	num = 100;
	mtr = 0;

	switch (second_char)
	{
	case 65: //'A' set_step
		pci.printf("_SA0\n");
		//set_step_mode(mtr, step_md);
	break;

	case 66: //'B' set_max_speed
		pci.printf("_SB0\n");
		set_max_speed(0, 200);
	break;

	case 67: //'C' set_min_speed
		pci.printf("_SC0\n");
		//set_min_speed(mtr, num);
	break;

	case 68: //'D' set_accel
		pci.printf("_SD0\n");
		//set_accel(mtr, num);
	break;

	case 69: //'E' set_decel
		pci.printf("_SE0\n");
		//set_deccel(mtr, num);
	break;

	case 70: //'F' set mark
		pci.printf("_SF0\n");
		//set_mark(mtr);
	break;

	case 71: //'G' set home
		pci.printf("_SG0\n");
		//set_home(mtr);
	break;

	case 72: //'H' set parameter
		uint16_t parameter;
		uint16_t value;
		pci.printf("_SH0\n");
		//set_parameter(mtr, parameter, value);
	break;

	case 73: //'I' set kval hold
		pci.printf("_SI0\n");
		//set_kval_hold(mtr, kval_hold);
	break;

	case 74: //'J' set kval run
		pci.printf("_SJ0\n");
		//set_kval_run(mtr, kval_run);
	break;

	case 75: //'K' set kval accel
		pci.printf("_SK0\n");
		//set_kval_accel(mtr, kval_accel);
	break;

	case 76: //'L' set kval deccel
		pci.printf("_SL0\n");
		//set_kval_decel(mtr, kval_decel);
	break;

	case 81: //'Q' set max voltage
		pci.printf("_SQ0\n");
	break;

	case 82: //'R' set max current
		pci.printf("_SR0\n");
	break;

	default:
		pci.printf("-------NON OF IT----------------\n");
	break;

	}

	return true;
}

bool read_message(void)
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

 	mtr = 0;

 switch (second_char)
 {
 case 65: //'A'  -get step mode
  	 //sf_step_mode = get_step_mode(mtr);
  	 pci.printf("_RA%d\n", sf_step_mode);
  break;

 case 66: //'B'  -get max speed
	 sf_max_speed = get_max_speed(0);
	 pci.printf("_RB%d\n", sf_max_voltage);
  break;

 case 67: //'C'  -get min speed
	 //sf_min_speed = get_min_speed(mtr);
	 pci.printf("_RC%d\n", sf_min_speed);
  break;

 case 68: //'D'  -get acceleration
	 //sf_accel = get_accel(mtr);
	 pci.printf("_RD%d\n", sf_accel);
  break;

 case 69: //'E'  -get deceleration
	 //sf_deccel = get_deccel(mtr);
	 pci.printf("_RE%d\n", sf_deccel);
  break;

 case 70: //'F'  -get mark
 	 //sf_mark = get_mark(mtr);
 	 pci.printf("_RF%d\n", sf_mark);
  break;

 case 72: //'H'  -get parameter
	 //sf_parameter_value = get_parameter(mtr, sf_parameter);
 	 pci.printf("_RH%d_%d", sf_parameter, sf_parameter_value);
  break;

 case 73: //'I'  -get kval hold
	 //sf_direction = get_direction(mtr);
	 pci.printf("_RI%d\n", sf_kval_hold);
  break;

 case 74: //'J'  -get kval run
 	 //sf_direction = get_direction(mtr);
 	 pci.printf("_RJ%d\n", sf_kval_run);
   break;

 case 75: //'K'  -get kval accel
 	 //sf_direction = get_direction(mtr);
 	 pci.printf("_RK%d\n", sf_kval_hold);
   break;

 case 76: //'L'  -get kval deccel
  	 //sf_direction = get_direction(mtr);
  	 pci.printf("_RL%d\n", sf_kval_hold);
 break;

 case 77: //'M'  -get speed
	 //sf_speed = get_speed(mtr);
	 pci.printf("_RM1224\n");
 break;

 case 78: //'N'  -get direction
	 //sf_direction = get_direction(mtr);
	 pci.printf("_RN%d\n", sf_direction);
  break;

 case 79: //'O'  -get status
	 //sf_status = get_status(mtr);
 	 pci.printf("_RO%d\n", sf_status);
  break;


 case 80: //'P'  -get position
 	 //sf_position = get_position(mtr);
 	 pci.printf("_RP%d\n", sf_position);
  break;



 case 81: //'Q'  -get max voltage
  	 pci.printf("_RQ%d\n", sf_max_voltage);
   break;

 case 82: //'R'  -get max current
  	 pci.printf("_RR%d\n", sf_max_current);
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
