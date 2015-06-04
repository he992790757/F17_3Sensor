#ifndef _FUC_PH_H_
#define _FUC_PH_H_
#include "stdint.h"

#ifndef __FUC_PH__
#define _FUC_PH_EXT  extern 
#else 
#define _FUC_PH_EXT 
#endif 

typedef  struct
{
	uint8_t length ; 
	uint8_t sence ; 
	uint8_t senceMode; 
	uint8_t ISO; 
	uint8_t TG; 
	uint8_t WB1;
	uint8_t WB2; 
	uint8_t sharpness;  //锐度
	uint8_t brightness; //亮度
	uint8_t saturation; //饱和度
	uint8_t contrast;   //对比度
	uint8_t compress ;  //压缩等级
	uint8_t phScale;    // 照片比例
	uint8_t phSize;     // 照片大小
	uint8_t fwdNum;     // 方向字符
//	uint8_t *p  ;       // 字符 	
}PH_SENCE; 

typedef struct 
{
	uint8_t length ;
	uint8_t sence ; 
	uint8_t phTotal ;
	uint8_t ScNum1; 
	uint8_t ScNum2; 
	uint8_t ScNum3; 
	uint8_t ScNum4; 
	uint8_t ScNum5; 
	uint8_t ScNum6; 
	uint8_t ScNum7; 
	uint8_t ScNum8; 

}PH_MODE; 

_FUC_PH_EXT   PH_SENCE   ph_sence[8]; 
_FUC_PH_EXT  PH_MODE    ph_mode[8]; 


#endif /*_FUC_PH_H_*/


