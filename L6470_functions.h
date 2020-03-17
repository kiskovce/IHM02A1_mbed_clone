#ifndef L6470_FUNCTIONS_H_
#define L6470_FUNCTIONS_H_

extern uint16_t get_speed(uint8_t mtr);
extern uint16_t get_max_speed(uint8_t mtr);
extern uint16_t get_min_speed(uint8_t mtr);
extern uint16_t get_accel(uint8_t mtr);
extern uint16_t get_deccel(uint8_t mtr);
extern uint8_t get_step_mode(uint8_t mtr);
extern uint8_t get_direction(uint8_t mtr);
extern uint16_t get_status(uint8_t mtr);
extern uint16_t get_parameter(uint8_t mtr, uint16_t parameter);
extern int16_t get_position(uint8_t mtr);
extern int16_t get_mark(uint8_t mtr);

extern void set_parameter(uint8_t mtr, uint16_t parameter, uint16_t value);
extern void set_home(uint8_t mtr);
extern void set_mark(uint8_t mtr);
extern void set_max_speed(uint8_t mtr, uint16_t max_speed);
extern void set_min_speed(uint8_t mtr, uint16_t min_speed);
extern void set_accel(uint8_t mtr, uint16_t accel);
extern void set_deccel(uint8_t mtr, uint16_t deccel);
extern void set_step_mode(uint8_t mtr, StepperMotor::step_mode_t step_mode);
extern void set_kval_run(uint8_t mtr, float kval_run);
extern void set_kval_hold(uint8_t mtr, float kval_hold);
extern void set_kval_accel(uint8_t mtr, float kval_accel);
extern void set_kval_decel(uint8_t mtr, float kval_decel);

#endif /* L6470_FUNCTIONS_H_ */

