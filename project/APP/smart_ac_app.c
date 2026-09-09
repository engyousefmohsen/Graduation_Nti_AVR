#include "../../MCAL/ADC/ADC_Interface.h"
#include"../../LIB/std_types.h"
#include "lm35.h"
void lm35_init(void) {
    //it just need adc initialization which is done so it is here for structure only
}


f32 lm35_read_temp(void) {
    u16 adc_value = ADC_Read(LM35_CHANNEL);
    f32 voltage = (adc_value * VREF_MV) / ADC_RESOLUTION;
    f32 temp_c = voltage / LM35_MV_PER_C;
    return temp_c;
}
