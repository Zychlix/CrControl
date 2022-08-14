#pragma once
#include <stdint.h>
#include "stm32l4xx_hal.h"
#include "stdbool.h"

#define CAR_MAX_DAC_VAL 4095
#define CAR_MAX_ADC_DAC_STEPS 4096
#define CAR_DAC_CHANNEL 0

typedef struct car
{
    uint8_t passthrough_engaged;
    uint8_t controler_engaged;
    DAC_HandleTypeDef * throttle_dac_handler;
    ADC_HandleTypeDef * accelerator_adc_handler;
    uint16_t zero_throttle_dac_offset;
    uint16_t max_throttle_dac_val;
    uint16_t zero_accelerator_adc_offset;
    uint16_t max_accelerator_adc_val;

    uint16_t throttle_out;
    uint16_t accelerator_in;

} car_t;
void car_controller_init();

void car_controller_flush_throttle(car_t * instance);

void car_controller_set_output_throttle(car_t *instance, uint16_t value);

void car_controller_get_accelerator(car_t * instance);

void car_throttle_handler(car_t * instance);
