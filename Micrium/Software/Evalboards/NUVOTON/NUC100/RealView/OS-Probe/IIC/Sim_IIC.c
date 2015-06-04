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
			SDA = 1; //prepare receive ack ��
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
	   /*��������Ϊ���뷽ʽ*/ 
	  for(BitCnt=0;BitCnt<8;BitCnt++) 
	      { 
	        NOP(1);            
	        SCL=0;       /*��ʱ����Ϊ�ͣ�׼����������λ*/ 
					NOP(5);		
	        SCL=1;       /*��ʱ����Ϊ��ʹ��������������Ч*/ 
	        NOP(1); 
	        NOP(1); 
	        retc=retc<<1; 
	        if(SDA==1)retc=retc+1; /*������λ,���յ�����λ����retc�� */ 
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
		if(a==0)SDA=0;     /*�ڴ˷���Ӧ����Ӧ���ź�*/ 
			else SDA=1; 
		NOP(1); 
		NOP(1); 
		NOP(1);       
		SCL=1; 
		NOP(5);		 
		SCL=0;                /*��ʱ���ߣ�ǯסI2C�����Ա��������*/ 
		NOP(1); 
		NOP(1);     
} 


