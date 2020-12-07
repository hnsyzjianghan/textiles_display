#include "stm32f10x.h"
#include "oled.h"
#include "sys.h"
#include "delay.h"
#include "bmp.h"
#include "adc.h"
#include "misc.h"
#include "dis.h"
NVIC_InitTypeDef NVIC_InitStructure;
u8 key_flag = 0;
char Input_char[4];

u8 key_ID = 100;
u8 last_ID = 100;
u16 adcx,adczp;
u8 adc_filter_time = 80;
u8 adc_filter_num = 0;
u32 adc_filter_sum = 0;
u8 key_buffer[8];
u8 buffer_num = 0;
void NVIC_Config(void)
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //设置中断优先级分组
  NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
  NVIC_Init(&NVIC_InitStructure);
}

void output(char w_i)
{
	
	if (w_i == '_')
	{
		return;
	}
	if (w_i == '&')
	{
		uart_output(key_buffer, buffer_num);
	}
	else
	{
		display(w_i);
		key_buffer[buffer_num] = w_i;
		buffer_num +=1;
		if(buffer_num == 8)
			buffer_num = 0;
	}
}

void processing(u8 key_ID)
{
	char char0[4] = {'1','A','B','C'};
	char char1[4] = {'2','D','E','F'};
	char char2[4] = {'3','G','H','I'};
	char char3[4] = {'!','2','3','4'};
	char char4[4] = {'4','J','K','L'};
	char char5[4] = {'5','M','N','O'};
	char char6[4] = {'6','P','Q','R'};
	char char7[4] = {',','S','T','U'};
	char char8[4] = {'7','V','W','X'};
	char char9[4] = {'8','Y','Z','_'};
	char char10[4] = {'9','_','_','_'};
	char char11[4] = {'.','_','_','_'};
	char char12[4] = {'+','-','*','/'};
	char char13[4] = {'&','&','&','&'}; 
	char char14[4] = {'0',' ','_','_'};
	char char15[4] = {'<','_','_','_'};
//	u8 last_ID = 0;
	u8 pad_num = 0;
	
	switch(key_ID)
	{
		case 0:
			if(last_ID==0)
			{
				pad_num +=1;
				if(pad_num>3)
				{
					pad_num=0;
				}
			}
			else
			{
				pad_num=0;
			}
			output(char0[pad_num]);
			break;
		case 1:
			if(last_ID==1)
			{
				pad_num +=1;
				if(pad_num>3)
				{
					pad_num=0;
				}
			}
			else
			{
				pad_num=0;
			}
			output(char1[pad_num]);
			break;
		case 2:
			if(last_ID==2)
			{
				pad_num +=1;
				if(pad_num>3)
				{
					pad_num=0;
				}
			}
			else
			{
				pad_num=0;
			}
			output(char2[pad_num]);
			break;
		case 3:
			if(last_ID==3)
			{
				pad_num +=1;
				if(pad_num>3)
				{
					pad_num=0;
				}
			}
			else
			{
				pad_num=0;
			}
			output(char3[pad_num]);
			break;
		case 4:
			if(last_ID==4)
			{
				pad_num +=1;
				if(pad_num>3)
				{
					pad_num=0;
				}
			}
			else
			{
				pad_num=0;
			}
			output(char4[pad_num]);
			break;
		case 5:
			if(last_ID==5)
			{
				pad_num +=1;
				if(pad_num>3)
				{
					pad_num=0;
				}
			}
			else
			{
				pad_num=0;
			}
			output(char5[pad_num]);
			break;
		case 6:
			if(last_ID==6)
			{
				pad_num +=1;
				if(pad_num>3)
				{
					pad_num=0;
				}
			}
			else
			{
				pad_num=0;
			}
			output(char6[pad_num]);
			break;
		case 7:
			if(last_ID==7)
			{
				pad_num +=1;
				if(pad_num>3)
				{
					pad_num=0;
				}
			}
			else
			{
				pad_num=0;
			}
			output(char7[pad_num]);
			break;
		case 8:
			if(last_ID==8)
			{
				pad_num +=1;
				if(pad_num>3)
				{
					pad_num=0;
				}
			}
			else
			{
				pad_num=0;
			}
			output(char8[pad_num]);
			break;
		case 9:
			if(last_ID==9)
			{
				pad_num +=1;
				if(pad_num>3)
				{
					pad_num=0;
				}
			}
			else
			{
				pad_num=0;
			}
			output(char9[pad_num]);
			break;
		case 10:
			if(last_ID==10)
			{
				pad_num +=1;
				if(pad_num>3)
				{
					pad_num=0;
				}
			}
			else
			{
				pad_num=0;
			}
			output(char10[pad_num]);
			break;
		case 11:
			if(last_ID==11)
			{
				pad_num +=1;
				if(pad_num>3)
				{
					pad_num=0;
				}
			}
			else
			{
				pad_num=0;
			}
			output(char11[pad_num]);
			break;
		case 12:
			if(last_ID==12)
			{
				pad_num +=1;
				if(pad_num>3)
				{
					pad_num=0;
				}
			}
			else
			{
				pad_num=0;
			}
			output(char12[pad_num]);
			break;
		case 13:
			if(last_ID==13)
			{
				pad_num +=1;
				if(pad_num>3)
				{
					pad_num=0;
				}
			}
			else
			{
				pad_num=0;
			}
			output(char13[pad_num]);
			break;
		case 14:
			if(last_ID==14)
			{
				pad_num +=1;
				if(pad_num>3)
				{
					pad_num=0;
				}
			}
			else
			{
				pad_num=0;
			}
			output(char14[pad_num]);
			break;
		case 15:
			if(last_ID==15)
			{
				pad_num +=1;
				if(pad_num>3)
				{
					pad_num=0;
				}
			}
			else
			{
				pad_num=0;
			}
			output(char15[pad_num]);
			break;
		default:
			break;
	}
	last_ID = key_ID;
}

int main(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	adczp = 0;

	//这两步是为了释放PB3、4，PA15的GPIO功能，其默认为JTAG的功能脚，我们要用LED所以要禁止JTAG 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//重映射需要先使能AFIO时钟
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//只关闭JTAG而保留SWD
	//	
	NVIC_Config();//设置ADC中断,需要对应相应的处理器容量来查向量号
	
	delay_init();
 	OLED_Init();
	OLED_Clear();
	Adc_Init();

	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE); //使能 PB,PA 端口时钟	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4; //LED2、3-->PB.3、4 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO 口速度为 10MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化 GPIOB.3、4

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; //LED1-->PA.15 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO 口速度为 10MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化 GPIOB.5	
	
	ADC_WatchdogConfig();
	ADC_RegularChannelConfig(ADC1, 9, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	  			    
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能	 

	
	
	while(1)
	{
			if(key_ID != 100)
			{
				processing(key_ID);
				key_ID = 100;
			}

	}
}


void ADC1_2_IRQHandler(void)
{

	ADC_ITConfig(ADC1,ADC_IT_AWD,DISABLE);
	if(SET == ADC_GetFlagStatus(ADC1,ADC_FLAG_AWD))
	{
		
		while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
		adcx=ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
		adc_filter_sum = adcx+adc_filter_sum;//这里是个滤波器函数，也可以理解为消抖函数，因为按键松开时有抖动，且电压不是跳变，而是“缓慢”回升，因此在
		adc_filter_num++;                    //ADC采样时，会采集到回升时电压，此时也会进入中断从而导致误操作，因此，设置一个滤波器，每次进入中断后叠加
		if(adc_filter_num == adc_filter_time)//采样值，叠加次数为adc_filter_time，接着判断本次采样值与平均值之差，相差不大时才认为是按键，否则忽略，也就是
		{                                    //不置位按键标志位，因此，限制滤波器时间窗，也就是消抖的条件，可以从两方面入手，一个是增大叠加次数adc_filter_time
			adc_filter_num = 0;								 //另一个就是减小偏差值，本例为100，效果不错
			if((adc_filter_sum/adc_filter_time - adcx)<100)
			{
				key_flag = 1;
				adczp = adc_filter_sum/adc_filter_time;
			}
			adc_filter_sum = 0;
		}
	}
	if(key_flag == 1)
	{
		key_ID = adczp/256;
		key_flag = 0;
	}
	ADC_ITConfig(ADC1,ADC_IT_AWD,ENABLE);
	ADC_ClearFlag(ADC1,ADC_FLAG_AWD);
	ADC_ClearITPendingBit(ADC1,ADC_IT_AWD);

}



