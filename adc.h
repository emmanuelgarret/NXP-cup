#include "MKL25Z4.h"
#define DIFF_SINGLE 0x00
#define PORT_PCR_REG(base,index)                 ((base)->PCR[index])
/* that function let to initialise one ADCx and configure the pin
here we will use ADC0, and the pin PTD5 as the analog input
PORT is a pointer on the struct PORT_TYPE wich let to chose the PORT desired
PORT_SHIFT is an integer and let to enable the clock for the PORT desired and the represent the position's bit of the PORT in SCGC5
ADCx_SHIFT represent the position's bit of the right ADCx in SCGC6
*/
void ADCx_init(PORT_Type *PORT,int ADCx_SHIFT,int PORT_SHIFT,int pin);
/*that function let to read the value after conversion on ADC0*/
short int readADC(short ChID);
