#include <elm327.h>

#include "stdlib.h"
int8_t elm_connect(elm_t * device)
{
    if(device->huart == 0)
    {
        return -1;
    }

    char rx_buffer[64];
    HAL_UART_Transmit(device->huart,ELM_COMMAND_RESET,sizeof (ELM_COMMAND_RESET),100);
    HAL_UART_Receive(device->huart, rx_buffer, 5, 2000);

    device->status =1;
    return 0;

}

int8_t elm_send_command(elm_t * device);
uint8_t elm_read_velocity(elm_t * device)
{
    char rx_buffer[32];
    HAL_UART_Receive(device->huart, rx_buffer,20,300);
}


void elm_send_query(elm_t *device, char * command, uint16_t size_command, uint16_t size_data)
{
    HAL_UART_Receive_IT(&device->huart, device->rec_buf, size_data);
    HAL_UART_Transmit_IT(&device->huart, command , size_command);
}

uint8_t elm_parse_speed(elm_t *device)
{
    char speed[2];
    speed[0] = device->rec_buf[9];
    speed[1] = device->rec_buf[10];

    return (uint8_t)strtol(speed,NULL,16);

}