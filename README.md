# STM32 UART Driver — HAL / LL / Bare Metal

## Hardware
- STM32F103 Blue Pill
- HC-05 Bluetooth Module
- 1 LED on PA5

## Wiring
HC-05 TX → PA10 (USART1 RX)
HC-05 RX → PA9  (USART1 TX)
GND      → GND

## Projects
| Version | Description |
|---------|-------------|
| HAL     | UART using STM32 HAL library |
| LL      | UART using Low-Layer library |
| BM      | UART bare metal (coming soon) |

## How it works
Send a command from your phone via Bluetooth :
- "led on"  → LED turns on
- "led off" → LED turns off
- other     → Error message
