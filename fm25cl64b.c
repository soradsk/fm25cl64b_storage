#include "fm25cl64b.h"	

/**************************************************************************************
 * ��  �� : ��ʱ����
 * ��  �� : ��
 * ����ֵ : ��
 **************************************************************************************/
void delay_80us(void)
{
  uint8 i;

  for (i = 0; i < 8; i++) 
	{
		 Delay_us(10);
  }               
}
void Delay10us()
{
	Delay_us(10);
}
/**************************************************************************************
 * ��  �� : ģ��SPIд��һ���ֽ�
 * ��  �� : uint8 date
 * ����ֵ : ��
 **************************************************************************************/
void SPI_WriteByte(uint8 date)
{
  uint8 temp,i;
  temp = date;  

  for (i = 0; i < 8; i++) 
	{
     SPI_SCK_0;
		 Delay10us();
     if((temp&0x80)==0x80)
     { SPI_MOSI_1; }
     else 
     { SPI_MOSI_0; }
     SPI_SCK_1 ;
		 Delay10us();
     temp <<= 1;
   }
   SPI_MOSI_0;                
}

/**************************************************************************************
 * ��  �� : ģ��SPI��ȡһ���ֽ�
 * ��  �� : ��
 * ����ֵ : ��ȡuint8����
 **************************************************************************************/
uint8 SPI_ReadByte(void)
{
  uint8 temp=0;
  uint8 i;
                  
  for(i = 0; i < 8; i++)
	{
    temp <<= 1;
    SPI_SCK_0 ;        
    Delay10us();
		if(E_SPI_MISO) 
    {temp++; }
    SPI_SCK_1 ;
		Delay10us();
   }
   return(temp);
}

/**************************************************************************************
 * ��  �� : ��ָ����ַ��������
 * ��  �� : uint16 addressд��ĵ�ַ,uint8  daд�������
 * ����ֵ : ��
 **************************************************************************************/
void FramWriteByte(uint16 address,uint8  da)
{
  uint8 temM,temL;

  temM=(uint8)((address&0xff00)>>8);
  temL=(uint8)(address&0x00ff);

 	SPI_CS_0;  
  SPI_WriteByte(WREN);          //дʹ��FRAM    
  SPI_CS_1;
  delay_80us();

  SPI_CS_0;
  SPI_WriteByte(WRITEE);        //д���ݵ�FRAM�洢������
  SPI_WriteByte(temM);          //д�洢����ַ��8λ
  SPI_WriteByte(temL);          //д�洢����ַ��8λ
  SPI_WriteByte(da);            //д��Ҫ���������
  SPI_CS_1;
  delay_80us();
	
  SPI_CS_0;
  SPI_WriteByte(WRDI);           //д��ЧFRAM
  SPI_CS_1;
}

/**************************************************************************************
 * ��  �� : ��ָ����ַ��ȡ����
 * ��  �� : uint16 addressҪ��ȡ�ĵ�ַ
 * ����ֵ : ���ض�ȡ��������uint8
 **************************************************************************************/
uint8 FramReadByte(uint16 address)
{
  uint8  temp,temM,temL;

  temM=(uint8)((address&0xff00)>>8);
  temL=(uint8)(address&0x00ff);

  SPI_CS_0;           
  SPI_WriteByte(READD);      //���洢�������·�
  SPI_WriteByte(temM);       //������ַ��λ�·�
  SPI_WriteByte(temL);       //������ַ��λ�·�
  temp = SPI_ReadByte();     //���洢������
  SPI_CS_1;   
	
  return temp;
}

/*********************************END FILE********************************************/	

