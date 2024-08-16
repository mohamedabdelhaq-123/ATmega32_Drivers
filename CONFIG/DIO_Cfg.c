/*
 * DIO_Cfg.c
 *
 * Created: 12/7/2023 10:51:03 PM
 *  Author: DELL
 */ 

#include "StdTypes.h"
#include "DIO_Int.h"
#include "DIO_Cfg.h"


	/* OUTPUT,INFREE,INPULL*/ 
const DIO_PinStatus_t DIO_PinsStatusArray[TOTAL_PINS]={   //configrable
	infree,      /* Port A Pin 0 ADC0*/
	output,      /* Port A Pin 1 ADC1*/
	output,      /* Port A Pin 2 */
	output,      /* Port A Pin 3 */
	output,      /* Port A Pin 4 */
	output,      /* Port A Pin 5 */
	output,      /* Port A Pin 6 */
	infree,      /* Port A Pin 7 ADC7*/
	inpullup,      /* Port B Pin 0   / */
	inpullup,      /* Port B Pin 1   /*/
	inpullup,		 /* Port B Pin 2 / INT2*/
	inpullup,		 /* Port B Pin 3   /OC0*/
	output,		 /* Port B Pin 4 /ss*/
	output,		 /* Port B Pin 5 //mosi*/
	infree,		 /* Port B Pin 6 /miso*/
	output,		 /* Port B Pin 7 clk*/
	output,		 /* Port C Pin 0 */
	output,		 /* Port C Pin 1 */
	output,		 /* Port C Pin 2 */
	output,		 /* Port C Pin 3 */
	output,		 /* Port C Pin 4 */
	output,		 /* Port C Pin 5 */
	output,		 /* Port C Pin 6 */
	output,		 /* Port C Pin 7 */
	infree,		 /* Port D Pin 0 /RX */
	output,		 /* Port D Pin 1 / TX */
    inpullup,      /* Port D Pin 2 /INT0*/
	inpullup,      /* Port D Pin 3 / INT1 */
	output,		 /* Port D Pin 4  OC1B*/
	output,		 /* Port D Pin 5 OC1A*/
	output,		 /* Port D Pin 6 /   ICP*/
	output		 /* Port D Pin 7 */
};