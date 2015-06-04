#include"Sim_IIC.h"
 	void IIcDelay(uint16_t Perm)
	{
		uint8_t i ; 
		while(Perm--);
		{
			i =200 ;
			while(i--);
		}
	}

	void IIC_SimStart()
	{ 
		SDA = 1 ;
	 
		NOP(1);	    
		SCL = 1 ; //>4.7us
		NOP(5);
		SDA = 0 ; //> 4us 
		NOP(5);		
		SCL =0 ; //busy 
		NOP(5);		
	}
	void IIC_SimStop()
	{
		SDA = 0 ;
		NOP(1);		
		SCL = 1 ; //>4us
		NOP(5);		
		SDA = 1 ; 
		NOP(5);	
		SCL = 0;		
	}
//
uint8_t IIC_SimSend(uint8_t Perm)
	{
		uint8_t i ,ack; 
		
		for(i=0; i<8 ;i++)
		{
			SCL = 0 ;
		  if((Perm <<i) & 0x80)
			SDA=1;   
			else
			SDA=0; 	
			NOP(1);
			SCL = 1 ;
			NOP(5);		
			SCL = 0 ;
			NOP(1);
		 }
		    NOP(5);	
			NOP(1);
			NOP(1);
			SDA = 1; //prepare receive ack ；
			NOP(5);		
			SCL = 1;
			NOP(5);		
			if ( SDA==1)
			{
				SCL=0;  
				ack = 1;
			}
			else
			{
				SCL=0; 
				ack = 0;
			}
			NOP(5);		
		 return ack ;	
	}

uint8_t IIC_SimRead()
	{
	  uint8_t  retc; 
	  uint8_t  BitCnt; 
	  retc=0;  
	  SDA=1;           
	   /*置数据线为输入方式*/ 
	  for(BitCnt=0;BitCnt<8;BitCnt++) 
	      { 
	        NOP(1);            
	        SCL=0;       /*置时钟线为低，准备接收数据位*/ 
					NOP(5);		
	        SCL=1;       /*置时钟线为高使数据线上数据有效*/ 
	        NOP(1); 
	        NOP(1); 
	        retc=retc<<1; 
	        if(SDA==1)retc=retc+1; /*读数据位,接收的数据位放入retc中 */ 
	        NOP(1); 
	        NOP(1);  
	      } 
	  //SCL=0;     
	  NOP(1); 
	  NOP(1); 
	  return(retc);  
	}
	
void Ack_I2c(uint8_t a) 
{ 
		if(a==0)SDA=0;     /*在此发出应答或非应答信号*/ 
			else SDA=1; 
		NOP(1); 
		NOP(1); 
		NOP(1);       
		SCL=1; 
		NOP(5);		 
		SCL=0;                /*清时钟线，钳住I2C总线以便继续接收*/ 
		NOP(1); 
		NOP(1);     
} 


