#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
char count, buffer, status;
void Init_Ports(void);

void main(void) {
	
	//char estado = 0;
	char aux = 0;
	Init_Ports();
	EnableInterrupts
	;
	/* include your code here */

	for (;;) {

		if ((PTAD_PTAD1 == 0) && (aux == 0)) {
			//estado = !estado;
			aux = 1;
			count++; //Acumulamos los pulsos de entrada, si pasa de 15, resetea.
			if (count > 15) {
				count = 0;
			}
			status = PTBD & 0x0f; //copiamos el estado de la salida y Limpiamos la parte alta del registro.
			buffer = count << 4; //desplazamos el contenido del contador 4 digitos hacia la izquierda y lo guardamos en un buffer.
			status = status | buffer; //A la parte alta del registro de estado le agregamos el valor del buffer actual.
			PTBD = status;		//Le pasamos el estado actual a la salida.

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
	PTADD = 0x00;
	PTBDD = 0xF0;

}
