#include <throttle.h>
#include "misc.h"

void car_controller_update_accelerator_raw_input(car_t * instance)
{
    uint16_t value;
    uint16_t adc_val;
    HAL_ADC_Start(instance->accelerator_adc_handler);
    adc_val = HAL_ADC_GetValue(instance->accelerator_adc_handler);
    value = adc_val;//((adc_val-instance->zero_accelerator_adc_offset)*CAR_MAX_ADC_DAC_STEPS)/instance->max_accelerator_adc_val; //Also for adc
    instance->accelerator_raw_in = value;
    car_calculate_accelerator_scaled_value(instance);

    return;
}

void car_throttle_handler(car_t * instance)
{
     //get current pedal throttle
    car_controller_update_accelerator_raw_input(instance);
    if(instance->state == CAR_STATUS_DIRECT)
    {
        instance->throttle_percent = instance->accelerator_percent; //set throttle value
    } else
    {

    }

    car_set_throttle_percent(instance);                         //turn throttle percent into dac value
    //car_controller_set_output_throttle(instance,instance->accelerator_raw_in);
    car_controller_execute_throttle(instance);                  //Set car throttle to set values

    return;
}

void car_controller_execute_throttle(car_t * instance)
{
    HAL_DAC_SetValue(instance->throttle_dac_handler, CAR_DAC_CHANNEL, 0, instance->throttle_raw_out);
    if(instance->throttle_percent>PEDAL_EN_TRSH)      //Set something reasonable was 10
    {
        HAL_GPIO_WritePin(instance->ecu_en_port,instance->ecu_en_pin,0);
        //HAL_GPIO_WritePin(PEDAL_EN_Port,PEDAL_EN_Pin,1);

    } else
    {
        HAL_GPIO_WritePin(instance->ecu_en_port,instance->ecu_en_pin,1);

    }

}

void car_calculate_accelerator_scaled_value(car_t * instance)
{
    int16_t value = instance->accelerator_raw_in ;
    value = 100 * ((float)value - ADC_ZERO_READING) / (ADC_MAX_READING - ADC_ZERO_READING);
    value = float_constraint(value,0,100);
    instance->accelerator_percent = value;
    return;
}

void car_set_throttle_percent(car_t * instance)
{
    int16_t throttle = DAC_ZERO_OFFSET + instance->throttle_percent*(DAC_MAX_VALUE-DAC_ZERO_OFFSET)/100;
    throttle = int_constraint(throttle,0,CAR_MAX_DAC_VAL);
    instance->throttle_raw_out = throttle;
}

void car_controller_enable_automatic_control(car_t * instance)
{
    instance->state = CAR_STATUS_CONTROLLED;
}

void car_controller_disable_automatic_control(car_t * instance)
{
    instance->state = CAR_STATUS_DIRECT ;
}

