#include "uart_bm_driver.h"

/**
 * @brief Sends one byte (blocking).
 *        Waits until TX register is empty (TXE flag).
 */
void UART_BM_SendByte(uint8_t byte)
{
    /* Wait until TX register is empty */
    while (!(USART1->SR & USART_SR_TXE));

    /* Write byte into data register */
    USART1->DR = byte;
}

/**
 * @brief Sends a string (blocking).
 *        Waits until last bit is physically sent (TC flag).
 */
void UART_BM_SendString(const char *str)
{
    while (*str)
        UART_BM_SendByte((uint8_t)*str++);

    /* Wait until last bit physically sent */
    while (!(USART1->SR & USART_SR_TC));
}

/**
 * @brief Receives one byte (blocking).
 *        Waits until data is available (RXNE flag).
 */
uint8_t UART_BM_ReceiveByte(void)
{
    /* Wait until data is available */
    while (!(USART1->SR & USART_SR_RXNE));

    /* Read and return received byte */
    return (uint8_t)(USART1->DR & 0xFF);
}

/**
 * @brief Reads a complete line until '\n' or '\r' (blocking).
 *        Stores result in buf as null-terminated string.
 */
void UART_BM_ReadLine(char *buf, uint8_t max)
{
    uint8_t idx = 0;
    uint8_t c   = 0;

    while (1)
    {
        c = UART_BM_ReceiveByte();

        /* End of line — terminate string */
        if (c == '\n' || c == '\r')
        {
            buf[idx] = '\0';
            break;
        }

        /* Store character if buffer not full */
        if (idx < max - 1)
            buf[idx++] = c;
    }
}
