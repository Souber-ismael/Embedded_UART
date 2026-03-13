
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "string.h"




void SystemClock_Config(void);





/* Buffer size for incoming UART data */
#define RX_BUF_SIZE 64

/* Global reception buffer and index */
static char    rx_buf[RX_BUF_SIZE];
static uint8_t rx_index = 0;

/**
 * @brief  Reads characters from UART until '\n' or '\r' is received.
 *         Stores the result in rx_buf as a null-terminated string.
 *         Ignores characters if buffer is full (overflow protection).
 */


void UART_ReadLine(void)
{
    uint8_t c;

    while (1)
    {
        /* Wait indefinitely for one byte */
        HAL_UART_Receive(&huart1, &c, 1, HAL_MAX_DELAY);

        /* End of line detected — terminate string and reset index */
        if (c == '\n' || c == '\r')
        {
            rx_buf[rx_index] = '\0';
            rx_index = 0;
            break;
        }

        /* Store character if buffer is not full */
        if (rx_index < RX_BUF_SIZE - 1)
        {
            rx_buf[rx_index++] = c;
        }
        /* else : buffer full — character discarded silently */
    }
}

/**
 * @brief  Parses and executes a command received over UART.
 * @param  cmd : null-terminated string containing the command.
 *
 * Supported commands :
 *   "led on"  -> turns LED on  (PA5)
 *   "led off" -> turns LED off (PA5)
 *   other     -> sends error message
 */
void ProcessCommand(char *cmd)
{
    /* Command : "led on" — turn LED on */
    if (strncmp(cmd, "led on", 6) == 0)
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
        HAL_UART_Transmit(&huart1, (uint8_t*)"LED ON\r\n", 8, 100);
        return;
    }

    /* Command : "led off" — turn LED off */
    if (strncmp(cmd, "led off", 7) == 0)
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
        HAL_UART_Transmit(&huart1, (uint8_t*)"LED OFF\r\n", 9, 100);
        return;
    }

    /* Unknown command */
    HAL_UART_Transmit(&huart1, (uint8_t*)"Error: unknown command\r\n", 23, 100);
}

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();

    while (1)
    {
        /* Wait for a complete line from Bluetooth terminal */
        UART_ReadLine();

        /* Execute the received command */
        ProcessCommand(rx_buf);
    }
}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};


  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }


  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}


void Error_Handler(void)
{

  __disable_irq();
  while (1)
  {
  }

}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
