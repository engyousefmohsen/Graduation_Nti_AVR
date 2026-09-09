//Author: Nour amr
#ifndef SMART_AC_H
#define SMART_AC_H




#define TEMP_LOW_ON     25.0
#define TEMP_LOW_OFF    23.0
#define TEMP_HIGH_ON    30.0
#define TEMP_HIGH_OFF   28.0

#define FAN_SPEED_OFF     0
#define FAN_SPEED_MEDIUM  128
#define FAN_SPEED_HIGH    255

void smart_ac_init(void);
void smart_ac_update(void);

#endif
