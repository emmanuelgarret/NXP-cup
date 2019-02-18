#ifndef TPMX
  #define TMPX
#define FRQ_MCGFLLCLK 20971520 
#define prescalier_64 0x06
#define prescalier_1 0x0;
#define maxMod 0xFFFF;

void TPM0_init(short int initMODvalue,short int prescalier);
void TPM1_init(short int initMODvalue,short int prescalier);
void TPM0_DelayOnce(void);
void TPM1_DelayOnce(void);

#endif