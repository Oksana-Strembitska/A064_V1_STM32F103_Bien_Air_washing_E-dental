/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : STM32F103_CAN_chair_A064_V1_Bien_Air+pedal.c
  * @brief          : Program for chair board AEGA 5.139.064 with Bien Air
											platform and CAN pedal
  ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "io.h" // порти вводу / виводу
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
ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;

CAN_HandleTypeDef hcan;

/* USER CODE BEGIN PV */
uint32_t dataBienAirBuffTx [255] = {0}; // дані про стан кнопок пульта для chair
uint32_t dataBienAirBuffHolder [255] = {0}; // стан тримачів для платформи Bien Air

void decodeBienAirBuffRx (uint32_t *dataBienAirBuffRx);	// робота з прийнятим повідомленням data_Bien_Air
void decodeBienAirBuffHolder (uint32_t *dataBienAirBuffHolder); // робота зі станом інструментів на платфлормі Bien Air

CAN_TxHeaderTypeDef TxHeader; // вихідний буфер CAN_Tx
CAN_RxHeaderTypeDef RxHeader; // вхідний буфер CAN_Rx

uint32_t dataBienAirBuffRx [255] = {0}; // дані про стан кнопок пульта для chair

uint32_t TxMailBox = 0; // Mailbox для відправки даних по CAN
uint8_t canRxBuffer [255] = {0}; // буфер для прийому даних по CAN
uint8_t canTxBuffer [255] = {0}; // буфер для передачі даних по CAN

uint8_t canTxPedal [255] = {0};

uint8_t len = 0; // лічильник прийнятих даних по CAN
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_ADC2_Init(void);
static void MX_CAN_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint8_t data_chair = 0; // дані про функції крісла HOME POSITION, CHAIR UP, CHAIR DOWN, BACKREST UP, BACKREST DOWN, SPITTON, MEMORY1, MEMORY2
uint8_t data_light_water_chair = 0; //  дані про функції крісла MEMORY3, світильник LIGHT, плювальницю WATER F, WATER S

uint8_t data_washing = 0; // промивка інструменту ON/OFF

uint8_t washing = 0; // прапорець по включенню / виключенню промивки

uint8_t state_masage = 0; // прапорець, який сигналізує, що дані по CAN отримані правильні

static uint8_t holder_state = 0;
uint8_t hol_state = 0;
uint8_t flag = 0;
uint8_t stop = 0;

uint32_t tim_washing = 0;
uint32_t tim_washing_add = 0;

uint8_t pedal_state = 0;
uint8_t pedal_state_prev = 0;
uint8_t button_BienAir = 0;

uint8_t state_CAN = 0; // прапорець, який сигналізує про наявність зв'язку по CAN
uint8_t data_CAN_NOT_OK = 0; // прапорець, який сигналізує про те, що на протязі 3с не було даних по CAN
uint32_t time_state_CAN = 0; // таймер для відліку часу роботи CAN
	
uint32_t tim_data_chair_ok = 0; // таймер, який використовується для відліку часу роботи із світлодіодом	
uint32_t time_error_LED = 0; // таймер, який використовується для мигання свтлодіодом при помилці по CAN - в буфері data_chair_answer crc заповнено 0
uint32_t tim_CAN_error = 0; //таймер для відліку 3с на початку роботи системи
uint32_t timeRemove = 0; // відлік часу для обнулення вхідного буфера по CAN
uint32_t timCanRxDataBienAirNOTOK = 0; // таймер для роботи із світлодіодами при помилці по CAN
uint32_t timeStatusCAN = 0; // таймер, який відповідає за погашення світлодіода Status при наявності помилки по CAN
	
	
uint8_t button_push_pedal = 0;
uint8_t button_push_pedal_ = 0;
uint8_t button_push_pedal_sent = 0;
uint8_t button_push_CHIP = 0;
uint8_t button_push_CHIP_sent = 0;
	
uint8_t button_push_SPRAY = 0;
uint8_t stateButtSPRAY = 0;
	
uint8_t button_push_pedal_sent_prev = 0;
	
uint32_t 	tim_pedal_transmit = 0;
uint32_t time_button = 0;
uint32_t time_pedal_on = 0;
	
uint16_t adcResult = 0; // дані, які отримано з АЦП 12-бітного
uint8_t dataResultL = 0; // дані, які приведено до АЦП 8-бітного
uint8_t dataResultM = 0; // дані, які приведено до АЦП 8-бітного

uint32_t adcResultdiv = 0;
uint32_t adcResultmn = 0;

uint32_t time_state_CAN_ = 0;

uint8_t button_push_pedal_state = 0;
uint8_t prev_state_pedal_on_off  = 0;

uint8_t start_instrument = 0;

uint8_t all_inst_off = 0;
uint8_t stop_washing = 0;

/* Робота з повідомленням про поточний стан кнопок data_Bien_Air*/
/* Робота з повідомленням про поточний стан кнопок data_Bien_Air*/
void decodeBienAirBuffRx (uint32_t *dataBienAirBuffRx) // робота з прийнятим повідомленням data_Bien_Air
{	
	// Перезапис даних із буфера data_Bien_Air у змінні
	data_chair = dataBienAirBuffRx [2]; // перша частина субіндексу посилки для chair
	data_light_water_chair = dataBienAirBuffRx [3]; // друга частина субіндексу посилки для chair
	data_washing = dataBienAirBuffRx [5]; //  функція промивки ON/OFF

		/*Формування стану виходів мікроконтролера для керування стоматологічним кріслом*/
		/*Стан кнопки HOME POSITION / 0 ПОЗИЦІЯ*/
		if (data_washing == 0x20)
		{
			washing = 1; // промивка ON
		}
		else if (data_washing == 0x00)
		{
			washing = 0; // промивка OFF
		}			
}

void decodeBienAirBuffHolder (uint32_t *dataBienAirBuffHolder) // робота з прийнятим повідомленням data_Bien_Air
{
	holder_state = dataBienAirBuffHolder [5];
	all_inst_off = dataBienAirBuffHolder [4];
	
	if (all_inst_off == 0xFF)
	{
	  stop_washing = 1;
	}
	else if (all_inst_off != 0xFF)
	{
		stop_washing = 0;
	}	
	
	if (holder_state == 0x01)
	{
	  hol_state = 1;
	}
	else if (holder_state == 0x81)
	{
		hol_state = 2;
	}		
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_CAN_Init();
  /* USER CODE BEGIN 2 */

 // Ініціалізація CAN
 HAL_CAN_Init (&hcan);
 
 	// Фільтр по прийому Rx для CAN
 CAN_FilterTypeDef canFilterConfig;
 canFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
 canFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
 canFilterConfig.FilterIdHigh = 0x0000;
 canFilterConfig.FilterIdLow = 0x0000;
 canFilterConfig.FilterMaskIdHigh = 0x0000<<5;
 canFilterConfig.FilterMaskIdLow = 0x0000;
 canFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
 canFilterConfig.FilterActivation = ENABLE;
 canFilterConfig.FilterBank = 1;
 HAL_CAN_ConfigFilter (&hcan, &canFilterConfig);
 HAL_CAN_Start (&hcan);
 
 // Rx вхідний буфер
 RxHeader.StdId = 0x00;
 RxHeader.RTR = CAN_RTR_DATA;
 RxHeader.IDE = CAN_ID_STD;
 RxHeader.DLC = 8;
 HAL_Delay(10);	
 
 HAL_Delay (2000);
 
 HAL_ADC_Start (&hadc1); // старт АЦП
 HAL_ADC_PollForConversion (&hadc1, 100); // АЦП запускає перетворення даних кожні 100мс
 HAL_ADC_Stop (&hadc1);

 start_instrument = 1;
 
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {	
		/* Прийом даних data_Bien_Air*/
		HAL_CAN_GetRxMessage (&hcan, CAN_RX_FIFO0, &RxHeader, canRxBuffer); // прийом даних
	  if (RxHeader.StdId == 0x28B) // прийом буфера data_Bien_Air
	  {
	    for (len=0; len<8; len++)
			dataBienAirBuffRx [len] = canRxBuffer [len];  // перезапис даних із mailbox у буфер dataBienAirBuffRx, якщо це посилка з потрібним Id
 			decodeBienAirBuffRx (dataBienAirBuffRx); // декодування вхідної посилки
			state_CAN = 1;
	  }
		if (RxHeader.StdId == 0x018A)
		{
			for (len=0; len<8; len++)
			dataBienAirBuffHolder [len] = canRxBuffer [len];
			decodeBienAirBuffHolder (dataBienAirBuffHolder);
		}
		

if (HAL_GetTick () - time_state_CAN >= 100) // таймер, який відраховує 3с від ввімкнення живлення, якщо немає прийому даних data_Bien_Air
{	
	time_state_CAN = HAL_GetTick (); // для відліку часу використано системний таймер
	if (state_CAN == 0) // посилка data_Bien_Air не отримана - помилка з'єднання
	{
		tim_CAN_error ++;  // початук відліку часу для оцінки роботи CAN
		if (tim_CAN_error >= 50) // відраховуємо 5с
		{
			data_CAN_NOT_OK = 1; // помилка при прийомі даних
		}
	}
  if (state_CAN == 1) // посилка data_Bien_Air отримана
  {
		tim_CAN_error = 0; // обнулення таймера, який відраховує 3с
	}
}	
		
if (HAL_GetTick () - tim_data_chair_ok >= 100) // обновлення стану світлодіодів відбувається кожні 100мс
{
	tim_data_chair_ok = HAL_GetTick(); // для відліку часу використано системний таймер
	timeRemove++;
	
	if (state_CAN == 1) // якщо отримано буфер data_Bien_Air
	{
		ErrorLEDReset (); // ввімкнення світлодіода Error - вимкнено - є передача даних по CAN 
	}
	
	if (data_CAN_NOT_OK == 1) // втрата даних / помилка на лінії CAN
	{
		timCanRxDataBienAirNOTOK++;
		if (timCanRxDataBienAirNOTOK >= 30)
		{
		state_CAN = 0;
		time_error_LED ++; // запускаємо таймер, який починає відлік часу для роботи із світлодіодами
		if (time_error_LED  < 5) // частота мигання світлодіода - 500мс
		{
			ErrorLEDSet (); // ввімкнення світлодіода, що сигналізує про роботу CAN
  	}
		else if (time_error_LED < 10) // частота мигання світлодіода - 500мс
		{
			ErrorLEDReset (); // вимиканення світлодіода, що сигналізує про роботу CAN
		}
		else
		{
			time_error_LED = 0; // після одного циклу мигання обнулення таймера для відліку часу
		}
	 }
	}
	
	if (state_CAN == 1)
	{
		StatusLEDSet (); // світлодіод Status LED ввімкнуто
	}
	else if (state_CAN == 0)
	{
		timeStatusCAN++;
		if (timeStatusCAN == 5)
		{
			StatusLEDReset (); // світлодіод Status LED вимкнуто
		}
	}	
}	

// Варіант 1 - всі клапани промиваються одночасно

//if (washing == 1)
//{
//  BackrestDownSet (); // інструмент 1
//	BackrestUpSet (); // інструмент 2
//	ChairUpSet (); // інструмент 3
//	ChairDownSet (); // інструмент 4
//	Memory2Set (); // обхідний клапан
//}
//else
//{
//  BackrestDownReset (); // інструмент 1
//	BackrestUpReset (); // інструмент 2
//	ChairUpReset (); // інструмент 3
//	ChairDownReset (); // інструмент 4
//	Memory2Reset (); // обхідний клапан
//}


// Варіант 1_1 - всі клапани промиваються одночасно через один вихід (вмикання через контакти реле)

if (washing == 1)
{
	ChairDownSet (); // опція реле для вмикання клапанів промивки
}
else
{
	ChairDownReset ();// опція реле для вмикання клапанів промивки
}


//// Варіант 2 - інструменти промиваються почергово


//static uint32_t washing_start = 0;
//static uint32_t tim_washing = 0;   // тут буде тривалість


//if (washing == 1 && hol_state == 2 && flag == 0)
//{
//    washing_start = HAL_GetTick();   // старт

//    BackrestDownSet();
//    BackrestUpReset();
//    ChairUpReset();
//    ChairDownReset();
//    Memory2Set();

//    flag = 1;
//}

//if (washing == 0 && washing_start != 0 && tim_washing == 0)
//{
//    tim_washing = HAL_GetTick() - washing_start;  // ТРИВАЛІСТЬ

//    washing_start = 0;
//}

//static uint32_t tim_washing_start1 = 0;
//static uint32_t tim_washing_start2 = 0;
//static uint32_t tim_washing_start3 = 0;

//uint32_t now = HAL_GetTick();

//if (flag == 1 && washing == 0 && hol_state == 1)
//{
//    if (tim_washing_start1 == 0)
//        tim_washing_start1 = now;

//    if (now - tim_washing_start1 <= tim_washing)
//    {
//        BackrestDownReset();
//        BackrestUpSet();
//        ChairUpReset();
//        ChairDownReset();
//        Memory2Set();
//    }
//    else
//    {
//        flag = 2;
//        tim_washing_start1 = 0;
//    }
//}
//	
//else if (flag == 2 && washing == 0 && hol_state == 1)
//{
//    if (tim_washing_start2 == 0)
//        tim_washing_start2 = now;

//    if (now - tim_washing_start2 <= tim_washing)
//    {
//        BackrestDownReset();
//				BackrestUpReset();
//        ChairUpSet();
//        ChairDownReset();
//        Memory2Set();
//    }
//    else
//    {
//        flag = 3;
//        tim_washing_start2 = 0;
//    }
//}

//else if (flag == 3 && washing == 0 && hol_state == 1)
//{
//    if (tim_washing_start3 == 0)
//        tim_washing_start3 = now;

//    if (now - tim_washing_start3 <= tim_washing)
//    {
//        BackrestDownReset();
//				BackrestUpReset();
//				ChairUpReset();
//        ChairDownSet();
//        Memory2Set();
//    }
//    else
//    {
//        tim_washing_start3 = 0;
//        tim_washing = 0;   // очищаємо після використання
//        flag = 0;
//    }
//}

//if (stop_washing == 1)
//{
//    BackrestDownReset();
//    BackrestUpReset();
//    ChairUpReset();
//    ChairDownReset();
//    Memory2Reset();

//    flag = 0;
//    tim_washing = 0;
//    washing_start = 0;
//		tim_washing_start1 = 0;
//		tim_washing_start2 = 0;
//		tim_washing_start3 = 0;
//}
//	
//if ((washing == 0 && hol_state != 1) || flag == 0)
//{
//        BackrestDownReset();  
//        BackrestUpReset();
//				ChairUpReset ();
//				ChairDownReset ();
//        Memory2Reset();
//				tim_washing_start1 = 0;
//				tim_washing_start2 = 0;
//				tim_washing_start3 = 0;
//}


   /* USER CODE END WHILE */

   /* USER CODE BEGIN 3 */
}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL5;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV4;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_10;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief ADC2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC2_Init(void)
{

  /* USER CODE BEGIN ADC2_Init 0 */

  /* USER CODE END ADC2_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC2_Init 1 */

  /* USER CODE END ADC2_Init 1 */

  /** Common config
  */
  hadc2.Instance = ADC2;
  hadc2.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc2.Init.ContinuousConvMode = ENABLE;
  hadc2.Init.DiscontinuousConvMode = DISABLE;
  hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc2.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC2_Init 2 */

  /* USER CODE END ADC2_Init 2 */

}

/**
  * @brief CAN Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN_Init(void)
{

  /* USER CODE BEGIN CAN_Init 0 */

  /* USER CODE END CAN_Init 0 */

  /* USER CODE BEGIN CAN_Init 1 */

  /* USER CODE END CAN_Init 1 */
  hcan.Instance = CAN1;
  hcan.Init.Prescaler = 2;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_8TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_1TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = ENABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN_Init 2 */

  /* USER CODE END CAN_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, CHAIR_DOWN_Pin|CHAIR_UP_Pin|BACKREST_UP_Pin|BACKREST_DOWN_Pin
                          |LIGHT_ON_Pin|WATER_S_Pin|WATER_F_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, SPITTOON_Pin|A_Pin|B_Pin|COAG_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, Open_Collector_1_Pin|Open_Collector_2_Pin|Code_LED_Pin|Status_LED_Pin
                          |Error_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : Coag_init_Pin */
  GPIO_InitStruct.Pin = Coag_init_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(Coag_init_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : CHAIR_DOWN_Pin CHAIR_UP_Pin BACKREST_UP_Pin BACKREST_DOWN_Pin
                           LIGHT_ON_Pin WATER_S_Pin WATER_F_Pin */
  GPIO_InitStruct.Pin = CHAIR_DOWN_Pin|CHAIR_UP_Pin|BACKREST_UP_Pin|BACKREST_DOWN_Pin
                          |LIGHT_ON_Pin|WATER_S_Pin|WATER_F_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : SPITTOON_Pin A_Pin B_Pin COAG_Pin */
  GPIO_InitStruct.Pin = SPITTOON_Pin|A_Pin|B_Pin|COAG_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : Pedal_ON_OFF_Pin */
  GPIO_InitStruct.Pin = Pedal_ON_OFF_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(Pedal_ON_OFF_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : CHIP_Pin SPRAY_Pin */
  GPIO_InitStruct.Pin = CHIP_Pin|SPRAY_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : Open_Collector_1_Pin Open_Collector_2_Pin Code_LED_Pin Status_LED_Pin
                           Error_LED_Pin */
  GPIO_InitStruct.Pin = Open_Collector_1_Pin|Open_Collector_2_Pin|Code_LED_Pin|Status_LED_Pin
                          |Error_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
