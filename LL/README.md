# UART LL Driver

## What is LL ?
Low-Layer library — no HAL, direct register access via macros.
CubeMX generates only the init.
The TX/RX driver is written manually.

## Files
- uart_ll_driver.h / .c → custom UART driver
- main.c                → command parser + LED control

## Key functions
| Function | Description |
|----------|-------------|
| UART_LL_SendByte()   | Send one byte (blocking) |
| UART_LL_SendString() | Send a string (blocking) |
| UART_LL_ReceiveByte()| Receive one byte (blocking) |
| UART_LL_ReadLine()   | Receive complete line |

## Difference vs HAL
| HAL | LL |
|-----|----|
| HAL_UART_Transmit() | UART_LL_SendByte() |
| HAL_UART_Receive()  | UART_LL_ReceiveByte() |
| huart1 handle | direct USART1 access |
