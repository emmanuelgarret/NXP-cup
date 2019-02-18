#include "MKL25Z4.h"
#include "stdio.h"
# include "TPMx.h"
#include "UART0_TxRx.h"
#include "camread.h"
#include "adc.h"


#define FRQ_MCGFLLCLK 20971520 

short int imageData[128];
	

int main (void)
{	 UART0_init();

    
    char buf [100];   // UART buffer 
    int n,i;            // number of characters in b2097uf to be sent
		int nImgRd; // number of image reading (how many times has the image been red) 
		short unsigned int initMODValue;
	 /* initialisation of UART0 at 5700 baud*/ 
	
	 /*initialisation of ADC0, for an analo input on the PTD5*/
		ADCx_init(PORTD,SIM_SCGC6_ADC0_SHIFT,SIM_SCGC5_PORTD_SHIFT ,5);
   
	 /*initialisation of the camera*/
	  camInit();
	
	  nImgRd=0;
	  initMODValue=0.5*(float)(FRQ_MCGFLLCLK)/1000000.0; //MOD value for 1us delay
	 /* initialisation of TPM0 for 1us delay , and TPM1 with 128 prescaler division */
	  TPM0_init(initMODValue,0x00);
	  TPM1_init(0xFFFF,0x07);
		/*test of the UART0*/
  
 	   while(1)
		 {
	  	 n=sprintf(buf, "nImgRd=%d\r\n", nImgRd);
		   sendStr(buf, n);	
			
		   nImgRd++;		
		   cam_ReadImage(imageData);
			 for (i=0;i<128;i++)
			  {	
					n = sprintf(buf, "%d ", imageData[i]); // convert integer value into ASCII
			    sendStr(buf, n);
			  }
			 sendStr("\r\n \r\n", 5);
			 for(int i=0;i<5;i++)
		    {
					TPM1_DelayOnce();
		    }

		}
		 
	
}
