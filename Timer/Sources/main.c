#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
volatile unsigned short blink;// volatile es para que el compilador no optimice la variable

void Init_Ports(void);
void InitMTIM(void);

void main(void) {
	Init_Ports();
	InitMTIM();
	EnableInterrupts
	;
	/* include your code here */

	for (;;) {
		if (blink > 999) {
			PTBD_PTBD4 = !PTBD_PTBD4;
			blink = 0;
			InitMTIM();//volvemos a configurar el timer a cero

		}

		__RESET_WATCHDOG(); /* feeds the dog */
	} /* loop forever */
	/* please make sure that you never leave main */
}
//funcion de configuracion de puertos
void Init_Ports(void) {
	PTAD = 0;
	PTBD = 0;
	PTADD_PTADD0 = 0;
	PTBDD_PTBDD4 = 1;

}
//funcion de configuracion de timer
void InitMTIM(void) {

	MTIMSC_TSTP = 1;//detenemos el contador
	MTIMSC_TRST = 1;//reiniciamos el contador
	MTIMCLK = 0X05;//configuramos el prescalador
	MTIMMOD = 250;//configuramos el modulo del timer
	MTIMSC_TOIE = 1;//habilitamos la interrupcion por timer
	MTIMSC_TSTP = 0;//arrancamos contador
}

interrupt VectorNumber_Vmtim void MTIMISR(void) {
	(void) MTIMSC;//leemos el registro MTIMSC es obligatorio para poder escribirlo, pero de esta manera no asignamos su valor a ninguna porcion de memoria
	MTIMSC_TOF = 0;// flag de overflow, lo bajamos para que entre de nuevo en la proxima interrupcion
	blink++;//incrementamos la variable
}

