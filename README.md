# STM32 UART Driver — Three Abstraction Levels

## Overview
Same project implemented in three different ways :
Control an LED via Bluetooth (HC-05) using UART commands.

Objective : understand what happens under the hood at each level.

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
Send a command from your phone via Bluetooth terminal :

| Command  | Result        | Response                |
|----------|---------------|-------------------------|
| led on   | LED turns on  | "LED ON"                |
| led off  | LED turns off | "LED OFF"               |
| other    | Nothing       | "Error: unknown command"|

## Project structure
```
STM32_UART/
├── HAL/         → using STM32 HAL library
├── LL/          → using Low-Layer library
├── BM/          → bare metal (direct register access)
└── README.md
```

## The three levels explained
| Level | Description | What you write |
|-------|-------------|----------------|
| HAL | High abstraction | Just call HAL functions |
| LL  | Low abstraction  | Check flags manually, no handle |
| BM  | No abstraction   | Direct USART1->SR and USART1->DR |

## Key difference in code
```c
/* HAL */
HAL_UART_Transmit(&huart1, (uint8_t*)"hello", 5, 100);

/* LL */
while (!LL_USART_IsActiveFlag_TXE(USART1));
LL_USART_TransmitData8(USART1, 'h');

/* Bare Metal */
while (!(USART1->SR & (1U << 7)));
USART1->DR = 'h';
```

## What I learned
- UART protocol — frame, baud rate, sampling
- HAL polling TX and RX
- LL driver written from scratch
- Bare metal register access (SR, DR)
- Command parsing in C
- Handling '\r' and '\n' edge cases
- Buffer overflow protection
- Why sprintf and strcpy are dangerous in firmware

## Bluetooth app
Android : Serial Bluetooth Terminal
Baud rate : 9600

