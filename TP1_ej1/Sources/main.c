#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

void Init_Ports(void);

void main(void) {
	Init_Ports();

	EnableInterrupts
	;
	/* include your code here */

	for (;;) {
		if (PTAD_PTAD0 == 0) 
			PTBD_PTBD4 = 1;
		else
			PTBD_PTBD4 = 0;
		if (PTAD_PTAD1 == 0) 
			PTBD_PTBD5 = 1;
		else
			PTBD_PTBD5 = 0;
		if (PTAD_PTAD2 == 0) 
			PTBD_PTBD6 = 1;
		else
			PTBD_PTBD6 = 0;
		if (PTAD_PTAD3 == 0) 
			PTBD_PTBD7 = 1;
		else
			PTBD_PTBD7 = 0;
				
		__RESET_WATCHDOG(); /* feeds the dog */
	} /* loop forever */
	/* please make sure that you never leave main */
}

void Init_Ports(void) {
	PTADD = 0;
	PTBDD = 1;

}
