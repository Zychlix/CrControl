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

#define PEDAL_EN_TRSH 6

typedef enum car_state
{
    CAR_STATUS_DIRECT,
    CAR_STATUS_CONTROLLED,
} car_state_t;

typedef struct car
{
    car_state_t state;
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
//void car_controller_init();

void car_controller_execute_throttle(car_t * instance);     //Set throttle position to one given by throttle_percent

void car_controller_update_accelerator_raw_input(car_t * instance);     //Read input throttle position and update the structure, calculate percent input

void car_calculate_accelerator_scaled_value(car_t * instance);  //Update accelerator percent value

void car_set_throttle_percent(car_t * instance);    // Sets raw out calculated from throttle percent

void car_throttle_handler(car_t * instance);

void car_controller_enable_automatic_control(car_t * instance);

void car_controller_disable_automatic_control(car_t * instance);
