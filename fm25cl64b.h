#ifndef __FM25CL64B_H_
#define __FM25CL64B_H_


/******************************************************************************
引脚别名定义
*******************************************************************************/			
sbit	E_SPI_CS	  = P7^4;	      //定义CS  
sbit	E_SPI_SCK	  = P7^7;	      //定义SCK
sbit	E_SPI_MOSI	= P7^5;	      //定义MOSI
sbit	E_SPI_MISO	= P7^6;	      //定义MISO

#define  SPI_CS_0      E_SPI_CS	    = 0 
#define  SPI_CS_1      E_SPI_CS	    = 1 
#define  SPI_SCK_0     E_SPI_SCK	  = 0 
#define  SPI_SCK_1     E_SPI_SCK	  = 1 
#define  SPI_MOSI_0    E_SPI_MOSI	  = 0  
#define  SPI_MOSI_1    E_SPI_MOSI	  = 1

#define WREN 0x06           //写使能
#define WRDI 0x04           //写无效
#define RDSR 0x05           //读状态寄存器
#define WRSR 0x01           //写状态寄存器
#define READD 0x03          //读存储器数据
#define WRITEE 0x02         //写存储器数据

#define uint16 uint
#define uint8 uchar

void FramWriteByte(uint16 address,uint8 da);
uint8 FramReadByte(uint16 address);

#endif
