#include "stm32f4xx.h"

#define GPIOAEN			(1U<<0)
#define UART2EN 		(1U<<17)
#define SYS_FREQ 		16000000
#define	APB1_CLK		(SYS_FREQ)
#define	UART_BAUDRATE	115200
#define	CR1_TE			(1U<<3)
#define	CR1_UE			(1U<<13)
#define

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);
static void uart_set_baudrate(USART_TypeDef *USARTx,_uint32_t PeriphClk, uint32_t BaudRate);

int main(void)
{


	while(1)
	{


	}
}

void uar2_tx_init(void)
{
	//*************Configure UART GPIO pin************
	//enable CLOCK access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;
	//set PA2 mode to alternative function mode
	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |=	(1U<<5);
	//set PA2 alternate function type to UART_TX (AF07)
	GPIOA->AFR[0] |= (1U<<12);
	GPIOA->AFR[0] |= (1U<<13);
	GPIOA->AFR[0] |= (1U<<14);
	GPIOA->AFR[0] &=~(1U<<15);
	//*************Configure UART module****************
	//enable clock access to uart2
	RCC->APB1ENR |= UART2EN;
	//configure baudrate
	uart_set_baudrate(USART2,APB1_CLK,UART_BAUDRATE);
	//configure the transfer direction
	USART2->CR1 = CR1_TE;
	//enable UART module
	USART2->CR1 |= CR1_UE;
}

static void uart_set_baudrate(USART_TypeDef *USARTx,_uint32_t PeriphClk, uint32_t BaudRate)
{
	USARTx->BRR = compute_uart_bd(PeriphClk, BaudRate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
	return	((PeriphClk + (BaudRate/2U))/BaudRate);
}
