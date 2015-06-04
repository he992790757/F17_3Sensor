#define __EXT_DS1307

#include"DS1307.h"
#include "DrvI2C.h"
#include"time.h"
#include"stdio.h"
uint8_t testds1307 ; 
uint8_t  BcdToHex( uint8_t Num)
{
	uint8_t m ; 
	m = Num ; 
	if( Num <= 0x99 )
	{
		Num = (Num>>4)*10+(m&0x0F);   return Num;	
	}
	else return 0 ; 			    
		
}

uint8_t  HexToBcd( uint8_t Num)			 
{
	if( Num <= 99 )
	{
		Num = ((Num/10)<<4)|(Num%10);  
	}	
	return Num ;	
}
void DS1307_DatChg()
{
    uint8_t i ; 
 	date_dsp[0] = 0xed ; 
    for(i =0 ;i<7;i++)
	{
		date[i]=BcdToHex(date[i]) ; 
	}
	
	NowTime.year 	= date[6]+2000 ; 	
	NowTime.month 	= date[5]; 
	NowTime.day 	= date[4];
	NowTime.week	= date[3];
	NowTime.hour	= date[2]; 
	NowTime.min		= date[1]; 
	NowTime.sec		= date[0]; 
		
	date_dsp[1] = date[6];
    date_dsp[2] = date[5];
	date_dsp[3] = date[4];
	date_dsp[4] = date[2];
	date_dsp[5] = date[1];
	date_dsp[6] = date[0];

//	printf("systime is :%2d%2d%2d%2d%2d%2d  \n\n",date[6],date[5],date[4],date[2],date[1],date[0] );
}

//#define IIC_HD

void DS1307_Init()
{  
#ifdef	 IIC_HD
//	UNLOCKREG();    
	DrvGPIO_InitFunction(E_FUNC_I2C0);  	
   // DrvI2C_SetAddress(I2C_PORT0, 0, DS1307_ADDR, 0);
#endif 

}

uint8_t  DS1307_WR(volatile uint8_t* DATA)
{
	uint8_t Err,i ; 
	for(i=0;i<7;i++)
	{
#ifdef	 IIC_HD

	    DrvI2C_Open(I2C_PORT0, 100000);  
	    DrvI2C_Ctrl(I2C_PORT0, 1, 0, 0, 0); 		// 开始
		while(DrvI2C_GetIntFlag == 0 ); 			// while (I2C0->CON.SI == 0);	
		
		DrvI2C_WriteData(I2C_PORT0,DS1307_ADDR);			// I2C0->DATA = DS1307_ADDR;
		DrvI2C_Ctrl(I2C_PORT0, 0, 0, 1, 0);			// 设备
		while(DrvI2C_GetIntFlag == 0 ); 			// while( I2C0->CON.SI == 0 );
		
		DrvI2C_WriteData(I2C_PORT0,i);			//I2C0->DATA =  ADDR ;	
		DrvI2C_Ctrl(I2C_PORT0, 0, 0, 1, 0);			//地址
		while(DrvI2C_GetIntFlag == 0 ); 			//while( I2C0->CON.SI == 0 );
		
		DrvI2C_WriteData(I2C_PORT0,DATA[i]);			//I2C0->DATA = DATA ; 
		DrvI2C_Ctrl(I2C_PORT0, 0, 0, 1, 0);			//数据
		while(DrvI2C_GetIntFlag == 0 ); 			//while( I2C0->CON.SI == 0 );	
		
		DrvI2C_Ctrl(I2C_PORT0, 0, 1, 1, 0);			//停止
		DrvI2C_Close(I2C_PORT0);

#else			
		IIC_SimStart();										//start  bit 
		Err = IIC_SimSend(DS1307_ADDR);												
		Err = IIC_SimSend(i) ;
		Err = IIC_SimSend(DATA[i]);
		IIC_SimStop();		 
#endif 

  	}
  return Err; 

}
	
uint8_t DS1307_RD(volatile uint8_t* DATA)
{

	 uint8_t i ;
 	 for(i=0;i<7;i++)
	  {	
	  		date[i] = 0 ; 
		//	printf("date[i] is : %d\n\n",date[i]); 
#ifdef	 IIC_HD
			DrvI2C_Open(I2C_PORT0, 100000);  

		 	DrvI2C_Ctrl(I2C_PORT0, 1, 0, 0, 0);			//开始	
			while(DrvI2C_GetIntFlag == 0 ); 			//while (I2C0->CON.SI == 0);
		
			DrvI2C_WriteData(I2C_PORT0,DS1307_ADDR);			// I2C0->DATA = 0XA0;	
			DrvI2C_Ctrl(I2C_PORT0, 0, 0, 1, 0);			//设备
			while(DrvI2C_GetIntFlag == 0 ); 			//while( I2C0->CON.SI == 0 );		//poll si flag
		
			DrvI2C_WriteData(I2C_PORT0,i);			//I2C0->DATA = 0XA0;	
			DrvI2C_Ctrl(I2C_PORT0, 0, 0, 1, 0);			//设备地址
			while(DrvI2C_GetIntFlag == 0 ); 			//while( I2C0->CON.SI == 0 );		//poll si flag
		
			//send start flag
			DrvI2C_Ctrl(I2C_PORT0, 1, 0, 1, 0);			//clr si and send start	开始
			while(DrvI2C_GetIntFlag == 0 ); 			//while( I2C0->CON.SI == 0 );		//poll si flag
		
			//send read command
			DrvI2C_WriteData(I2C_PORT0,(DS1307_ADDR<<1)|0x01); //I2C0->DATA = 0XA1;
			DrvI2C_Ctrl(I2C_PORT0, 0, 0, 1, 0);			//clr si 读设备
			while(DrvI2C_GetIntFlag == 0 ); 			//while( I2C0->CON.SI == 0 );		//poll si flag
		
			DrvI2C_WriteData(I2C_PORT0,0x00); 			//I2C0->DATA = 0X00;
			DrvI2C_Ctrl(I2C_PORT0, 0, 0, 1, 0);			//clr si and set ack	
			while(DrvI2C_GetIntFlag == 0 ); 			//while( I2C0->CON.SI == 0 );		//poll si flag读
			DATA[i] = DrvI2C_ReadData(I2C_PORT0);							//flash_data=I2C0->DATA;
		
		 	DrvI2C_Ctrl (I2C_PORT0, 0, 1, 1, 0);    		//clr si and set stop停止
			DrvI2C_Close(I2C_PORT0);
#else
			IIC_SimStart();
			IIC_SimSend(DS1307_ADDR);
			IIC_SimSend(i) ;
			IIC_SimStop();
	
			IIC_SimStart();
			IIC_SimSend(DS1307_ADDR+1); //READ DS1307
			DATA[i]=IIC_SimRead(); 
			Ack_I2c(1);
			IIC_SimStop();
 #endif 
  	  }	
    DS1307_DatChg(); 	
  return 0 ;

}


