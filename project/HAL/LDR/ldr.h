/*
* LDR.H 
*/ 

#ifndef LDR_H_
#define LDR_H_

/* Initializes the underlying ADC peripheral */
void LDR_voidInit(void);

/* Returns the raw ADC reading (0 -> 1023) */
u16 LDR_u16GetRawValue(void);

/*
 * Returns the ambient LIGHT level as a percentage :
 *   0   = full darkness
 *   100 = full brightness
 */
u8 LDR_u8GetLightPercentage(void);

#endif /* LDR_H_ */
