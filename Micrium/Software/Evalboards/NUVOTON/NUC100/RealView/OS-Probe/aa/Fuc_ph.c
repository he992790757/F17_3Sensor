#define  __FUC_PH__
#include "fuc_ph.h"
#include "stdint.h"
#include "Driver\DrvUART.h" 
#include "Driver\DrvGPIO.h" 
#include "Driver\DrvSYS.h" 
#include "NUC1xx.h" 
#include "communication.h" 
#include <ucos_ii.h>
#include "config.h"
#include "DrvUSB.h"			
#include "V6MDebug.h"

 PH_SENCE  ph_sence[8] =
{
	{
	 0x0E,	 //	长度
	 0x01,	 //	场景
	 0x01,	 //	场景模式
	 0x08,	 //	ISO
	 0x16, 	 // 曝光时间

	 0xA6,	// //白平衡
	 0x7E, 	//

	 0x80,	// //锐度
	 0x80,	// //亮度
	 0x6a, 	// //饱和度
	 0x80, 	// //对比度

	 0x06, //  //压缩等级
	 0x00, //  // 照片比例
	 0x01, //  // 照片大小
	 0x01, //  // 方向字符
//	 0, //  // 字符     	
	},  
	{
	 0x0E,	 //	长度
	 0x02,	 //	场景
	 0x03,	 //	场景模式
	 0x10,	 //	ISO
	 0x30, 	 // 曝光时间

	 0x48,	// //白平衡
	 0xC0, 	//


	 0x90,	// //锐度
	 0x80,	// //亮度
	 0x6a, 	// //饱和度
	 0x80, 	// //对比度

	 0x06, //  //压缩等级
	 0x00, //  // 照片比例
	 0x01, //  // 照片大小
	 0x01, //  // 方向字符
//	 0, //  // 字符     		
	}, 
	{
	 0x0E,	 //	长度
	 0x03,	 //	场景
	 0x02,	 //	场景模式
	 0x40,	 //	ISO
	 0x30, 	 // 曝光时间

	 0x00,	// //白平衡
	 0x00, 	//

	 0x90,	// //锐度
	 0x80,	// //亮度
	 0x80, 	// //饱和度
	 0x80, 	// //对比度

	 0x06, //  //压缩等级
	 0x00, //  // 照片比例
	 0x01, //  // 照片大小
	 0x01, //  // 方向字符
//	 0, //  // 字符   		
	}, 
	{
	 0x0E,	 //	长度
	 0x04,	 //	场景
	 0x01,	 //	场景模式
	 0x30,	 //	ISO
	 0x32, 	 // 曝光时间

	 0xA0,	// //白平衡  
	 0x70, 	//         

	 0xB1,	// //锐度 
	 0x70,	// //亮度
	 0xA0, 	// //饱和度
	 0x00, 	// //对比度

	 0x06, //  //压缩等级
	 0x00, //  // 照片比例
	 0x01, //  // 照片大小
	 0x01, //  // 方向字符
//	 0, //  // 字符     		
	}, 
}	;

PH_MODE ph_mode[8] =
{
	{
	 0x10,		// length ;
	 0x01,		// sence ; 
	 0x04,		// phTotal ;
	 0x01,		// ScNum1; 
	 0x02,		// ScNum2; 
	 0x03,		// ScNum3; 
	 0x04,		// ScNum4; 
	 0x01,		// ScNum5; 
	 0x01,		// ScNum6; 
	 0x01,		// ScNum7; 
	 0x01,		// ScNum8; 		
	}  ,

} ;






