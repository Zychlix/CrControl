#include <throttle.h>

void car_controller_set_output_throttle(car_t* instance, uint16_t value )
{
    if(instance->controler_engaged == 0)
    {
        instance->throttle_out = 0;
        return;
    }
    uint16_t dac_val;
    dac_val = instance->zero_throttle_dac_offset + (value * (CAR_MAX_DAC_VAL - instance->zero_throttle_dac_offset)) / CAR_MAX_ADC_DAC_STEPS;

    instance->throttle_out = dac_val;

    if(value >= CAR_MAX_ADC_DAC_STEPS )
    {

        dac_val = CAR_MAX_DAC_VAL;
    }



    return;
}

void car_controller_get_accelerator(car_t * instance)
{
    uint16_t value;
    uint16_t adc_val;
    HAL_ADC_Start(instance->accelerator_adc_handler); //repair that
    adc_val = HAL_ADC_GetValue(instance->accelerator_adc_handler);
    value = ((adc_val-instance->zero_accelerator_adc_offset)*CAR_MAX_ADC_DAC_STEPS)/instance->max_accelerator_adc_val; //Also for adc
    instance->accelerator_in = value;

    return;
}

void car_throttle_handler(car_t * instance)
{
    car_controller_get_accelerator(instance);
    instance->throttle_out = instance->accelerator_in;
    car_controller_set_output_throttle(instance,instance->accelerator_in);
    car_controller_flush_throttle(instance);

    return;
}

void car_controller_flush_throttle(car_t * instance)
{
    HAL_DAC_SetValue(instance->throttle_dac_handler, CAR_DAC_CHANNEL, 0, instance->throttle_out);

}