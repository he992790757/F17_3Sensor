 #define __EXT_TIME__
 #include "time.h"


uint16_t monthDayCount(tm time)
{
 		uint16_t i=0 ; 
		switch(time.month)
			{ 
			case 12 : i+=30 ;
			case 11	: i+=31 ;	
			case 10 : i+=30 ;	
			case 9 : i+=31 ;
			case 8 : i+=31 ;
			case 7 : i+=30 ;
			case 6 : i+=31 ;
			case 5 : i+=30 ;
			case 4 : i+=31 ;
			case 3 : if(time.year%4){i+=28 ;}else{i+= 29;} 
			case 2 : i+=31 ; 
			case 1 : i+=0; 
			default:break; 
		}
		return i ; 
 }
 
 uint16_t yearDayCount(tm time) //基于2011.1.1 0:0:0
 	{
 		uint16_t i=0 ; 
		//
		i = (time.year - 2011)*365 + (time.year-1)/4-502 ;  
		return i ; 
 }


uint32_t sTime(tm time)
 	{
		uint32_t i =0 ; 
		if(time.year<2011) return 0 ; //时间设置不正确
		
		i = ((uint32_t)yearDayCount(time)+ (uint32_t)monthDayCount(time)+(uint32_t)time.day-1)*24*2600 
			+(uint32_t) time.hour*3600 + (uint32_t) time.min *60 + (uint32_t)time.sec ; 

		return i ; 
 }









