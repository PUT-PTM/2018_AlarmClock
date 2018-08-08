#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

int counter2 = 0;
int counterzapas = 0;
int counter3 = 0;
int counter4 = 0;
int counter5 = 0;
int segment = 0;


volatile int segments[]={GPIO_Pin_4,GPIO_Pin_5,GPIO_Pin_6,GPIO_Pin_7,GPIO_Pin_8,GPIO_Pin_9,GPIO_Pin_10,GPIO_Pin_11};
volatile int i=0;
volatile int piny[] = {GPIO_Pin_0,GPIO_Pin_1,GPIO_Pin_2,GPIO_Pin_3};

uint16_t numbersReset [10] = {
		/* -0- */  GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9,
		/* -1- */	GPIO_Pin_5 | GPIO_Pin_6,
		/* -2- */	GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_10 ,
		/* -3- */	GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_10 ,
		/* -4- */	GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_9 | GPIO_Pin_10,
		/* -5- */	GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_9 | GPIO_Pin_10 ,
		/* -6- */	 GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10,
		/* -7- */	GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6,
		/* -8- */   GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10,
		/* -9- */	GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_9 | GPIO_Pin_10
};

uint16_t numbersSet [10] = {
		/* -0- */  GPIO_Pin_10 | GPIO_Pin_11,
		/* -1- */	GPIO_Pin_4 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11,
		/* -2- */	GPIO_Pin_6 | GPIO_Pin_9 | GPIO_Pin_11 ,
		/* -3- */	GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_11 ,
		/* -4- */	GPIO_Pin_4 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_11,
		/* -5- */	GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_11 ,
		/* -6- */	GPIO_Pin_5 | GPIO_Pin_11,
		/* -7- */	GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11,
		/* -8- */   GPIO_Pin_11 ,
		/* -9- */	GPIO_Pin_8 | GPIO_Pin_11
};


void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		if(segment == 0)
		{
			GPIO_SetBits(GPIOD, piny[0]);
			GPIO_ResetBits(GPIOD, piny[1] | piny[2] | piny[3]);

			GPIO_SetBits(GPIOE, numbersSet[counter2]);
			GPIO_ResetBits(GPIOE, numbersReset[counter2]);

		}
		if(segment == 1)
		{
			GPIO_SetBits(GPIOD, piny[1]);
			GPIO_ResetBits(GPIOD, piny[0] | piny[2] | piny[3]);

			GPIO_SetBits(GPIOE, numbersSet[counter3]);
			GPIO_ResetBits(GPIOE, numbersReset[counter3]);
		}
		if(segment == 2)
		{
			GPIO_SetBits(GPIOD, piny[2]);
			GPIO_ResetBits(GPIOD, piny[1] | piny[0] | piny[3]);

			GPIO_SetBits(GPIOE, numbersSet[counter4]);
			GPIO_ResetBits(GPIOE, numbersReset[counter4]);
		}
		if(segment == 3)
		{
			GPIO_SetBits(GPIOD, piny[3]);
			GPIO_ResetBits(GPIOD, piny[1] | piny[2] | piny[0]);

			GPIO_SetBits(GPIOE, numbersSet[counter5]);
			GPIO_ResetBits(GPIOE, numbersReset[counter5]);
		}
		segment++;
		if(segment == 4) segment = 0;

		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		counterzapas++;

		counter3++;
		if(counter3 == 10) {counter3=0;}

		if(counterzapas == 10) {counter2++; counterzapas =0;}
		if(counter2 == 10) {counter2=0;}

		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}

void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{
		counter4++;
		if(counter4 == 10) counter4=0;

		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}

void TIM5_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
	{
		counter5++;
		if(counter5 == 10) counter5=0;

		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	}
}


int main(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7 | GPIO_Pin_8 |  GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitTypeDef  GPIO_InitStructure2;
	GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3;
	GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure2.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure2.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure2.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure2);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure2;
	TIM_TimeBaseStructure2.TIM_Period = 9999;
	TIM_TimeBaseStructure2.TIM_Prescaler = 20;
	TIM_TimeBaseStructure2.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure2.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure2);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure3;
	TIM_TimeBaseStructure3.TIM_Period = 9999;
	TIM_TimeBaseStructure3.TIM_Prescaler = 8399;
	TIM_TimeBaseStructure3.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure3.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure3);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure4;
	TIM_TimeBaseStructure4.TIM_Period = 9999;
	TIM_TimeBaseStructure4.TIM_Prescaler = 839;
	TIM_TimeBaseStructure4.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure4.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure4);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure5;
	TIM_TimeBaseStructure5.TIM_Period = 9999;
	TIM_TimeBaseStructure5.TIM_Prescaler = 83;
	TIM_TimeBaseStructure5.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure5.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure5);


	NVIC_InitTypeDef NVIC_InitStructure2;
	NVIC_InitStructure2.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure2.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_InitStructure2.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure2.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure2);

	NVIC_InitTypeDef NVIC_InitStructure3;
	NVIC_InitStructure3.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure3.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure3.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure3.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure3);

	NVIC_InitTypeDef NVIC_InitStructure4;
	NVIC_InitStructure4.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure4.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure4.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure4.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure4);

	NVIC_InitTypeDef NVIC_InitStructure5;
	NVIC_InitStructure5.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure5.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure5.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure5.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure5);


	TIM_Cmd(TIM2, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
	TIM_Cmd(TIM5, ENABLE);

	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

	TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);


	GPIO_SetBits(GPIOE, GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11);

	for(;;)
	{

	}
}
