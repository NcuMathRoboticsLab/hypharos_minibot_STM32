#include "usart.h"
//加入以下代码,支持printf函数,而不需要选择use MicroLIB
#if 1
#if defined(__CC_ARM)
#pragma import(__use_no_semihosting)
//标准库需要的支持函数
struct __FILE
{
	int handle;
	/* Whatever you require here. If the only file you are using is */
	/* standard output using printf() for debugging, no file handling */
	/* is required. */
};
#else
__asm(".global __use_no_semihosting\n\t");
#endif
/* FILE is typedef’ d in stdio.h. */
FILE __stdout;
//定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x)
{
	x = x;
}
void _ttywrch(int ch)
{
	ch = ch;
}
//重定义fputc函数
int fputc(int ch, FILE *f)
{
	while((USART1->SR&0X40)==0);
	USART1->DR = (u8) ch;
	return ch;
}
#endif
//end
//////////////////////////////////////////////////////////////////
/**************************************************************************
函数功能：串口1发送一个字节
入口参数：data：要发送的数据
返回  值：无
**************************************************************************/
void usart1_send(u8 data)
{
	USART1->DR = data;
	while((USART1->SR&0x40)==0);
}
/**************************************************************************
函数功能：串口1初始化 (PA9=TX, PA10=RX，連接C03C板載USB轉串口)
入口参数：pclk2：PCLK2时钟频率(MHz)；bound：波特率
返回  值：无
**************************************************************************/
void uart_init(u32 pclk2,u32 bound)
{
	float temp;
	u16 mantissa;
	u16 fraction;
	temp=(float)(pclk2*1000000)/(bound*16);//得到USARTDIV
	mantissa=temp;				 //得到整数部分
	fraction=(temp-mantissa)*16; //得到小数部分
	mantissa<<=4;
	mantissa+=fraction;
	RCC->APB2ENR|=1<<2;   //使能PORTA口时钟
	RCC->APB2ENR|=1<<14;  //使能串口1时钟
	GPIOA->CRH&=0XFFFFF00F;//IO状态设置
	GPIOA->CRH|=0X000008B0;//IO状态设置

	RCC->APB2RSTR|=1<<14;   //复位串口1
	RCC->APB2RSTR&=~(1<<14);//停止复位
	//波特率设置
	USART1->BRR=mantissa; // 波特率设置
	USART1->CR1|=0X200C;  //1位停止,无校验位.
	USART1->CR1|=1<<8;    //PE中断使能
	USART1->CR1|=1<<5;    //接收缓冲区非空中断使能
	MY_NVIC_Init(0,1,USART1_IRQn,2);//组2，最低优先级
}
/**************************************************************************
函数功能：串口1接收中断 (接收上位机 0xff 0xfe + 4字节速度指令)
入口参数：无
返回  值：无
**************************************************************************/
int USART1_IRQHandler(void)
{
	if(USART1->SR&(1<<5))//接收到数据
	{
		u8 temp;
		static u8 count,last_data,last_last_data;
		temp=USART1->DR;
		if(Usart_Flag==0)
		{
			if(last_data==0xfe&&last_last_data==0xff)
				Usart_Flag=1,count=0;
		}
		if(Usart_Flag==1)
		{
			Urxbuf[count]=temp;
			count++;
			if(count==4)Usart_Flag=0;
		}
		last_last_data=last_data;
		last_data=temp;
	}
	return 0;
}

