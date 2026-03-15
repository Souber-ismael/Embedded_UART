/*
 * uart_ll.h
 *
 *  Created on: Mar 15, 2026
 *      Author: admin
 */

#ifndef UART_LL_DRIVER_H
#define UART_LL_DRIVER_H

#include "stm32f1xx_ll_usart.h"
#include <stdint.h>

void UART_LL_SendByte(uint8_t byte);
void UART_LL_SendString(const char *str);
uint8_t UART_LL_ReceiveByte(void);
void UART_LL_ReadLine(char *buf, uint8_t max);

#endif

