#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
volatile signed char delay = -1; //

void Init_Ports(void);
void InitMTIM(void);
void HTIMisr(void);

void main(void) {
	Init_Ports();
	InitMTIM();
	EnableInterrupts
	;
	/*  */
	/* En este caso, aplicamos un antirrebote */
	for (;;) {
		if (delay == 0) {
			delay = -1;
			if (PTAD_PTAD0 == 0) {

				PTBD_PTBD4 = !PTBD_PTBD4;
			}
		}
		
		

		__RESET_WATCHDOG(); /* feeds the dog */
	} /* loop forever */
	/* please make sure that you never leave main */
}

void Init_Ports(void) {
	PTBD_PTBD4 = 0; //LED APAGADO
		PTBDD_PTBDD4 = 1;
		PTAD_PTAD0 = 0; //PULSADOR DE ENTRADA
		PTADD_PTADD0 = 0;
		PTAPS_PTAPS0 = 1; //PTA0 COMO FLANCO DESCENDENTE
		PTAES_PTAES0 = 0;
		PTASC_PTAACK = 1; //Borro el flag de interrupcion
		PTASC_PTAIE = 1; //Habilito interrupciones

}

void InitMTIM(void) {

	MTIMSC_TSTP = 1; //
	MTIMSC_TRST = 1; //
	MTIMCLK = 0X05; //
	MTIMMOD = 250; //
	MTIMSC_TOIE = 1; //
	MTIMSC_TSTP = 0; //
}


