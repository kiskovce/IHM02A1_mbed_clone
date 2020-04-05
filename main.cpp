#include "mbed.h"
#include "XNucleoIHM02A1.h"
#include "DevSPI.h"
#include "functions.h"
#include "serial_function.h"
#include "L6470.h"
#include "StepperMotor.h"
#include "L6470_functions.h"
#include "g_code.h"
/*=============== creating objects===============*/
XNucleoIHM02A1 *x_nucleo_ihm02a1;
DevSPI dev_spi(D11, D12, D3);

int main()
{
   x_nucleo_ihm02a1 = new XNucleoIHM02A1(&init[0], &init[1], A4, A5, D4, A2, &dev_spi);      /* Initializing Motor Control Expansion Board. */
   L6470 **motors = x_nucleo_ihm02a1->get_components();       /* Building a list of motor control components. */
   pci.attach(&onDataReceived, Serial::RxIrq);


  while (1)
  {
	wait_ms(1500);
	bool reply = false;
	int speedoo;
	bool msg_ok = false;

	  switch (message[0])
	  {

	  case 83:  //'S' - set setup
		reply = set_message(motors);
	  break;

	  case 82:  //'R' - read setup
		reply = read_message(motors);
	  break;

	  case 71: // 'G' -- G code
		  error_code = g_code();
		 break;

	  case 88:   //'X'  X move                 //message X_b__2000
		msg_ok = x_movement(motors);
		if (msg_ok == true)
			pci.printf("_X_OK\n");
		else
			pci.printf("_X!!\n");
	  break;

	  case 89:  // 'Y' Y move               //message Y_f__5000
		msg_ok = y_movement(motors);
		if (msg_ok == true)
			pci.printf("_X_OK\n");
		else
			pci.printf("_X!!\n");
	  break;

	  case 90:  // 'Z' XY move
		  reply = xy_movement(motors);
		  pci.printf("_Z\n");
	  break;


	  }
	memset(message, '\0', sizeof message);
  }
}



