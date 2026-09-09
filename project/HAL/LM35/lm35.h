//Author: Nour amr
#include<stdint.h>
#include"../../LIB/std_types.h"
#include"../../LIB/bit_math.h"
#define LM35_CHANNEL   0


#define VREF_MV        5000.0
#define ADC_RESOLUTION 1024.0
#define LM35_MV_PER_C  10.0


void lm35_init(void);
 f32 lm35_read_temp(void);
