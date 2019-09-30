#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

void Init_Ports(void);

void main(void) {
	char estado = 0;
	char aux = 0;
	Init_Ports();

	EnableInterrupts
	;
	/* include your code here */

	for (;;) {
		if ((PTAD_PTAD1 == 0) && (aux == 0)) {
			estado = !estado;
			aux = 1;
			PTBD_PTBD4 = estado;
		}
		if ((PTAD_PTAD1 == 1) && (aux == 1)) {
			aux = 0;

		}

		__RESET_WATCHDOG(); /* feeds the dog */
	} /* loop forever */
	/* please make sure that you never leave main */
}

void Init_Ports(void) {
	PTAD = 0;
	PTBD = 0;
	PTADD_PTADD0 = 0;
	PTBDD_PTBDD4 = 1;

}
