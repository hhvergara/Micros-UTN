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


void PutSCI(unsigned char *buffer, unsigned char cant) {//0 para cadenas / 1 para direccion de la variable que querramos usar

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


