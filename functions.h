#ifndef FUNCTIONS_H___
#define FUNCTIONS_H___

#include "XNucleoIHM02A1.h"

#define MPR_1 4                 /* Number of movements per revolution. */
#define STEPS_1 (400 * 128)     /* 1 revolution given a 400 steps motor configured at 1/128 microstep mode. */
#define STEPS_2 (STEPS_1 * 2)   /* 1 revolution given a 400 steps motor configured at 1/128 microstep mode. */
#define DELAY_1 1000            /* Delay in milliseconds. */
#define DELAY_2 2000            /* Delay in milliseconds. *///dd
#define DELAY_3 5000            /* Delay in milliseconds. */
#define STRING_SIZE                                                         20


extern L6470_init_t init[L6470DAISYCHAINSIZE];

extern L6470 **motors;

extern void set_home_xy(void);

#endif /* FUNCTIONS_H___ */
