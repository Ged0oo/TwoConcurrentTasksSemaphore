/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "LCD_interface.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */



/* USER CODE END Variables */
/* Definitions for LCD_WRITE_TASK1 */
osThreadId_t LCD_WRITE_TASK1Handle;
const osThreadAttr_t LCD_WRITE_TASK1_attributes = {
  .name = "LCD_WRITE_TASK1",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for LCD_WRITE_TASK2 */
osThreadId_t LCD_WRITE_TASK2Handle;
const osThreadAttr_t LCD_WRITE_TASK2_attributes = {
  .name = "LCD_WRITE_TASK2",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for myBinarySem01 */
osSemaphoreId_t myBinarySem01Handle;
const osSemaphoreAttr_t myBinarySem01_attributes = {
  .name = "myBinarySem01"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void taskLCD1(void *argument);
void taskLCD2(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of myBinarySem01 */
  myBinarySem01Handle = osSemaphoreNew(1, 1, &myBinarySem01_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of LCD_WRITE_TASK1 */
  LCD_WRITE_TASK1Handle = osThreadNew(taskLCD1, NULL, &LCD_WRITE_TASK1_attributes);

  /* creation of LCD_WRITE_TASK2 */
  LCD_WRITE_TASK2Handle = osThreadNew(taskLCD2, NULL, &LCD_WRITE_TASK2_attributes);

  /* USER CODE BEGIN RTOS_THREADS */



  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_taskLCD1 */
/**
  * @brief  Function implementing the LCD_WRITE_TASK1 thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_taskLCD1 */
void taskLCD1(void *argument)
{
  /* USER CODE BEGIN taskLCD1 */
	uint16_t counter = 1;
	TickType_t taskPeriod = pdMS_TO_TICKS(500);
	TickType_t lastWakeTime = xTaskGetTickCount();
  /* Infinite loop */
  for(;;)
  {
	  osSemaphoreAcquire(myBinarySem01Handle, portMAX_DELAY);

	  //lcd_4bit_send_command(&lcd_1, _LCD_CLEAR);
	  lcd_4bit_send_string_pos(&lcd_1, 1, 1, "Task 1 => ");
	  LCD_WriteNumber(counter);

	  osSemaphoreRelease(myBinarySem01Handle);

	  vTaskDelayUntil(&lastWakeTime, taskPeriod);
	  counter++;
  }
  /* USER CODE END taskLCD1 */
}

/* USER CODE BEGIN Header_taskLCD2 */
/**
* @brief Function implementing the LCD_WRITE_TASK_ thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_taskLCD2 */
void taskLCD2(void *argument)
{
  /* USER CODE BEGIN taskLCD2 */
	uint16_t counter = 1;
	TickType_t taskPeriod = pdMS_TO_TICKS(1000);
	TickType_t lastWakeTime = xTaskGetTickCount();
  /* Infinite loop */
  for(;;)
  {
	  osSemaphoreAcquire(myBinarySem01Handle, portMAX_DELAY);

	  //lcd_4bit_send_command(&lcd_1, _LCD_CLEAR);
	  lcd_4bit_send_string_pos(&lcd_1, 2, 1, "Task 2 => ");
	  LCD_WriteNumber(counter);

	  osSemaphoreRelease(myBinarySem01Handle);

	  vTaskDelayUntil(&lastWakeTime, taskPeriod);
	  counter++;
  }
  /* USER CODE END taskLCD2 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
/* Task to be created. */


/* USER CODE END Application */

