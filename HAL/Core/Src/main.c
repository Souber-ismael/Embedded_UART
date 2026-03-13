
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "string.h"

#define RX_BUF_SIZE 32
char rx_buf[RX_BUF_SIZE];
uint8_t rx_index = 0;


void SystemClock_Config(void);






void UART_ReadLine(){

	uint8_t c;

	while(1){
	HAL_UART_Transmit(&huart1, &c, 1, HAL_MAX_DELAY);

	if(c == '\n' || c == '\r' ){
		rx_buf[rx_index]= '\0';
		rx_index = 0;
		break;
	 }
	else{
		if(rx_index < RX_BUF_SIZE -1 ){
			rx_buf[rx_index]=c;
			rx_index++;
		}
	}
	}
}

void ProcessCommand(void)
{
    // led on
    if (strcmp(cmd,"led on")==0)
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
        char msg[] = "LED ON\r\n";
        HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), 100);
        return;
    }

    // led off
    else if (strcmp(cmd,"led off")==0)
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
        char msg[] = "LED OFF\r\n";
        HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), 100);
        return;
    }

    else {
    	 HAL_UART_Transmit(&huart1, (uint8_t*)"Erreur\r\n", 1, 100);
    	 return;
    }


}



int main(void)
{

  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();




  while(1)
  {
        // lire une commande
	      UART_ReadLine();

	      // parser et agir
	      ProcessCommand();
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
