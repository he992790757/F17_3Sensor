#define __KEYSCAN

#include "KeyScan.h"
#include "ucos_ii.h"
#include "stdint.h"
#include "config.h"
#include "global.h"
#include <stdio.h>


uint32_t 	press_time = 0 ;

uint8_t Judge_press(void)
{
	OSTimeDly(1);
	press_time++;
	if(press_time>140)
	{
		press_time=0;
		Keylong = 1 ; 
		GR_DBG_PRINTF("IN KeyLong\n\n") ; 
	}
	else Keylong = 0 ; 
	return Keylong ; 
}


uint8_t KeyScan()
{	
    press_time = 0 ; 
  	if(K1==0) 
	{
		OSTimeDly(2);
		if(K1==0)
		{
			 while(K1==0)
			 { 
				if(Judge_press()) break;	 		
			 }	
		    GR_DBG_PRINTF("Key Value is:1 \n\n"); 
			return 1 ;  
		}	
					    			 
	}
  	else if(K2==0) 
	{
		OSTimeDly(2);
		if(K2==0)
		{
			 while(K2==0)
			 { 
				if(Judge_press()) break;	 		
			 }		  		
		    GR_DBG_PRINTF("Key Value is:2 \n\n"); 
			return 2 ;  	
		}						    			 
	}	
  	else if(K3==0) 
	{
		OSTimeDly(2);
		if(K3==0)
		{
			 while(K3==0)
			 { 
				if(Judge_press()) break;	 		
			 }		  		
		    GR_DBG_PRINTF("Key Value is:3 \n\n"); 
			return 3 ;  
		}						    			 
	}	
  	else if(K4==0) 
	{
		OSTimeDly(2);
		if(K4==0)
		{
			 while(K4==0)
			 { 
				if(Judge_press()) break;	 		
			 }		  		
		    GR_DBG_PRINTF("Key Value is:4 \n\n"); 
			return 4 ;  
		}						     		 
	}	
  	else if(K5==0) 
	{
		OSTimeDly(2);
		if(K5==0)
		{
			 while(K5==0)
			 { 
				if(Judge_press()) break;	 		
			 }		  		
		    GR_DBG_PRINTF("Key Value is:5 \n\n"); 
			return 5 ;  	
		}						    			 
	}	
  	else if(K6==0) 
	{
		OSTimeDly(2);
		if(K6==0)
		{
			 while(K6==0)
			 { 
				if(Judge_press()) break;	 		
			 }		  		
		    GR_DBG_PRINTF("Key Value is:6 \n\n"); 
			return 6 ;  
		}						    			 
	}		
  	else if(K7==0) 
	{
		OSTimeDly(2);
		if(K7==0)
		{
			 while(K7==0)
			 { 
				if(Judge_press()) break;	 		
			 }		  		
		    GR_DBG_PRINTF("Key Value is:7 \n\n"); 
			return 7 ;  	
		}						    			 
	}	
  	else if(K8==0) 
	{
		OSTimeDly(2);
		if(K8==0)
		{
			 while(K8==0)
			 { 
				if(Judge_press()) break;	 		
			 }		  		
		    GR_DBG_PRINTF("Key Value is:8 \n\n"); 
			return 8 ;  
		}						    			 
	}
  	else if(K9==0) 
	{
		OSTimeDly(2);
		if(K9==0)
		{
			 while(K9==0)
			 { 
				if(Judge_press()) break;	 		
			 }		  		
		    GR_DBG_PRINTF("Key Value is:9 \n\n"); 
			return 9 ;  	
		}						    			 
	}	  
	return 0 ; 
}


