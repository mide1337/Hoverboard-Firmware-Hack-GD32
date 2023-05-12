#ifdef MASTER		// layout 2.2 has buzzer on the slave board.
	#define BUZZER
#endif


// LED defines
#define LED_GREEN GPIO_PIN_15
#define LED_GREEN_PORT GPIOA
#define LED_ORANGE GPIO_PIN_12
#define LED_ORANGE_PORT GPIOA
#define LED_RED GPIO_PIN_3
#define LED_RED_PORT GPIOB

#define UPPER_LED_PIN GPIO_PIN_1
#define UPPER_LED_PORT GPIOA
#define LOWER_LED_PIN GPIO_PIN_0
#define LOWER_LED_PORT GPIOA

// Mosfet output
#define MOSFET_OUT_PIN GPIO_PIN_13
#define MOSFET_OUT_PORT GPIOC

// Brushless Control DC (BLDC) defines
#define TIMER_BLDC_PULLUP	GPIO_PUPD_NONE	// robo
// Channel G
#define RCU_TIMER_BLDC RCU_TIMER0
#define TIMER_BLDC TIMER0
#define TIMER_BLDC_CHANNEL_G TIMER_CH_2
#define TIMER_BLDC_GH_PIN GPIO_PIN_10
#define TIMER_BLDC_GH_PORT GPIOA
#define TIMER_BLDC_GL_PIN GPIO_PIN_15
#define TIMER_BLDC_GL_PORT GPIOB
// Channel B
#define TIMER_BLDC_CHANNEL_B TIMER_CH_1
#define TIMER_BLDC_BH_PIN GPIO_PIN_9
#define TIMER_BLDC_BH_PORT GPIOA
#define TIMER_BLDC_BL_PIN GPIO_PIN_14
#define TIMER_BLDC_BL_PORT GPIOB
// Channel Y
#define TIMER_BLDC_CHANNEL_Y TIMER_CH_0
#define TIMER_BLDC_YH_PIN GPIO_PIN_8
#define TIMER_BLDC_YH_PORT GPIOA
#define TIMER_BLDC_YL_PIN GPIO_PIN_13
#define TIMER_BLDC_YL_PORT GPIOB

// Timer BLDC short circuit emergency shutoff define
#define TIMER_BLDC_EMERGENCY_SHUTDOWN_PIN GPIO_PIN_12
#define TIMER_BLDC_EMERGENCY_SHUTDOWN_PORT GPIOB

// Hall sensor defines
#define HALL_A_PIN GPIO_PIN_11
#define HALL_A_PORT GPIOB
#define HALL_B_PIN GPIO_PIN_1
#define HALL_B_PORT GPIOF
#define HALL_C_PIN GPIO_PIN_14
#define HALL_C_PORT GPIOC

// Usart master slave defines
#define USART_MASTERSLAVE USART1
#define USART_MASTERSLAVE_TX_PIN GPIO_PIN_2
#define USART_MASTERSLAVE_TX_PORT GPIOA
#define USART_MASTERSLAVE_RX_PIN GPIO_PIN_3
#define USART_MASTERSLAVE_RX_PORT GPIOA

// ADC defines
#define VBATT_PIN	GPIO_PIN_4
#define VBATT_PORT GPIOA
#define VBATT_CHANNEL ADC_CHANNEL_4
#define CURRENT_DC_PIN	GPIO_PIN_6
#define CURRENT_DC_PORT GPIOA
#define CURRENT_DC_CHANNEL ADC_CHANNEL_6

// Self hold defines
#define SELF_HOLD_PIN GPIO_PIN_2
#define SELF_HOLD_PORT GPIOB

// Button defines
#define BUTTON_PIN GPIO_PIN_15
#define BUTTON_PORT GPIOC

// Usart steer defines
#define USART_STEER_COM USART0
#define USART_STEER_RCU RCU_USART0
#define USART_STEER_AF	GPIO_AF_0
#define USART_STEER_COM_TX_PIN GPIO_PIN_6
#define USART_STEER_COM_TX_PORT GPIOB
#define USART_STEER_COM_RX_PIN GPIO_PIN_7
#define USART_STEER_COM_RX_PORT GPIOB

#ifdef BUZZER
	// Buzzer defins
	#define BUZZER_PIN GPIO_PIN_10
	#define BUZZER_PORT GPIOB
#endif

#ifdef MASTER
	// Charge state defines
	#define CHARGE_STATE_PIN GPIO_PIN_0
	#define CHARGE_STATE_PORT GPIOF
#endif

// Debug pin defines
#define DEBUG_PIN GPIO_PIN_4
#define DEBUG_PORT GPIOB

