#ifndef LDR_CONFIG_H_
#define LDR_CONFIG_H_
/* Which ADC channel / DIO pin the LDR voltage-divider output is connected to */
#define LDR_CHANNEL             0   /* ADC0 (PA0) */
#define LDR_PORT                DPORTA
#define LDR_PIN                 PIN0

/*
 * Calibration values (raw ADC, 0 -> 1023) measured on Proteus / hardware.
 * Wiring assumption: LDR from VCC to ADC pin, fixed resistor from ADC pin
 * to GND -> darkness gives a HIGH raw value. If your wiring is opposite,
 * swap the two values below.
 */
#define LDR_RAW_VALUE_DARK      900
#define LDR_RAW_VALUE_BRIGHT    100

#endif