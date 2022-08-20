#include "PID.h"
#include "misc.h"

void pid_controller_init(pid_controller_t * pid)
{
    pid->p_coefficient = -10.f;
}

void pid_controller_evaluate(pid_controller_t * pid)
{
    if(pid->input_updated) {
        pid->input_last = pid->input_current;
        pid->input_updated = false;
    }
    float dx = pid->input_current - pid->input_last; //calculate input differential

    float proportional = pid->p_coefficient*(pid->input_current - pid->setpoint); //calculate proportional feedback

    pid->output = float_constraint(proportional,0,100);

}