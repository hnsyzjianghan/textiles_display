#include "delay.h" 
#include "sys.h" 
#include "usart.h" 
#include "stm32f10x.h"
#include "oled.h"
#include "sys.h"
#include "delay.h"
#include "bmp.h"
#include "adc.h"
#include "misc.h"
#define BaudRateUsed        115200
#define SendingDelay        8
#define TXD_high()                GPIO_SetBits(GPIOA, GPIO_Pin_2)
#define TXD_low()                GPIO_ResetBits(GPIOA, GPIO_Pin_2)

	u8 anx[] = {0x00,0x60,0x02,0x90,0x28,0x97,0x92,0xF4,0x92,0x94,0x92,0x94,0xAA,0x94,0x00,0x00,  // anxious
		         0x00,0x00,0x00,0x00,0x9C,0x64,0x90,0x94,0x88,0x94,0x84,0x94,0x5C,0x63,0x00,0x00,};
	u8 foc[] = {0x00,0xE0,0x00,0x80,0xEA,0x8E,0x8A,0xEA,0x8A,0x8A,0x8A,0x8A,0xEF,0x8E,0x00,0x00,  // focused
		         0x08,0x00,0x08,0x00,0x08,0xE6,0x38,0x89,0x48,0x4F,0x48,0x28,0x38,0xE6,0x00,0x00,};
	u8 rel[] = {0x20,0xE0,0x20,0x90,0x2E,0x93,0xAA,0xF4,0xAA,0xA7,0x2A,0x94,0x2F,0x93,0x00,0x00,  // relaxed
		         0x08,0x00,0x08,0x00,0x38,0xA6,0x48,0x49,0x48,0x4F,0x48,0x48,0x38,0xA6,0x00,0x00,};
	u8 none[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // none
						 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,};

static void TIM3_Configuration(void)
{
        TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);

          /* Time base configuration */
          TIM_TimeBaseStructure.TIM_Period = 65535 - 1;
          TIM_TimeBaseStructure.TIM_Prescaler = 72-1;
        TIM_TimeBaseStructure.TIM_ClockDivision = 0;
          TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

          TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
        TIM_Cmd(TIM3,ENABLE);    

}

void Delay_Ms(__IO uint32_t nTime)
{ 

        uint16_t tmp;

        tmp = TIM_GetCounter(TIM3);
        
        if(tmp + nTime <= 65535)
                while( (TIM_GetCounter(TIM3) - tmp) < nTime );
        else
        {
                TIM_SetCounter(TIM3, 0);
                while( TIM_GetCounter(TIM3) < nTime );
        }
                        
}

void SendOneByte(uint8_t datatoSend)
{
        uint8_t i, tmp;

        /* Start bit */
        TXD_low();
        Delay_Ms(SendingDelay);        

        for(i = 0; i < 8; i++)
        {
                tmp        = (datatoSend >> i) & 0x01;

                if(tmp == 0)
                {
                        TXD_low();
                        Delay_Ms(SendingDelay);        //0                
                }
                else
                {
                        TXD_high();
                        Delay_Ms(SendingDelay);        //1                
                }        
        }
        
        /* Stop bit */
        TXD_high();
        Delay_Ms(SendingDelay);        
}
int main(void) 
{ 
	 u8 t,len,Flag; 
	 u16 times=0; 
	 GPIO_InitTypeDef GPIO_InitStructure_A, GPIO_InitStructure_B;

	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PA端口时钟
	 GPIO_SetBits(GPIOA,GPIO_Pin_2);	//PA2 输出高
	 GPIO_InitStructure_A.GPIO_Pin = GPIO_Pin_2;	 //PA2推挽输出  
 	 GPIO_InitStructure_A.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	 GPIO_InitStructure_A.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
   GPIO_Init(GPIOA, &GPIO_InitStructure_A);	  //初始化GPIOA2
   GPIO_SetBits(GPIOA,GPIO_Pin_2);	//PA2 输出高
 	 delay_init();
	 
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	 uart_init(115200); 

	 while(1) 
	 { 
		 if(USART_RX_STA&0x8000) 
		 { 
			 len=USART_RX_STA&0x3f; 
			 for(u8 i=0;i<len;i++)
			 {
				 SendOneByte(USART_RX_BUF[i]);
			 }
			 USART_RX_STA=0;
		 }
	 } 
} 



