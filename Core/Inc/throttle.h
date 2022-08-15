#pragma once
#include <stdint.h>
#include "stm32l4xx_hal.h"
#include "stdbool.h"

#define CAR_MAX_DAC_VAL 4095
#define CAR_MAX_ADC_DAC_STEPS 4096
#define CAR_DAC_CHANNEL 0

#define ADC_DIVIDER     2
#define DAC_MULTIPLIER  2

#define ADC_ZERO_READING 430/ADC_DIVIDER
#define ADC_MAX_READING 2500 //2700

#define DAC_ZERO_OFFSET 0//0.25V
#define DAC_MAX_VALUE 4095
typedef struct car
{
    uint8_t passthrough_engaged;
    uint8_t controler_engaged;
    DAC_HandleTypeDef * throttle_dac_handler;
    ADC_HandleTypeDef * accelerator_adc_handler;


    uint16_t throttle_raw_out;
    uint16_t accelerator_raw_in;

    float accelerator_percent; // 0-100
    float throttle_percent;


    uint16_t * ecu_en_port;
    uint16_t ecu_en_pin;

} car_t;
void car_controller_init();

void car_controller_flush_throttle(car_t * instance);

void car_controller_set_output_throttle(car_t *instance, uint16_t value);

void car_controller_update_accelerator_raw_input(car_t * instance);

void car_calculate_accelerator_scaled_value(car_t * instance);  //Update acclerator percent value

void car_set_throttle_percent(car_t * instance);

void car_throttle_handler(car_t * instance);

void car_scale_values(car_t * instance);
