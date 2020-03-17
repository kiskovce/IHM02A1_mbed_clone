#include "mbed.h"
#include "XNucleoIHM02A1.h"
#include "DevSPI.h"
#include "functions.h"
#include "serial_function.h"

XNucleoIHM02A1 *x_nucleo_ihm02a1;
DevSPI dev_spi(D11, D12, D3);

int main()
{
   x_nucleo_ihm02a1 = new XNucleoIHM02A1(&init[0], &init[1], A4, A5, D4, A2, &dev_spi);      /* Initializing Motor Control Expansion Board. */
   L6470 **motors = x_nucleo_ihm02a1->get_components();       /* Building a list of motor control components. */
   pci.attach(&onDataReceived, Serial::RxIrq);
   pci.printf("****************************");

  while (1)
  {
	wait_ms(1500);
	bool reply = false;
	int speedoo;

	  switch (message[0])
	  {
	  case 83:  //'S' - set setup
		reply = set_message();
	  break;

	  case 82:  //'R' - read setup
		reply = read_message();
	  break;

	  case 88:   //'X'  X move
		pci.printf("Move x mode\n");
		pci.printf("second char is : %c\n", message[1]);
		//reply = x_movement();
		speedoo = motors[0]->get_max_speed();
		pci.printf("Printo is : %d\n", speedoo);
	  break;

	  case 89:  // 'Y' Y move
		  pci.printf("Move Y mode\n");
		  pci.printf("second char is : %c\n", message[1]);
		  motors[0]->set_max_speed(300);
		  wait(1);
		  motors[0]->set_max_speed(200);
		  //reply = y_movement();
	  break;

	  case 90:  // 'Z' XY move
		  pci.printf("move xy mode\n");
		  pci.printf("second char is : %c\n", message[1]);
		  reply = xy_movement();
	  break;

	  }
	memset(message, '\0', sizeof message);
  }
}



