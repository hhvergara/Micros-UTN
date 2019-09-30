#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "keyboard.h"

interrupt VectorNumber_Vporta void PortaIsr(void) {
	PTASC_PTAACK = 1; //Borro el flag de interrupcion
	PushKEY();
}
void InitPorts(void) {

	/* inicializacion de puertos */
	PTCDD = 0x01;
	PTBD = 0; //PTB EN CERO
	PTBDD = 0xfc; //PTB SALIDA
	PTAD_PTAD = 0x00; //PTA EN CERO
	PTADD_PTADD = 0x00; //PTA ENTRADA
	PTAES = 0; //PTA PULL-UP
	PTAPS = 0x0f; //PTA 0,1,2 REALIZA LA INTERRUPCION
	PTASC_PTAACK = 1; // BORRO EL FLAG DE INTERRUPCION
	PTASC_PTAIE = 1; //HABILITO INTERRUPCION

}

void InitTimer(void) {
	MTIMSC_TOF = 0; //Timer overflow (flagg)
	MTIMSC_TSTP = 1; //Timer Stop
	MTIMSC_TRST = 1; //Timer reset
	MTIMCLK = 0X05; //Seleccionamos el bus clk y configuramos el PS
	MTIMMOD = 250; //Registro de comparacion
	MTIMSC_TOIE = 1; //Habilitamos la int. Por timer
	MTIMSC_TSTP = 0; //Activamos el contador
}

interrupt VectorNumber_Vmtim void MTIMISR(void) {
	(void) MTIMSC; //Leemos el registro, sino no nos deja escribir
	MTIMSC_TOF = 0; //bajamos el Flagg de Overflow
	TicKEY();
}

void main(void) {
	InitPorts();
	InitTimer();
	EnableInterrupts
	;
	/* include your code here */

	for (;;) {
		GetKEY();
		if (key_press != NO_TECLA) {
			PTBD = key_press << 4;

		}

		__RESET_WATCHDOG(); /* feeds the dog */
	} /* loop forever */
	/* please make sure that you never leave main */
}

//dentro de la funcion de la interrupcion hay que llamar a TicKEY que es un delay de 1mS

