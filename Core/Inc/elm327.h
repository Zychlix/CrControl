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

    int8_t status;
} elm_t;

int8_t elm_connect(elm_t * device);

int8_t elm_send_command(elm_t * device);
uint8_t elm_read_velocity(elm_t * device);

