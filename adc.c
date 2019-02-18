 

#include "MKL25Z4.h"
# include "adc.h"
/* configuration of the input Analogue Signal for conversion in digital Signal 
AO (PTD5) input*/
void ADCx_init(PORT_Type *PORT,int ADCx_SHIFT,int PORT_SHIFT,int index)
{ 
	/*Enable Clock to the port*/
	 SIM->SCGC5 |= (0x1<<PORT_SHIFT); 
	/* analog input*/
	 PORT->PCR[index]=0;
	/*enbale clock to the ADCx desired*/
	 SIM->SCGC6 |= (0x1<<ADCx_SHIFT);  
   ADC0->SC1[0] = DIFF_SINGLE|ADC_SC1_ADCH(31); 
   ADC0->SC2 &= ~ADC_SC2_ADTRG_MASK ;   // ADTRG=0, software trigger
	 /* clock div by 4, long sample time, single ended 12 bit, bus clock*/ 
   ADC0->CFG1 =(0x1<<6 | 0x1<<4 |0x1<<2); 	
	/* select the B set of ADC input channels for PTD5 (SE6b)*/
	 ADC0->CFG2 |=(0x1<<ADC_CFG2_MUXSEL_SHIFT); //CFG2.MUXSEL=1, ADxxb channels are selected; 
	
	
}

short int readADC(short ChID) 
{
	short int result;     	
	
	ADC0->SC1[0] = ChID; //software triger conversion on channel 6, SE6B
	while(!(ADC0->SC1[0] & 0x80)) { } /* wait for conversion complete */
	result = ADC0->R[0];        /* read conversion result and clear COCO flag */
	return result;
}