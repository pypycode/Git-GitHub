//                                     HO VA TEN : NGUYEN HUU TIEN
//                             BAI TAP : BIEN DOI ADC CHE DO DMA VOI 3 KENH ADC
/*****************************************************************************************************************/

#include "stm32f4xx.h"

DMA_InitTypeDef            098;
ADC_InitTypeDef            ADC_InitStructure;
ADC_CommonInitTypeDef      ADC_CommonInitStructure;
GPIO_InitTypeDef           GPIO_InitStructure;

volatile uint16_t ADCValue[3]={0};

void ADC_Config(void);

int main(void)
{
  ADC_Config();
  while (1)
  {
    
  }
}
void ADC_Config(void)
{
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;                     
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  DMA_InitStructure.DMA_Channel = DMA_Channel_0;   //  ho tro kenh 0
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&ADCValue;  // bien DMA_Memory0BaseAddr se chua dia chi bien adc
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&(ADC1->DR)); //gan dia chi thanh ghi chua gia tri chuyen doi adc vao bien  DMA_PeripheralBaseAddr
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory; //chon huong du lieu tu ngoai vi den bo nho
  DMA_InitStructure.DMA_BufferSize = 3;  
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; // neu bat thi dia chi ngoai vi se tang dan (khong quan tr )nguy hiemkhi khong nam ro dk dia chi tiep theo
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//vì có 3 ph?n tu nên nó co tác dung tang dia chi ô nho
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//chon kich thuoc thanh ghi chua du lieu ngoai vi  HalfWord(16bit)
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;// chon kich thuoc mang ADCValue là HalfWord
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;      //che do chuyen doi lien tuc
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;// thiet lap che do yeu tien cao 
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA2_Stream0, &DMA_InitStructure);

  /* DMA2_Stream0 enable */
  DMA_Cmd(DMA2_Stream0, ENABLE);
  
  
  /* ADC Common Init **********************************************************/
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;  // mode don co ban không su dung chuc nang dac biet
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2; // bo chia 2 lay mau o tan so cao nhat
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_10Cycles; // thoi gian tre giua 2 lan lay mau lien tiep
  ADC_CommonInit(&ADC_CommonInitStructure);
   
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b; // che do 12bit
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; // khong su dung convert  bang tin hieu ngoai
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; // canh le ben phai do thanh ghi 16 bit nhung do phan dai 12bit
  ADC_InitStructure.ADC_NbrOfConversion = 3; //so kenh chuyen doi 
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channels configuration */ 
  ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_84Cycles); 
  ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_84Cycles);  // thu tu 1 2 3 nghia la khi xay ra chuyen doi kenh theo thu tu 1 truoc
  ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_84Cycles); //  ADC_SampleTime_3Cycles thoi gian lay maucang lon thì tg lay mau cang lau
  
  /* Enable ADC1 DMA */
  ADC_DMACmd(ADC1, ENABLE);
       
  /* Enable DMA request after last transfer (Single-ADC mode) */
  ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
  
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);
  
  /* Start ADC1 Software Conversion */
  ADC_SoftwareStartConv(ADC1);
}
void USART1(void)
{
	volatile unsigned int IIR;
  uint8_t c2;
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) // Neu co ky tu moi trong bo dem nhan
	{
		IIR = USART1->SR;
		GPIO_WriteBit(GPIOB,GPIO_Pin_9,(BitAction)(0));
		c2=USART_ReceiveData(USART1); 
		if(i<100)
		{
			GPIO_WriteBit(GPIOB,GPIO_Pin_9,(BitAction)(0));
		    c2=USART_ReceiveData(USART1); 
		}
    else
    {
			i=0;
	  }
	}
}

void Delay(__IO uint32_t nCount)
{
  while(nCount--)
  {
  }
}
#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  while (1)
  {}
}
#endif

