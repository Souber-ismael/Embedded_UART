#include "uart_ll.h"

/**
 * @brief Sends one byte (blocking)
 */
void UART_LL_SendByte(uint8_t byte)
{
    while (!LL_USART_IsActiveFlag_TXE(USART1));
    LL_USART_TransmitData8(USART1, byte);
}

/**
 * @brief Sends a string (blocking)
 */
void UART_LL_SendString(const char *str)
{
    while (*str)
        UART_LL_SendByte((uint8_t)*str++);

    /* Wait until last bit physically sent */
    while (!LL_USART_IsActiveFlag_TC(USART1));
}

/**
 * @brief Receives one byte (blocking)
 */
uint8_t UART_LL_ReceiveByte(void)
{
    while (!LL_USART_IsActiveFlag_RXNE(USART1));
    return LL_USART_ReceiveData8(USART1);
}

/**
 * @brief Reads a complete line until '\n' or '\r' (blocking)
 *        Stores result in buf as null-terminated string
 */
void UART_LL_ReadLine(char *buf, uint8_t max)
{
    uint8_t idx = 0;
    uint8_t c   = 0;

    while (1)
    {
        c = UART_LL_ReceiveByte();

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
