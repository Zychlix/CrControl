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
    HAL_Delay(1000);
    HAL_UART_Transmit(device->huart,ELM_COMMAND_ECHO_OFF,sizeof (ELM_COMMAND_ECHO_OFF),100);
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
    HAL_UART_Receive_IT(device->huart, device->rec_buf, size_data);
    HAL_UART_Transmit_IT(device->huart, command , size_command);
    device->rec_buf[size_data]='\n';
}

uint8_t elm_parse_speed(elm_t *device)
{
    if(device->rec_buf[0] != "N" && device->rec_buf[1] != "O") {    // just find 41, or something
        device->valid_reading = 1;
        char speed[2];
        speed[0] = device->rec_buf[6];
        speed[1] = device->rec_buf[7];

        device->current_speed = (uint8_t) strtol(speed, NULL, 16);
        return device->current_speed;
    }
    device->valid_reading = 0;
    return 0;

}