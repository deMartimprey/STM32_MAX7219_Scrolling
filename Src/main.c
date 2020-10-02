#include "main.h"

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

uint8_t led = 0;

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  HAL_Init();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  SystemClock_Config();
  MX_GPIO_Init();
  init_matrix();
  max_init();
  blank_all_matrice();
  while (1)
    {
      demo_matrix();
      HAL_Delay(400);
      letter_come_and_left((uint8_t *)"BON ");
      letter_come_and_left2((uint8_t *)"ANNIV");
      letter_come_and_left((uint8_t *)"ABCD");
      letter_come_and_left((uint8_t *)"EFGH");
    }
}

void letter_come_and_left(uint8_t *letters)
{
  uint8_t dl = 20;
  uint8_t slide = 20;
  uint8_t* matrix_tab_0[5] = {0, };
  uint8_t* matrix_tab_1[4] = {0, };
  uint8_t* matrix_tab_2[4] = {0, };
  uint8_t* matrix_tab_3[4] = {0, };

  uint8_t letter0_0[8] = {0, };
  uint8_t letter1_0[8] = {0, };
  uint8_t letter2_0[8] = {0, };
  uint8_t letter3_0[8] = {0, };
  uint8_t letter4_0[8] = {0, };

  uint8_t letter0_1[8] = {0, };
  uint8_t letter1_1[8] = {0, };
  uint8_t letter2_1[8] = {0, };
  uint8_t letter3_1[8] = {0, };

  uint8_t letter0_2[8] = {0, };
  uint8_t letter1_2[8] = {0, };
  uint8_t letter2_2[8] = {0, };
  uint8_t letter3_2[8] = {0, };

  uint8_t letter0_3[8] = {0, };
  uint8_t letter1_3[8] = {0, };
  uint8_t letter2_3[8] = {0, };
  uint8_t letter3_3[8] = {0, };

  matrix_tab_0[0] = letter0_0;
  matrix_tab_0[1] = letter1_0;
  matrix_tab_0[2] = letter2_0;
  matrix_tab_0[3] = letter3_0;
  matrix_tab_0[4] = letter4_0;

  matrix_tab_1[0] = letter0_1;
  matrix_tab_1[1] = letter1_1;
  matrix_tab_1[2] = letter2_1;
  matrix_tab_1[3] = letter3_1;

  matrix_tab_2[0] = letter0_2;
  matrix_tab_2[1] = letter1_2;
  matrix_tab_2[2] = letter2_2;
  matrix_tab_2[3] = letter3_2;

  matrix_tab_3[0] = letter0_3;
  matrix_tab_3[1] = letter1_3;
  matrix_tab_3[2] = letter2_3;
  matrix_tab_3[3] = letter3_3;

  uint8_t matrix_str_0[6] = "     ";
  uint8_t matrix_str_1[5] = "    ";
  uint8_t matrix_str_2[5] = "    ";
  uint8_t matrix_str_3[5] = "    ";

  matrix_str_0[3] = letters[3];
  matrix_str_1[0] = letters[2];
  matrix_str_2[0] = letters[1];
  matrix_str_3[1] = letters[0];

  fill_matrix_tab((uint8_t**)matrix_tab_0, (uint8_t*)&matrix_str_0, 5);
  fill_matrix_tab((uint8_t**)matrix_tab_1, (uint8_t*)&matrix_str_1, 4);
  fill_matrix_tab((uint8_t**)matrix_tab_2, (uint8_t*)&matrix_str_2, 4);
  fill_matrix_tab((uint8_t**)matrix_tab_3, (uint8_t*)&matrix_str_3, 4);
  
  turn_matrix_tab((uint8_t**)matrix_tab_0, 4);
  inverse_matrix_tab((uint8_t**)matrix_tab_0, 4);

  turn_matrix_tab((uint8_t**)matrix_tab_1, 4);
  inverse_matrix_tab((uint8_t**)matrix_tab_1, 4);

  turn_matrix_tab((uint8_t**)matrix_tab_2, 4);
  inverse_matrix_tab((uint8_t**)matrix_tab_2, 4);

  turn_matrix_tab((uint8_t**)matrix_tab_3, 4);
  inverse_matrix_tab((uint8_t**)matrix_tab_3, 4);

  HAL_Delay(dl);
  for (int i = 0; i < 8; i++)
    {
      decal_1_left((uint8_t**)matrix_tab_0, 4);
      print_matrix_tab((uint8_t**)matrix_tab_0, 3);
      HAL_Delay(slide);
    }
  for (int i = 0; i < 8 * 3; i++)
    {
      decal_1_left((uint8_t**)matrix_tab_0, 4);
      print_matrix_tab((uint8_t**)matrix_tab_0, 4);
      HAL_Delay(slide);
    }
  HAL_Delay(dl);
  for (int i = 0; i < 8 * 2; i++)
    {
      decal_1_left((uint8_t**)matrix_tab_1, 4);
      print_matrix_tab((uint8_t**)matrix_tab_1, 3);
      HAL_Delay(slide);
    }
  HAL_Delay(dl);
  for (int i = 0; i < 8 * 1; i++)
    {
      decal_1_left((uint8_t**)matrix_tab_2, 4);
      print_matrix_tab((uint8_t**)matrix_tab_2, 2);
      HAL_Delay(slide);
    }
  HAL_Delay(dl);
  for (int i = 0; i < 8 * 1; i++)
    {
      decal_1_left((uint8_t**)matrix_tab_3, 2);
      print_matrix_tab_first((uint8_t**)matrix_tab_3, 2);
      HAL_Delay(slide);
    }
  HAL_Delay(300);
  for (int i = 0; i < 8 * 1; i++)
    {
      decal_1_right((uint8_t**)matrix_tab_3, 4);
      print_matrix_tab_first((uint8_t**)matrix_tab_3, 2);
      HAL_Delay(slide);
    }
  HAL_Delay(dl);
  for (int i = 0; i < 8 * 2; i++)
    {
      decal_1_right((uint8_t**)matrix_tab_2, 4);
      print_matrix_tab((uint8_t**)matrix_tab_2, 2);
      HAL_Delay(slide);
    }
  for (int i = 0; i < 8 * 3; i++)
    {
      decal_1_right((uint8_t**)matrix_tab_1, 4);
      print_matrix_tab((uint8_t**)matrix_tab_1, 3);
      HAL_Delay(slide);
    }
  HAL_Delay(dl);
  for (int i = 0; i < 8 * 4; i++)
    {
      decal_1_right((uint8_t**)matrix_tab_0, 5);
      print_matrix_tab((uint8_t**)matrix_tab_0, 4);
      HAL_Delay(slide);
    }
  HAL_Delay(dl);
}

void letter_come_and_left2(uint8_t *letters)
{
  uint8_t dl = 20;
  uint8_t slide = 20;
  uint8_t* matrix_tab_0[5] = {0, };
  uint8_t* matrix_tab_1[4] = {0, };
  uint8_t* matrix_tab_2[4] = {0, };
  uint8_t* matrix_tab_3[4] = {0, };
  uint8_t* matrix_tab_3_bis[4] = {0, };

  uint8_t letter0_0[8] = {0, };
  uint8_t letter1_0[8] = {0, };
  uint8_t letter2_0[8] = {0, };
  uint8_t letter3_0[8] = {0, };
  uint8_t letter4_0[8] = {0, };

  uint8_t letter0_1[8] = {0, };
  uint8_t letter1_1[8] = {0, };
  uint8_t letter2_1[8] = {0, };
  uint8_t letter3_1[8] = {0, };

  uint8_t letter0_2[8] = {0, };
  uint8_t letter1_2[8] = {0, };
  uint8_t letter2_2[8] = {0, };
  uint8_t letter3_2[8] = {0, };

  uint8_t letter0_3[8] = {0, };
  uint8_t letter1_3[8] = {0, };
  uint8_t letter2_3[8] = {0, };
  uint8_t letter3_3[8] = {0, };

  uint8_t letter0_3_bis[8] = {0, };
  uint8_t letter1_3_bis[8] = {0, };
  uint8_t letter2_3_bis[8] = {0, };
  uint8_t letter3_3_bis[8] = {0, };

  matrix_tab_0[0] = letter0_0;
  matrix_tab_0[1] = letter1_0;
  matrix_tab_0[2] = letter2_0;
  matrix_tab_0[3] = letter3_0;
  matrix_tab_0[4] = letter4_0;

  matrix_tab_1[0] = letter0_1;
  matrix_tab_1[1] = letter1_1;
  matrix_tab_1[2] = letter2_1;
  matrix_tab_1[3] = letter3_1;

  matrix_tab_2[0] = letter0_2;
  matrix_tab_2[1] = letter1_2;
  matrix_tab_2[2] = letter2_2;
  matrix_tab_2[3] = letter3_2;

  matrix_tab_3[0] = letter0_3;
  matrix_tab_3[1] = letter1_3;
  matrix_tab_3[2] = letter2_3;
  matrix_tab_3[3] = letter3_3;

  matrix_tab_3_bis[0] = letter0_3_bis;
  matrix_tab_3_bis[1] = letter1_3_bis;
  matrix_tab_3_bis[2] = letter2_3_bis;
  matrix_tab_3_bis[3] = letter3_3_bis;

  uint8_t matrix_str_0[6] = "     ";
  uint8_t matrix_str_1[5] = "    ";
  uint8_t matrix_str_2[5] = "    ";
  uint8_t matrix_str_3[5] = "    ";
  uint8_t matrix_str_3_bis[5] = "    ";

  matrix_str_0[3] = letters[4];
  matrix_str_1[0] = letters[3];
  matrix_str_2[0] = letters[2];
  matrix_str_3[1] = letters[0];
  matrix_str_3_bis[1] = letters[1];

  fill_matrix_tab((uint8_t**)matrix_tab_0, (uint8_t*)&matrix_str_0, 5);
  fill_matrix_tab((uint8_t**)matrix_tab_1, (uint8_t*)&matrix_str_1, 4);
  fill_matrix_tab((uint8_t**)matrix_tab_2, (uint8_t*)&matrix_str_2, 4);
  fill_matrix_tab((uint8_t**)matrix_tab_3, (uint8_t*)&matrix_str_3, 4);
  fill_matrix_tab((uint8_t**)matrix_tab_3_bis, (uint8_t*)&matrix_str_3_bis, 4);
  
  turn_matrix_tab((uint8_t**)matrix_tab_0, 4);
  inverse_matrix_tab((uint8_t**)matrix_tab_0, 4);

  turn_matrix_tab((uint8_t**)matrix_tab_1, 4);
  inverse_matrix_tab((uint8_t**)matrix_tab_1, 4);

  turn_matrix_tab((uint8_t**)matrix_tab_2, 4);
  inverse_matrix_tab((uint8_t**)matrix_tab_2, 4);

  turn_matrix_tab((uint8_t**)matrix_tab_3, 4);
  inverse_matrix_tab((uint8_t**)matrix_tab_3, 4);

  turn_matrix_tab((uint8_t**)matrix_tab_3_bis, 4);
  inverse_matrix_tab((uint8_t**)matrix_tab_3_bis, 4);

  HAL_Delay(dl);
  for (int i = 0; i < 8; i++)
    {
      decal_1_left((uint8_t**)matrix_tab_0, 4);
      print_matrix_tab((uint8_t**)matrix_tab_0, 3);
      HAL_Delay(slide);
    }
  for (int i = 0; i < 8 * 3; i++)
    {
      decal_1_left((uint8_t**)matrix_tab_0, 4);
      print_matrix_tab((uint8_t**)matrix_tab_0, 4);
      HAL_Delay(slide);
    }
  HAL_Delay(dl);
  for (int i = 0; i < 8 * 2; i++)
    {
      decal_1_left((uint8_t**)matrix_tab_1, 4);
      print_matrix_tab((uint8_t**)matrix_tab_1, 3);
      HAL_Delay(slide);
    }
  HAL_Delay(dl);
  for (int i = 0; i < 8 * 1; i++)
    {
      decal_1_left((uint8_t**)matrix_tab_2, 4);
      print_matrix_tab((uint8_t**)matrix_tab_2, 2);
      HAL_Delay(slide);
    }
  HAL_Delay(dl);
  for (int i = 0; i < 8 * 1; i++)
    {
      decal_1_left((uint8_t**)matrix_tab_3_bis, 2);
      print_matrix_tab_first((uint8_t**)matrix_tab_3_bis, 2);
      HAL_Delay(slide);
    }
  HAL_Delay(300);
  decal_1_right((uint8_t**)matrix_tab_3_bis, 2);
  print_matrix_tab_first((uint8_t**)matrix_tab_3_bis, 2);
  HAL_Delay(300);
  decal_1_left((uint8_t**)matrix_tab_3_bis, 2);
  print_matrix_tab_first((uint8_t**)matrix_tab_3_bis, 2);
  HAL_Delay(300);
  decal_1_right((uint8_t**)matrix_tab_3_bis, 2);
  print_matrix_tab_first((uint8_t**)matrix_tab_3_bis, 2);
  HAL_Delay(300);
  decal_1_left((uint8_t**)matrix_tab_3_bis, 2);
  print_matrix_tab_first((uint8_t**)matrix_tab_3_bis, 2);
  HAL_Delay(300);  
  HAL_Delay(100);
  decal_1_right((uint8_t**)matrix_tab_3_bis, 2);
  print_matrix_tab_first((uint8_t**)matrix_tab_3_bis, 2);
  HAL_Delay(100);
  decal_1_right((uint8_t**)matrix_tab_3_bis, 2);
  print_matrix_tab_first((uint8_t**)matrix_tab_3_bis, 2);
  HAL_Delay(100);
  decal_1_right((uint8_t**)matrix_tab_3_bis, 2);
  print_matrix_tab_first((uint8_t**)matrix_tab_3_bis, 2);
  HAL_Delay(100);
  decal_1_right((uint8_t**)matrix_tab_3_bis, 2);
  print_matrix_tab_first((uint8_t**)matrix_tab_3_bis, 2);
  HAL_Delay(100);
  decal_1_right((uint8_t**)matrix_tab_3_bis, 2);
  print_matrix_tab_first((uint8_t**)matrix_tab_3_bis, 2);
  HAL_Delay(100);
  decal_1_right((uint8_t**)matrix_tab_3_bis, 2);
  print_matrix_tab_first((uint8_t**)matrix_tab_3_bis, 2);
  for (int i = 0; i < 8 * 1; i++)
    {
      decal_1_left((uint8_t**)matrix_tab_3, 2);
      print_matrix_tab_first((uint8_t**)matrix_tab_3, 2);
      HAL_Delay(slide);
    }
  HAL_Delay(700);
  for (int i = 0; i < 8 * 1; i++)
    {
      decal_1_right((uint8_t**)matrix_tab_3, 4);
      print_matrix_tab_first((uint8_t**)matrix_tab_3, 2);
      HAL_Delay(slide);
    }
  HAL_Delay(dl);
  for (int i = 0; i < 8 * 2; i++)
    {
      decal_1_right((uint8_t**)matrix_tab_2, 4);
      print_matrix_tab((uint8_t**)matrix_tab_2, 2);
      HAL_Delay(slide);
    }
  for (int i = 0; i < 8 * 3; i++)
    {
      decal_1_right((uint8_t**)matrix_tab_1, 4);
      print_matrix_tab((uint8_t**)matrix_tab_1, 3);
      HAL_Delay(slide);
    }
  HAL_Delay(dl);
  for (int i = 0; i < 8 * 4; i++)
    {
      decal_1_right((uint8_t**)matrix_tab_0, 5);
      print_matrix_tab((uint8_t**)matrix_tab_0, 4);
      HAL_Delay(slide);
    }
  HAL_Delay(dl);
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
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

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
}
#endif /* USE_FULL_ASSERT */
