#ifndef __FM25CL64B_H_
#define __FM25CL64B_H_


/******************************************************************************
���ű�������
*******************************************************************************/			
sbit	E_SPI_CS	  = P7^4;	      //����CS  
sbit	E_SPI_SCK	  = P7^7;	      //����SCK
sbit	E_SPI_MOSI	= P7^5;	      //����MOSI
sbit	E_SPI_MISO	= P7^6;	      //����MISO

#define  SPI_CS_0      E_SPI_CS	    = 0 
#define  SPI_CS_1      E_SPI_CS	    = 1 
#define  SPI_SCK_0     E_SPI_SCK	  = 0 
#define  SPI_SCK_1     E_SPI_SCK	  = 1 
#define  SPI_MOSI_0    E_SPI_MOSI	  = 0  
#define  SPI_MOSI_1    E_SPI_MOSI	  = 1

#define WREN 0x06           //дʹ��
#define WRDI 0x04           //д��Ч
#define RDSR 0x05           //��״̬�Ĵ���
#define WRSR 0x01           //д״̬�Ĵ���
#define READD 0x03          //���洢������
#define WRITEE 0x02         //д�洢������

#define uint16 uint
#define uint8 uchar

void FramWriteByte(uint16 address,uint8 da);
uint8 FramReadByte(uint16 address);

#endif
