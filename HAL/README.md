# UART HAL Driver — STM32F103 Blue Pill

## Overview
Simple UART driver using STM32 HAL library.
Receives commands via Bluetooth (HC-05) and controls an LED.

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

| Command  | Result       | Response    |
|----------|--------------|-------------|
| led on   | LED turns on | "LED ON"    |
| led off  | LED turns off| "LED OFF"   |
| other    | Nothing      | "Error: unknown command" |

## Project structure
```
HAL/
├── Core/
│   ├── Src/
│   │   └── main.c        
│   └── Inc/
└── README.md
```

## Key functions
| Function | Description |
|----------|-------------|
| UART_ReadLine() | Reads a complete line until '\n' or '\r' |
| ProcessCommand() | Parses and executes the received command |

## What I learned
- HAL UART polling TX and RX
- Command parsing in C
- Handling '\r' and '\n' edge cases
- Buffer overflow protection

## Bluetooth app
Android : Serial Bluetooth Terminal
Baud rate : 9600

