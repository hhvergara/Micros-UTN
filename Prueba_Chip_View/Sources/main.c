#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

void Init_Ports(void);

void main(void) {
	Init_Ports();
	EnableInterrupts;
	/* include your code here */

	for (;;) {
		PTBD = 0x02+0x0F;

		__RESET_WATCHDOG(); /* feeds the dog */
	} /* loop forever */
	/* please make sure that you never leave main */
}

void Init_Ports(void) {
	PTAD=0;
	PTBD=0;
	PTADD = 0x00;
	PTBDD = 0xF0;

}
