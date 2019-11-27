#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "keyboard.h"
const unsigned char codigo[] = "1234";

int PWRD(void) {
	int i = 0;
	int status = 0, done = 0, sucess = 1;
	char input_value[4];
	/* include your code here */

	for (;;) {
		sucess = 1;

		GetKEY();

		if (key_press != NO_TECLA) {
			(void) status++;

			if (status == 1) {

				input_value[0] = key_press;
				key_press = NO_TECLA;
			}
			if (status == 2) {
				input_value[1] = key_press;
				key_press = NO_TECLA;
			}
			if (status == 3) {
				input_value[2] = key_press;
				key_press = NO_TECLA;
			}
			if (status == 4) {
				input_value[3] = key_press;
				key_press = NO_TECLA;
				done = 1;

			}

			if (done == 1) {
				done = 0;
				status = 0;
				for (i = 0; i < 4; i++) {

					if (input_value[i] != codigo[i]) {
						return 0;
						sucess = 0;
						break;
					}

				}
				//i = 0;

				if (sucess)
					return 1;
			}

		} /* loop forever */
		/* please make sure that you never leave main */
		__RESET_WATCHDOG(); /* feeds the dog */
	}
}

//dentro de la funcion de la interrupcion hay que llamar a TicKEY que es un delay de 1mS
