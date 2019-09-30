#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

void PWMInit(void) {
	TPM1SC = 0x0b; //0b00001011
	TPM1MOD = 10000; //Periodo
	TPM1C0SC = 0x28; //0b00011000
	TPM1C0V = 5000; //Dutty
}

void main(void) {
	PWMInit();
	EnableInterrupts
	;
	/* include your code here */

	for (;;) {
		__RESET_WATCHDOG(); /* feeds the dog */
	} /* loop forever */
	/* please make sure that you never leave main */
}

void InitSCI(void) {
	SCIBD = 52;
	SCIC1 = 0;
	SCIC2 = 0X0C;
	SCIC3 = 0;
	SCIC2_RIE = 1;

}

interrupt VectorNumber_Vscirx void SCI_RXisr(void){
	(void)SCIS1;
	rx_byte=SCID;
	
}

if (rx_byte){
	
	rx_byte=0;
}

