# UART Bare Metal Driver — STM32F103 Blue Pill

## Overview
Same project as HAL and LL versions but using direct register access.
No HAL, no LL — only USART1->SR and USART1->DR.

## Hardware
- STM32F103 Blue Pill
- HC-05 Bluetooth Module
- 1 LED on PA5

## Wiring
| HC-05 | STM32 |
|-------|-------|
| TX    | PA10 (USART1 RX) |
| RX    | PA9  (USART1 TX) |
| GND   | GND  |
| VCC   | 5V   |

## How it works
| Command  | Result        | Response                |
|----------|---------------|-------------------------|
| led on   | LED turns on  | "LED ON"                |
| led off  | LED turns off | "LED OFF"               |
| other    | Nothing       | "Error: unknown command"|

## Project structure
```
BM/
├── Core/
│   ├── Src/
│   │   ├── main.c
│   │   └── uart_bm_driver.c
│   └── Inc/
│       └── uart_bm_driver.h
└── README.md
```

## Key functions
| Function | Description |
|----------|-------------|
| UART_BM_SendByte()    | Sends one byte — polls TXE bit in SR    |
| UART_BM_SendString()  | Sends a string — waits for TC bit in SR |
| UART_BM_ReceiveByte() | Reads one byte — polls RXNE bit in SR   |
| UART_BM_ReadLine()    | Reads complete line until '\n' or '\r'  |

## Registers used
| Register | Description |
|----------|-------------|
| USART1->SR | Status register — TXE, TC, RXNE flags |
| USART1->DR | Data register — read and write data   |

## Key flags
| Flag | Bit | Meaning |
|------|-----|---------|
| TXE  | 7   | TX register empty — ready to send    |
| TC   | 6   | Transmission complete — line is free |
| RXNE | 5   | RX register not empty — data arrived |

## Difference vs LL
| LL | Bare Metal |
|----|------------|
| LL_USART_IsActiveFlag_TXE() | USART1->SR & (1U << 7) |
| LL_USART_TransmitData8()    | USART1->DR = byte      |
| LL_USART_IsActiveFlag_RXNE()| USART1->SR & (1U << 5) |
| LL_USART_ReceiveData8()     | (uint8_t)USART1->DR    |

## What I learned
- Direct register access without any library
- USART1->SR and USART1->DR manipulation
- Difference between TXE and TC flags
- LL macros are just wrappers around register access

## Bluetooth app
Android : Serial Bluetooth Terminal
Baud rate : 9600
