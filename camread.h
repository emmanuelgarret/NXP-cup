#ifndef CAMREAD
  #define CAMREAD

#include "MKL25Z4.h"
#include "stdio.h"
#define DIFF_SINGLE 0x00
#define DIFF_DIFFERENTIAL (0x01<<5)
/*we defined the output ( Enabel an Clock signal)of the card thus input of the camera*/
#define CAM_SI_HIGH PTD->PSOR=(0x01<<7); 
#define CAM_SI_LOW PTD->PCOR=(0x01<<7);  

#define CAM_CK_HIGH PTE->PSOR=(0x01<<1); 
#define CAM_CK_LOW PTE->PCOR=(0x01<<1);  
void camInit(void);
void cam_ReadImage(short int *imgData);
short int readADC(short ChID);

#endif