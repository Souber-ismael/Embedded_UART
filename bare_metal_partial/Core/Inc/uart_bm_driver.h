/*
 * uart_bm_driver.h
 *
 *  Created on: Mar 15, 2026
 *      Author: admin
 */

#ifndef UART_BM_DRIVER_H
#define UART_BM_DRIVER_H

#include "stm32f1xx.h"
#include <stdint.h>

/* USART1 Status Register flags */
#define USART_SR_TXE    (1U << 7)   /* TX register empty    */
#define USART_SR_TC     (1U << 6)   /* Transmission complete */
#define USART_SR_RXNE   (1U << 5)   /* RX register not empty */

void UART_BM_SendByte(uint8_t byte);
void UART_BM_SendString(const char *str);
uint8_t UART_BM_ReceiveByte(void);
void UART_BM_ReadLine(char *buf, uint8_t max);

#endif
