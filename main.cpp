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
	  case 65:  //'A' - test write
		  motors[0]->set_max_speed(121);   ///PRIAMY PRISTUP Z MAIN FUNGUJE
		  pci.printf("_A\n");
	  break;

	  case 66:  //'B' - test read
		  pci.printf ("_B_%d\n", motors[0]->get_max_speed());    ///PRIAMY PRISTUP Z MAIN FUNGUJE
	  break;

	  case 83:  //'S' - set setup
		reply = set_message();     ///PRISTUP CEZ serial_functions.cpp - > L6470_functions.cpp NEFUNGUJE
	  break;

	  case 82:  //'R' - read setup
		reply = read_message();    ///PRISTUP CEZ serial_functions.cpp - > L6470_functions.cpp NEFUNGUJE
	  break;

	  case 88:   //'X'  X move
		speedoo = motors[0]->get_max_speed();
		pci.printf("_X\n");
	  break;

	  case 89:  // 'Y' Y move
		  motors[0]->set_max_speed(200);
		  pci.printf("_Y\n");
	  break;

	  case 90:  // 'Z' XY move
		  reply = xy_movement();
		  pci.printf("_Z\n");
	  break;


	  }
	memset(message, '\0', sizeof message);
  }
}



