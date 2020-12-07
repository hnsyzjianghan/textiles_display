#include "delay.h" 
#include "key.h" 
#include "sys.h" 
#include "usart.h" 

u8 message_flag[4][16] = {
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0xF0,0x1F,0x30,0x18,0x50,0x14,0x90,0x13,0x10,0x11,0x10,0x10,0xF0,0x1F},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0xF0,0x1F,0x30,0x18,0x50,0x14,0x90,0x13,0x10,0x11,0x10,0x10,0xF0,0x1F}
}
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
	 u8 t,len; 
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
	 LED_Init(); 

	 while(1) 
	 { 
		 if(USART_RX_STA&0x8000) 
		 { 
			 for(zp_j=0;zp_j<4;zp_j++)
			 {
				 for(zp_i=0;zp_i<16;zp_i++)
				 {
						SendOneByte(message_flag[zp_j][zp_i]);
				 }
			 }
			 len=USART_RX_STA&0x3f; 
			 for(t=0;t<len;t++) 
			 { 
				 SendOneByte(USART_RX_BUF[t]);
				 delay_ms(1000); 
				 while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET); 
			 } 
			 printf("\r\n\r\n");
			 USART_RX_STA=0; 
		 }else 
		 { 
			 times++; 
			 if(times%5000==0) 
			 { 
				 printf("Hi!!!"); 
			 }
			 delay_ms(10); 
		 } 
	 } 
 } 



