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
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�����ж����ȼ�����
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

	//��������Ϊ���ͷ�PB3��4��PA15��GPIO���ܣ���Ĭ��ΪJTAG�Ĺ��ܽţ�����Ҫ��LED����Ҫ��ֹJTAG 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//��ӳ����Ҫ��ʹ��AFIOʱ��
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//ֻ�ر�JTAG������SWD
	//	
	NVIC_Config();//����ADC�ж�,��Ҫ��Ӧ��Ӧ�Ĵ�������������������
	
	delay_init();
 	OLED_Init();
	OLED_Clear();
	Adc_Init();

	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE); //ʹ�� PB,PA �˿�ʱ��	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4; //LED2��3-->PB.3��4 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO ���ٶ�Ϊ 10MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ�� GPIOB.3��4

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; //LED1-->PA.15 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO ���ٶ�Ϊ 10MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ�� GPIOB.5	
	
	ADC_WatchdogConfig();
	ADC_RegularChannelConfig(ADC1, 9, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			    
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������	 

	
	
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
		
		while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
		adcx=ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
		adc_filter_sum = adcx+adc_filter_sum;//�����Ǹ��˲���������Ҳ�������Ϊ������������Ϊ�����ɿ�ʱ�ж������ҵ�ѹ�������䣬���ǡ������������������
		adc_filter_num++;                    //ADC����ʱ����ɼ�������ʱ��ѹ����ʱҲ������жϴӶ��������������ˣ�����һ���˲�����ÿ�ν����жϺ����
		if(adc_filter_num == adc_filter_time)//����ֵ�����Ӵ���Ϊadc_filter_time�������жϱ��β���ֵ��ƽ��ֵ֮�����ʱ����Ϊ�ǰ�����������ԣ�Ҳ����
		{                                    //����λ������־λ����ˣ������˲���ʱ�䴰��Ҳ�������������������Դ����������֣�һ����������Ӵ���adc_filter_time
			adc_filter_num = 0;								 //��һ�����Ǽ�Сƫ��ֵ������Ϊ100��Ч������
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



