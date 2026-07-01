
/* IO.c*/
/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "stm32f1xx_it.h"

/* Керування станом кнопок стоматологічного крісла по  прийнятому від пульта стану кнопок*/

void ChairDownSet (void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET); // кнопка CHAIR DOWN / КРІСЛО ВНИЗ ввімкнута
}

void ChairDownReset (void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET); // кнопка CHAIR DOWN / КРІСЛО ВНИЗ вимкнута
}

void ChairUpSet (void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET); // кнопка CHAIR UP / КРІСЛО ВВЕРХ ввімкнута
}

void ChairUpReset (void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET); // кнопка CHAIR UP / КРІСЛО ВВЕРХ вимкнута
}

void BackrestUpSet (void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET); // кнопка BACKREST UP / СПИНКА ВВЕРХ ввімкнута
}

void BackrestUpReset (void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET); // кнопка BACKREST UP / СПИНКА ВВЕРХ вимкнута
}

void BackrestDownSet (void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET); // кнопка BACKREST DOWN / СПИНКА ВНИЗ ввімкнута
}

void BackrestDownReset (void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET); // кнопка BACKREST DOWN / СПИНКА ВНИЗ вимкнута
}

void SpittoonSet (void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET); // кнопка SPITTOON / СПЛЬОВУВАННЯ ввімкнута
}

void SpittoonReset (void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET); // кнопка SPITTOON / СПЛЬОВУВАННЯ вимкнута
}

void Memory1Set (void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET); // кнопка MEMORY 1 / ПРОГРАМА 1 ввімкнута
}

void Memory1Reset (void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET); // кнопка MEMORY 1 / ПРОГРАМА 1 вимкнута
}

void Memory2Set (void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET); // кнопка MEMORY 2 / ПРОГРАМА 2 ввімкнута
}

void Memory2Reset (void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET); // кнопка MEMORY 2 / ПРОГРАМА 2 вимкнута
}

void HomePositionSet (void) // кнопка HOME POSITION / 0 ПОЗИЦІЯ ввімкнута
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET); // кнопка HOME POSITION / 0 ПОЗИЦІЯ ввімкнута
}

void HomePositionReset (void) // кнопка HOME POSITION / 0 ПОЗИЦІЯ вимкнута
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET); // кнопка HOME POSITION / 0 ПОЗИЦІЯ вимкнута
}

void Memory3Set (void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET); // кнопка MEMORY 3 / ПРОГРАМА 3 ввімкнута
}

void Memory3Reset (void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET); // кнопка MEMORY 3 / ПРОГРАМА 3 вимкнута
}

/* Керування станом кнопок WATER F, WATER S та LIGHT ON
для контролеру гідроблоку А120М*/

void LightONSet (void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET); // кнопка LIGHT ON / СВІТИЛЬНИК ввімкнута
}

void LightONReset (void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET); // кнопка LIGHT ON / СВІТИЛЬНИК вимкнута
}

void WaterFSet (void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_SET); // кнопка WATER F / НАПОВНЕННЯ СКЛЯНКИ ввімкнута
}

void WaterFReset (void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET); // кнопка WATER F / НАПОВНЕННЯ СКЛЯНКИ вимкнута
}

void WaterSSet (void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_SET); // кнопка WATER S / ЗМИВ ПЛЮВАЛЬНИЦІ ввімкнута
}

void WaterSReset (void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_RESET); // кнопка WATER S / ЗМИВ ПЛЮВАЛЬНИЦІ вимкнута
}

void CoagSet (void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET); // Coag / Коагулятор ввімкнуто від педалі
}

void CoagReset (void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET); // Coag / Коагулятор вимкнуто від педалі
}

/* Додаткові виходи мікроконтролера Open Collector*/

void OpenCollector1Set (void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET); // вихід Open Collector 1 ввімкнуто
}

void OpenCollector1Reset (void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET); // вихід Open Collector 1 вимкнуто
}

void OpenCollector2Set (void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET); // вихід Open Collector 2 ввімкнуто
}

void OpenCollector2Reset (void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET); // вихід Open Collector 2 вимкнуто
}

/* Керування роботою світлодіодів, які сигналізують про стан передачі даних та про
виконання програми для мікроконтролера - кнопки написнуті*/

void StatusLEDSet (void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET); // ввімкнення світлодіода, який сигналізує про натискання кнопок керування кріслом
}

void StatusLEDReset (void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET); // вимкнення світлодіода, який сигналізує про натискання кнопок керування кріслом
}

void ErrorLEDSet (void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET); // ввімкнення світлодіода, який сигналізує про передачу або відсутність передачі даних по CAN
}

void ErrorLEDReset (void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET); // вимкнення світлодіода, який сигналізує про передачу або відсутність передачі даних по CAN
}

void CodeLEDSet (void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET); // ввімкнення світлодіода Code
}

void CodeLEDReset (void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET); // вимкнення світлодіода Code
}

/* Робота з кнопками Pedal_ON/OFF, CHIP та SPRAY*/
uint8_t readButtonPedalONOFF () // стан кнопки Pedal ON/OFF / Педаль ВКЛ./ВИКЛ.
{
uint8_t stateButtonPedalONOFF = 0;
	if (HAL_GPIO_ReadPin (GPIOD, GPIO_PIN_2) == 0)
	{
	stateButtonPedalONOFF = 1;
	}
	else
	stateButtonPedalONOFF = 0;
	return stateButtonPedalONOFF;
}

uint8_t readButtonCHIP () // стан кнопки CHIP / ПРОДУВКА
{
uint8_t stateButtonCHIP = 0;
	if (HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_3) == 0)
	{
	stateButtonCHIP= 1;
	}
	else
	stateButtonCHIP = 0;
	return stateButtonCHIP;
}

uint8_t readButtonSPRAY () // стан кнопки SPRAY / СПРЕЙ
{
uint8_t stateButtonSPRAY = 0;
	if (HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_4) == 0)
	{
	stateButtonSPRAY= 1;
	}
	else
	stateButtonSPRAY = 0;
	return stateButtonSPRAY;
}

/* Робота з перемичкою для ініціалізації коагулятора*/
uint8_t readButtonCoag () // стан перемички для коагулятора 
{
uint8_t stateButtonPedalONOFF = 0;
	if (HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_0) == 0)
	{
	stateButtonPedalONOFF = 1;
	}
	else
	stateButtonPedalONOFF = 0;
	return stateButtonPedalONOFF;
}
