#include "camread.h"
# include "TPMx.h"
#include "UART0_TxRx.h"

	void camInit(void)
{  
	/*Initial the IO port
	 SI (PTD7) output, CLK (PTE1) output*/
	
	SIM->SCGC5 |=( 0x1<<13); 
  /* enable clock to Port D, E */
	
    PORTD->PCR[7] = 0x100;     /* make PTD7 pin as GPIO */
    PTD->PDDR |= (0x1<<7);     /* make PTD7 as output pin */
	
    PORTE->PCR[1] = 0x100;     /* make PTE1 pin as GPIO */
    PTE->PDDR |= (0x1<<1);     /* make PTE1 as output pin */
	
	
	
	  CAM_SI_LOW;
	  CAM_CK_LOW;

}   
void cam_ReadImage(short int *imgData)
{  
	unsigned int i;
	
	 CAM_SI_HIGH;
	 TPM0_DelayOnce();
	 CAM_CK_HIGH;
	 TPM0_DelayOnce();
	 CAM_SI_LOW;
	 TPM0_DelayOnce();

	/* image sensor is red at the falling edge of CLK
	 howver, Fig. 11 suggests reading image at rising edge
	 read the 128 pixel image data
	*/
			CAM_CK_LOW;
		TPM0_DelayOnce();
		TPM0_DelayOnce();
		
	for (i=0;i<128;i++)
	{
		imgData[i]=(short int)readADC(6); 
		CAM_CK_HIGH;
		TPM0_DelayOnce();
		TPM0_DelayOnce();
		CAM_CK_LOW;
		TPM0_DelayOnce();
		TPM0_DelayOnce();
	}
	
	  CAM_CK_HIGH;
		TPM0_DelayOnce();
		TPM0_DelayOnce();
		CAM_CK_LOW;
	  TPM0_DelayOnce();
		TPM0_DelayOnce();
}   
		

		

