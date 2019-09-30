#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

volatile unsigned short blink;
volatile unsigned short contador;
char debounce = 0;

void InitPorts(void);
void InitTimer(void);
interrupt VectorNumber_Vporta void PortaIsr(void);
interrupt VectorNumber_Vmtim void MTIMISR(void);

void BlinkOnOff(void);
void Debounce(void);

void main(void) {
	InitPorts();
	InitTimer();
	EnableInterrupts
	;
	/* include your code here */

	for (;;) {


		__RESET_WATCHDOG(); /* feeds the dog */
	} /* loop forever */
	/* please make sure that you never leave main */
}
/* INICIALIZACION DE PUERTOS */

void InitPorts(void) {
	/* */

	/* inicializacion de puertos */
	PTBD = 0; //PTB EN CERO
	PTBDD = 0xff; //PTB SALIDA
	PTAD_PTAD = 0x00; //PTA EN CERO
	PTADD_PTADD = 0x00; //PTA ENTRADA
	PTAES_PTAES = 0; //PTA PULL-UP
	PTAPS_PTAPS1 = 1; //PTA1 REALIZA LA INTERRUPCION
	PTASC_PTAACK = 1; // BORRO EL FLAG DE INTERRUPCION
	PTASC_PTAIE = 1; //HABILITO INTERRUPCION

}

/* CONFIGURACION DE TIMER*/

void InitTimer(void) {
	MTIMSC_TOF = 0; //Timer overflow (flagg)
	MTIMSC_TSTP = 1; //Timer Stop
	MTIMSC_TRST = 1; //Timer reset
	MTIMCLK = 0X05; //Seleccionamos el bus clk y configuramos el PS
	MTIMMOD = 250; //Registro de comparacion
	MTIMSC_TOIE = 1; //Habilitamos la int. Por timer
	MTIMSC_TSTP = 0; //Activamos el contador
}

/*INTERRUPCION POR PULSADOR */
interrupt VectorNumber_Vporta void PortaIsr(void) {
	PTASC_PTAACK = 1; //Borro el flag de interrupcion
	debounce = 1;//Activo la rutina antirebote
	contador=0;//Borro el buffer de contador

}

/*INTERRUPCION POR TIMER */
interrupt VectorNumber_Vmtim void MTIMISR(void) {
	(void) MTIMSC; //Leemos el registro, sino no nos deja escribir
	MTIMSC_TOF = 0; //bajamos el Flagg de Overflow
	
	contador = contador + 1;//Acumulamos vueltas de timmer en 1ms
/*intervalo antirebote */
	if (debounce > 0) {
		PTBD_PTBD4 = 0; //Apago led si está prendido
		if ((contador > 30)&&(PTAD_PTAD1==0)) {
			debounce = 0; //
			contador = 0; //
			blink = !blink;
		}
/*Blink!*/
	} else {
		if (blink) {
			if (contador > 250) {
				PTBD_PTBD4 = !PTBD_PTBD4;
				contador = 0;
			}

		}

	}

}
