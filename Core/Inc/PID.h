#pragma once
#include "stdbool.h"

typedef struct pid_controller
{
    float input_current;
    float input_last;
    float setpoint;
    float dt;
    bool input_updated;     //set 1 on every x update

    float output;

    float p_coefficient;
    float i_coefficient;
    float d_coefficient;
    float integrated;
} pid_controller_t;

void pid_controller_init(pid_controller_t * pid);

void pid_controller_evaluate(pid_controller_t * pid);