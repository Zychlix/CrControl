#include <throttle.h>
#include "misc.h"

void car_controller_set_output_throttle(car_t* instance, uint16_t value )
{
    if(instance->controler_engaged == 0)
    {
        instance->throttle_raw_out = 0;
        return;
    }
    uint16_t dac_val;
    dac_val = value;//instance->zero_throttle_dac_offset + (value * (CAR_MAX_DAC_VAL - instance->zero_throttle_dac_offset)) / CAR_MAX_ADC_DAC_STEPS;

    instance->throttle_raw_out = dac_val;

    if(value >= CAR_MAX_ADC_DAC_STEPS )
    {

        dac_val = CAR_MAX_DAC_VAL;
    }



    return;
}

void car_controller_update_accelerator_raw_input(car_t * instance)
{
    uint16_t value;
    uint16_t adc_val;
    HAL_ADC_Start(instance->accelerator_adc_handler); //repair that
    adc_val = HAL_ADC_GetValue(instance->accelerator_adc_handler);
    value = adc_val;//((adc_val-instance->zero_accelerator_adc_offset)*CAR_MAX_ADC_DAC_STEPS)/instance->max_accelerator_adc_val; //Also for adc
    instance->accelerator_raw_in = value;

    return;
}

void car_throttle_handler(car_t * instance)
{
    car_controller_update_accelerator_raw_input(instance);
    car_calculate_accelerator_scaled_value(instance);
    instance->throttle_percent = instance->accelerator_percent;
    car_set_throttle_percent(instance);
    //car_controller_set_output_throttle(instance,instance->accelerator_raw_in);
    car_controller_flush_throttle(instance);

    return;
}

void car_controller_flush_throttle(car_t * instance)
{
    HAL_DAC_SetValue(instance->throttle_dac_handler, CAR_DAC_CHANNEL, 0, instance->throttle_raw_out);
    if(instance->throttle_raw_out>300)      //Set something reasonable
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