#pragma once
#include <stdint.h>
#include <commands_ELM.h>
#include <stm32l4xx.h>
/*
 * Michal Zychla 15.08.2022
 * ELM327
 * This library allows you to communicate with your car via ELM327
 */

typedef struct elm
{

    UART_HandleTypeDef * huart;
    UART_HandleTypeDef * debug_huart;

    uint8_t valid_reading;

    uint8_t current_speed;

    uint16_t current_rpm;
    uint32_t velocity_read_interval;
    uint32_t velocity_read_timestamp;

    volatile char * rec_buf;

    int8_t status;
} elm_t;

int8_t elm_connect(elm_t * device);

void elm_send_query(elm_t *device ,char * command, uint16_t size_command, uint16_t size_data);

uint8_t elm_parse_speed(elm_t *device);

int8_t elm_send_command(elm_t * device);
uint8_t elm_read_velocity(elm_t * device);

