/* IO.h*/
/* Includes ------------------------------------------------------------------*/
#ifndef __IO_H
#define __IO_H
#include "stm32f1xx_hal.h"

void ChairDownSet (void); // кнопка CHAIR DOWN / КРІСЛО ВНИЗ ввімкнута
void ChairDownReset (void); // кнопка CHAIR DOWN / КРІСЛО ВНИЗ вимкнута
void ChairUpSet (void); // кнопка CHAIR UP / КРІСЛО ВВЕРХ ввімкнута
void ChairUpReset (void); // кнопка CHAIR UP / КРІСЛО ВВЕРХ вимкнута
void BackrestUpSet (void); // кнопка BACKREST UP / СПИНКА ВВЕРХ ввімкнута
void BackrestUpReset (void); // кнопка BACKREST UP / СПИНКА ВВЕРХ вимкнута
void BackrestDownSet (void); // кнопка BACKREST DOWN / СПИНКА ВНИЗ ввімкнута
void BackrestDownReset (void); // кнопка BACKREST DOWN / СПИНКА ВНИЗ вимкнута
void SpittoonSet (void); // кнопка SPITTOON / СПЛЬОВУВАННЯ ввімкнута
void SpittoonReset (void); // кнопка SPITTOON / СПЛЬОВУВАННЯ вимкнута
void Memory1Set (void); // кнопка MEMORY 1 / ПРОГРАМА 1 ввімкнута
void Memory1Reset (void); // кнопка MEMORY 1 / ПРОГРАМА 1 вимкнута
void Memory2Set (void); // кнопка MEMORY 2 / ПРОГРАМА 2 ввімкнута
void Memory2Reset (void); // кнопка MEMORY 2 / ПРОГРАМА 2 вимкнута
void HomePositionSet (void); // кнопка HOME POSITION / 0 ПОЗИЦІЯ ввімкнута
void HomePositionReset (void); // кнопка HOME POSITION / 0 ПОЗИЦІЯ вимкнута
void Memory3Set (void); // кнопка MEMORY 3 / ПРОГРАМА 3 ввімкнута
void Memory3Reset (void); // кнопка MEMORY 3 / ПРОГРАМА 3 вимкнута

void LightONSet (void); // кнопка LIGHT ON / СВІТИЛЬНИК ввімкнута
void LightONReset (void); // кнопка LIGHT ON / СВІТИЛЬНИК вимкнута
void WaterFSet (void); // кнопка WATER F / НАПОВНЕННЯ СКЛЯНКИ ввімкнута
void WaterFReset (void); // кнопка WATER F / НАПОВНЕННЯ СКЛЯНКИ вимкнута
void WaterSSet (void); // кнопка WATER S / ЗМИВ ПЛЮВАЛЬНИЦІ ввімкнута
void WaterSReset (void); // кнопка WATER S / ЗМИВ ПЛЮВАЛЬНИЦІ вимкнута
void CoagSet (void); // Coag / Коагулятор ввімкнуто від педалі
void CoagReset (void); // Coag / Коагулятор вимкнуто від педалі

void OpenCollector1Set (void); // вихід Open Collector 1 ввімкнуто
void OpenCollector1Reset (void); // вихід Open Collector 1 вимкнуто
void OpenCollector2Set (void); // вихід Open Collector 2 ввімкнуто
void OpenCollector2Reset (void); // вихід Open Collector 2 вимкнуто

void StatusLEDSet (void); // ввімкнення світлодіода, який сигналізує про натискання кнопок керування кріслом
void StatusLEDReset (void); // вимкнення світлодіода, який сигналізує про натискання кнопок керування кріслом
void ErrorLEDSet (void); // ввімкнення світлодіода, який сигналізує про передачу або відсутність передачі даних по CAN
void ErrorLEDReset (void); // вимкнення світлодіода, який сигналізує про передачу або відсутність передачі даних по CAN
void CodeLEDSet (void); // ввімкнення світлодіода Code
void CodeLEDReset (void); // вимкнення світлодіода Code

uint8_t readButtonPedalONOFF (); // кнопка Pedal_ON/OFF / Педаль ВКЛ./ВИКЛ.
uint8_t readButtonCHIP (); // кнопка CHIP / ПРОДУВКА
uint8_t readButtonSPRAY (); // кнопка SPRAY / СПРЕЙ

uint8_t readButtonCoag (); // стан перемички для коагулятора 

#endif
