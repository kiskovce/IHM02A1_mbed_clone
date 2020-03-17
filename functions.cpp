#include "functions.h"
#include "mbed.h"
#include "DevSPI.h"
#include "XNucleoIHM02A1.h"
#include "variables.h"
#include "serial_function.h"

L6470_init_t init[L6470DAISYCHAINSIZE] = {
    {
        9.0,                           /* Motor supply voltage in V. */
        200,                           /* Min number of steps per revolution for the motor. */
        1.7,                           /* Max motor phase voltage in A. */
        3.06,                          /* Max motor phase voltage in V. */
        300.0,                         /* Motor initial speed [step/s]. */
        5000.0,                        /* Motor acceleration [step/s^2] (comment for infinite acceleration mode). */
        5000.0,                        /* Motor deceleration [step/s^2] (comment for infinite deceleration mode). */
        2000.0,                        /* Motor maximum speed [step/s]. */
        1.0,                           /* Motor minimum speed [step/s]. */
        602.7,                         /* Motor full-step speed threshold [step/s]. from this speed will  full step mode will applied*/
        3.06,                          /* Holding kval [V]. */
        3.06,                          /* Constant speed kval [V]. */
        3.06,                          /* Acceleration starting kval [V]. */
        3.06,                          /* Deceleration starting kval [V]. */
        61.52,                         /* Intersect speed for bemf compensation curve slope changing [step/s]. */
        392.1569e-6,                   /* Start slope [s/step]. */
        643.1372e-6,                   /* Acceleration final slope [s/step]. */
        643.1372e-6,                   /* Deceleration final slope [s/step]. */
        0,                             /* Thermal compensation factor (range [0, 15]). */
        3.06 * 1000 * 1.10,            /* Ocd threshold [ma] (range [375 ma, 6000 ma]). */
        3.06 * 1000 * 1.00,            /* Stall threshold [ma] (range [31.25 ma, 4000 ma]). */
        StepperMotor::STEP_MODE_FULL,  /* Step mode selection. */
        0xFF,                          /* Alarm conditions enable. */
        0x2E88                         /* Ic configuration. */
    },

    {
        9.0,                           /* Motor supply voltage in V. */
        200,                           /* Min number of steps per revolution for the motor. */
        1.7,                           /* Max motor phase voltage in A. */
        3.06,                          /* Max motor phase voltage in V. */
        300.0,                         /* Motor initial speed [step/s]. */
        5000.0,                        /* Motor acceleration [step/s^2] (comment for infinite acceleration mode). */
        5000.0,                        /* Motor deceleration [step/s^2] (comment for infinite deceleration mode). */
        2000.0,                        /* Motor maximum speed [step/s]. */
        1.0,                           /* Motor minimum speed [step/s]. */
        602.7,                         /* Motor full-step speed threshold [step/s]. */
        3.06,                          /* Holding kval [V]. */
        3.06,                          /* Constant speed kval [V]. */
        3.06,                          /* Acceleration starting kval [V]. */
        3.06,                          /* Deceleration starting kval [V]. */
        61.52,                         /* Intersect speed for bemf compensation curve slope changing [step/s]. */
        392.1569e-6,                   /* Start slope [s/step]. */
        643.1372e-6,                   /* Acceleration final slope [s/step]. */
        643.1372e-6,                   /* Deceleration final slope [s/step]. */
        0,                             /* Thermal compensation factor (range [0, 15]). */
        3.06 * 1000 * 1.10,            /* Ocd threshold [ma] (range [375 ma, 6000 ma]). */
        3.06 * 1000 * 1.00,            /* Stall threshold [ma] (range [31.25 ma, 4000 ma]). */
        StepperMotor::STEP_MODE_FULL,  /* Step mode selection. */
        0xFF,                          /* Alarm conditions enable. */
        0x2E88                         /* Ic configuration. */
    }
};

L6470 **motors = NULL;

void set_home_xy(void)
{
    motors[0]->set_home();
    motors[1]->set_home();
}
