#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

interrupt VectorNumber_Vporta void PortaIsr(void) {
	PTASC_PTAACK = 1; //Borro el flag de interrupcion
	PTBD_PTBD4 = PTBD_PTBD4 ^ 1; // Prendo el led

}






void main(void) {

	/* Configuramos los puertos*/
	PTBD_PTBD4 = 0; //LED APAGADO
	PTBDD_PTBDD4 = 1;
	PTAD_PTAD0 = 0; //PULSADOR DE ENTRADA
	PTADD_PTADD0 = 0;
	PTAPS_PTAPS0 = 1; //PTA0 COMO FLANCO DESCENDENTE
	PTAES_PTAES0 = 0;
	PTASC_PTAACK = 1; //Borro el flag de interrupcion
	PTASC_PTAIE = 1; //Habilito interrupciones
	EnableInterrupts
	;

	for (;;) {
		/*if (PTASC_PTAIF == 1) {
		 PTASC_PTAACK = 1;
		 PTBD_PTBD4 = PTBD_PTBD4 ^ 1;

		 }
		 */
		__RESET_WATCHDOG(); /* feeds the dog */
	} /* loop forever */
	/* please make sure that you never leave main */
}
