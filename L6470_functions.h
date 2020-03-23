#ifndef L6470_FUNCTIONS_H_
#define L6470_FUNCTIONS_H_


extern uint16_t get_speed(L6470 **motors, uint8_t mtr);
extern uint16_t get_max_speed(L6470 **motors, uint8_t mtr);
extern uint16_t get_min_speed(L6470 **motors, uint8_t mtr);
extern uint16_t get_accel(L6470 **motors, uint8_t mtr);
extern uint16_t get_deccel(L6470 **motors, uint8_t mtr);
extern uint8_t get_step_mode(L6470 **motors, uint8_t mtr);
extern uint8_t get_direction(L6470 **motors, uint8_t mtr);
extern uint16_t get_status(L6470 **motors, uint8_t mtr);
extern uint16_t get_parameter(L6470 **motors, uint8_t mtr, uint16_t parameter);
extern int16_t get_position(L6470 **motors, uint8_t mtr);
extern int16_t get_mark(L6470 **motors, uint8_t mtr);

extern void set_parameter(L6470 **motors, uint8_t mtr, uint16_t parameter, uint16_t value);
extern void set_home(L6470 **motors, uint8_t mtr);
extern void set_mark(L6470 **motors, uint8_t mtr);
extern void set_max_speed(L6470 **motors, uint8_t mtr, uint16_t max_speed);
extern void set_min_speed(L6470 **motors, uint8_t mtr, uint16_t min_speed);
extern void set_accel(L6470 **motors, uint8_t mtr, uint16_t accel);
extern void set_deccel(L6470 **motors, uint8_t mtr, uint16_t deccel);
extern void set_step_mode(L6470 **motors, uint8_t mtr, StepperMotor::step_mode_t step_mode);
extern void set_kval_run(L6470 **motors, uint8_t mtr, float kval_run);
extern void set_kval_hold(L6470 **motors, uint8_t mtr, float kval_hold);
extern void set_kval_accel(L6470 **motors, uint8_t mtr, float kval_accel);
extern void set_kval_decel(L6470 **motors, uint8_t mtr, float kval_decel);

#endif /* L6470_FUNCTIONS_H_ */

