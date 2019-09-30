#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

unsigned char *buffer_tx;
unsigned char cant_tx;
unsigned char status = 0;
unsigned char rx_byte;

char tx_buffer[] = "CHAU";

void InitSCI(void) {
	SCIBD = 52;
	SCIC1 = 0;
	SCIC2 = 0X0C;
	SCIC3 = 0;
	SCIC2_RIE = 1;
}
/*
 interrupt VectorNumber_Vscirx void SCI_RXisr(void){
 (void)SCIS1;
 rx_byte=SCID;
 
 }*/

void PutSCI(unsigned char *buffer, unsigned char cant) {

	while (SCIC2_TCIE)
		;
	buffer_tx = buffer;
	if (cant == 0) {
		while (*buffer++)
			cant_tx++;

	} else
		cant_tx = cant;
	SCIC2_TCIE = 1;

}

interrupt VectorNumber_Vscitx void SCI_TXisr(void) {
	(void) SCIS1;
	if (cant_tx) {
		SCID = *buffer_tx++;
		cant_tx--;
	} else
		SCIC2_TCIE = 0;

}

interrupt VectorNumber_Vscirx void SCI_RXisr(void) {
	(void) SCIS1;
	rx_byte = SCID;

}
/*
 if (rx_byte){
 
 rx_byte=0;
 }
 */

void main(void) {
	PTBD_PTBD4 = 0; //LED APAGADO
	PTBDD_PTBDD4 = 1;
	PTAD_PTAD0 = 0; //PULSADOR DE ENTRADA
	PTADD_PTADD0 = 0;
	//PTAPS_PTAPS0 = 1; //PTA0 COMO FLANCO DESCENDENTE
	//PTAES_PTAES0 = 0;

	InitSCI();
	EnableInterrupts
	;
	/* include your code here */
	PutSCI(tx_buffer, 0);

	for (;;) {
		if (rx_byte) {
			switch (status) {
			case 0:
				if (rx_byte == 'H') {
					status = 1;

				} else {
					status = 0;
				}
				break;
			case 1:
				if (rx_byte == 'O') {
					status = 2;

				} else {
					status = 0;
				}
				break;
			case 2:
				if (rx_byte == 'L') {
					status = 3;

				} else {
					status = 0;
				}
				break;
			case 3:
				if (rx_byte == 'A') {
					status = 0;
					PTBD_PTBD4 = 1;
				} else {
					status = 0;
				}
				break;

			}
			rx_byte=0;
		}

		if (PTAD_PTAD0 == 0) {

			PTBD_PTBD4 = 0;

		}

		__RESET_WATCHDOG(); /* feeds the dog */
	} /* loop forever */
	/* please make sure that you never leave main */
}

