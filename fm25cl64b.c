#include "fm25cl64b.h"	

/**************************************************************************************
 * 描  述 : 延时函数
 * 入  参 : 无
 * 返回值 : 无
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
 * 描  述 : 模拟SPI写入一个字节
 * 入  参 : uint8 date
 * 返回值 : 无
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
 * 描  述 : 模拟SPI读取一个字节
 * 入  参 : 无
 * 返回值 : 读取uint8数据
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
 * 描  述 : 向指定地址存入数据
 * 入  参 : uint16 address写入的地址,uint8  da写入的数据
 * 返回值 : 无
 **************************************************************************************/
void FramWriteByte(uint16 address,uint8  da)
{
  uint8 temM,temL;

  temM=(uint8)((address&0xff00)>>8);
  temL=(uint8)(address&0x00ff);

 	SPI_CS_0;  
  SPI_WriteByte(WREN);          //写使能FRAM    
  SPI_CS_1;
  delay_80us();

  SPI_CS_0;
  SPI_WriteByte(WRITEE);        //写数据到FRAM存储器命令
  SPI_WriteByte(temM);          //写存储器地址高8位
  SPI_WriteByte(temL);          //写存储器地址低8位
  SPI_WriteByte(da);            //写入要存入的数据
  SPI_CS_1;
  delay_80us();
	
  SPI_CS_0;
  SPI_WriteByte(WRDI);           //写无效FRAM
  SPI_CS_1;
}

/**************************************************************************************
 * 描  述 : 向指定地址读取数据
 * 入  参 : uint16 address要读取的地址
 * 返回值 : 返回读取到的数据uint8
 **************************************************************************************/
uint8 FramReadByte(uint16 address)
{
  uint8  temp,temM,temL;

  temM=(uint8)((address&0xff00)>>8);
  temL=(uint8)(address&0x00ff);

  SPI_CS_0;           
  SPI_WriteByte(READD);      //读存储器命令下发
  SPI_WriteByte(temM);       //待读地址高位下发
  SPI_WriteByte(temL);       //待读地址低位下发
  temp = SPI_ReadByte();     //读存储器数据
  SPI_CS_1;   
	
  return temp;
}

/*********************************END FILE********************************************/	

