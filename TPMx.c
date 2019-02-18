#include "MKL25Z4.h"
#define FRQ_MCGFLLCLK 20971520 
#define prescalier_64 0x06
#define prescalier_1 0x0;
/*Timer which let to set the freqnecy of the Clock send to the camera at 1Mhz*/
void TPM0_init(short int initMODvalue,short int prescalier)
{
	
	SIM->SCGC6 |= (0x01<<24);/* 0x0100000 enale clk to TPM0*/
	SIM->SOPT2 |=(0x01<<24); /* 0x01000000, use MCGFLLCLK as timer counter clk*/

	TPM0->SC = 0; /*diable timer when configuring*/
	TPM0->MOD = initMODvalue;
	TPM0->SC|=0x80; /* clear TOF*/
	TPM0->SC|=prescalier;
	// TPM0->SC|=0x08; // enable timer free-rnning mode
}
/*timer which set the Integration Time */
void TPM1_init(short int initMODvalue,short int prescalier)
{
	
	SIM->SCGC6 |= (0x01<<25);//(0x01<<24); // 0x01000000;, enale clk to TPM0
	SIM->SOPT2 |=(0x01<<24);//(0x01<<16); // 0x01000000, use MCGFLLCLK as timer counter clk

	TPM1->SC = 0; // diable timer when configuring
	// TPM0->MOD = 0xFFFF; // by default, set the 16-bit modulo value to maximum
	                    // thus results in maximum delay
	TPM1->MOD = initMODvalue;
	TPM1->SC|=0x80; // clear TOF
	TPM1->SC|=prescalier;//0x06;
	// TPM0->SC|=0x08; // enable timer free-rnning mode
}


void TPM0_DelayOnce(void)
{
	TPM0->SC|=0x80; // clear TOF
	TPM0->SC|=0x08; // enable timer free-rnning mode
	while((TPM0->SC & 0x80) == 0) { } // wait until the TOF is set
	TPM0->SC = 0; // diable timer when configuring
}


void TPM1_DelayOnce(void)
{
	TPM1->SC|=0x80; // clear TOF
	TPM1->SC|=0x08; // enable timer free-rnning mode
	while((TPM1->SC & 0x80) == 0) { } // wait until the TOF is set
	TPM1->SC = 0; // diable timer when configuring
}
