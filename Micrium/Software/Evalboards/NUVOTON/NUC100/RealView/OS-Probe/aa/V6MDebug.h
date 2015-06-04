#ifndef INC__V6MDEBUG_H__
#define INC__V6MDEBUG_H__
#ifdef __cplusplus
extern "C"
{
#endif
#ifdef __V6MDEBUG
#define V6MDEBUG_EXT
#else
#define  V6MDEBUG_EXT extern 
#endif 

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "DrvUSB.h"

V6MDEBUG_EXT volatile Status  MCU_Status;			//类型定义结构体	
V6MDEBUG_EXT volatile USB_DATAS USB_DATA;
V6MDEBUG_EXT 	void (*ptr)(); 
    /*---------------------------------------------------------------------------------------------------------*/
    /*                                                                                                         */
    /* Copyright (c) Nuvoton Technology Corp. All rights reserved.                                             */
    /*                                                                                                         */
    /*---------------------------------------------------------------------------------------------------------*/

#define V6M_CMD_RESET_CMD_SRIAL	0xFFFFFFFFUL

#define V6M_CMD_TOP_W		0x03UL
#define V6M_CMD_SIDE_W		0x04UL
#define V6M_CMD_IR_850		0x05UL
#define V6M_CMD_IR_940		0x06UL
#define V6M_CMD_UV_365		0x07UL
#define V6M_CMD_SIDE_IR		0x08UL
#define V6M_CMD_SIDE_IR_90	0xB8UL
#define V6M_CMD_BOT_W		0x09UL
#define V6M_CMD_BOT_IR		0x0AUL
#define V6M_CMD_COUN_PIC	0x0BUL

#define V6M_CMD_Left		0x0DUL
#define V6M_CMD_Up			0x0EUL
//#define V6M_CMD_USB_U		0x0FUL		 	//u盘

#define V6M_CMD_Down		0x10UL

#define V6M_CMD_Right		0x12UL
#define V6M_CMD_ZoomUp		0x13UL
#define V6M_CMD_ZoomDown	0x14UL		   //
#define V6M_CMD_Photo		0x15UL		   //拍照
#define V6M_CMD_Del_Photo	0x16UL		   //删除单张
#define V6M_CMD_PhotoLong	0x17UL		   //删除全部
#define V6M_CMD_OverView	0x18UL		   //全幅
#define V6M_CMD_PartView	0x19UL		   //局部
#define V6M_CMD_SpecView	0x1AUL		   //细节局部
#define V6M_CMD_C608		0x1BUL		   //c608
#define V6M_CMD_HDMI		0x1CUL		   // HDMI
#define V6M_CMD_HDMI_OUT	0x1DUL		   // 退出HDMI
#define V6M_CMD_RESET		0x1EUL		   // 复位系统
#define V6M_CMD_FORMAT_SD	0x1FUL		   // 格式化SD
#define V6M_CMD_RESET_DSP	0x20UL		   // 复位DSP
#define V6M_CMD_IR_940_test	0x21UL

//#define V6M_CMD_SHARPNESS  	0x21UL			//锐度
//#define V6M_CMD_CONTRAST	0x22UL			//对比度
//#define V6M_CMD_SATURATION	0x23UL			//饱和度
//#define V6M_CMD_BRIGHTNESS	0x24UL			//亮度



#define V6M_CMD_View		0x33UL		   //预览
#define V6M_CMD_Play		0x34UL		   //回放
#define V6M_CMD_SL			0x35UL		   //休眠
#define V6M_CMD_WU			0x36UL		   //唤醒
#define V6M_CMD_FZ			0x37UL		   //照片分组，连拍用

#define V6M_CMD_SLP_DIS		0x38UL		   //禁用休眠
#define V6M_CMD_SLP_EN		0x39UL		   //启动休眠


//=============查询=======================
#define V6M_CMD_C_Sys_Inf	0x80UL		   //系统信息
#define V6M_CMD_C_Mac_Ver	0x81UL		   //机器型号
#define V6M_CMD_C_Pro_Num	0x82UL		   //产品序列号
#define V6M_CMD_C_Mac_Num	0x83UL		   //机器编号
#define V6M_CMD_C_Sof_Ver	0x84UL		   //软件版本
#define V6M_CMD_C_Pro_Dat	0x85UL		   //生产日期

//=============修改=======================
#define V6M_CMD_M_Mac_Ver	0x86UL		   //机器型号
#define V6M_CMD_M_Pro_Num	0x87UL		   //产品序列号
#define V6M_CMD_M_Mac_Num	0x88UL		   //机器编号
#define V6M_CMD_M_Sof_Ver	0x89UL		   //软件版本
#define V6M_CMD_M_Hrd_Ver	0x8CUL		   //硬件版本
#define V6M_CMD_M_Pro_Dat	0x8AUL		   //生产日期


#define V6M_CMD_AlarmSound	0x8FUL		   //机器报警声音控制


#define V6M_CMD_Check_Stat	0x90UL		   //查询系统状态
#define V6M_CMD_USB_U		0x91UL		   //进入U盘模式  
#define V6M_CMD_USB_U_Out	0x92UL		   //退出U盘模式
#define V6M_CMD_USB_PC		0x93UL		   //进入PC-CAM
#define V6M_CMD_USB_PC_Out	0x94UL		   //退出PC-CAM

//=============指令=======================
#define V6M_CMD_ZHUANFA		0xA0UL		   //转发指令
#define V6M_CMD_PASSWRD		0xA1UL		   // 恢复原厂密码	
#define V6M_CMD_SETTIME		0xA2UL		   // 设置时间	
#define V6M_CMD_SETUVC		0xA3UL		   // 设置紫光曝光值
#define V6M_CMD_UNLOCK_TM	0xA4UL		   // 取消输入错误锁定
#define V6M_CMD_SETUVC71	0xA6UL		   // 设置sen2紫光曝光值
#define V6M_CMD_SETUVC72	0xA7UL		   // 设置sen3紫光曝光值
#define V6M_CMD_C_Hrd_Ver	0xA8UL		   // 硬件版本 


#define V6M_CMD_Chk_Phot	0xA9UL		   // 请进一步检查 
#define V6M_CMD_Ext_Black	0xAAUL		   // 退出黑屏显示字符
#define V6M_CMD_Chk_Phot_2	0xABUL		   // 可疑， 请进一步检查
#define	V6M_CMD_Sign_Cnt	0xACUL		   // 签发
#define	V6M_CMD_Sign_Chk	0xADUL		   // 审验
#define	V6M_CMD_Sign_F1  	0xAEUL		   // F1功能 
#define	V6M_CMD_Sign_F2  	0xAFUL		   // F2功能 
#define	V6M_CMD_Sign_F3  	0xB0UL		   // F3功能 
#define	V6M_CMD_Sign_F4  	0xB1UL		   // F4功能 

#define V6M_CMD_SIDE_W_90   0xB4UL			//侧白光（前方）
#define V6M_CMD_Photo_Four  0xB5UL		   	//4连拍
#define V6M_CMD_AUTO_VIEW	0xB6UL	  		//自动预览
#define V6M_CMD_PH_ARGV	    0xB7UL	  		//照片参数设定

#define V6M_CMD_AutoExposure 0xB9UL		   	//  校正
#define V6M_CMD_PH_ADJUST	 0xBAUL	  		//照片参数设定 用于每种光源调整,查看


#define V6M_CMD_PH_NUM	 	 0xBCUL	  		//用于软件修改本机照片数量的值
#define V6M_CMD_PH_NUM_Dec 	 0xBDUL	  		//用于软件修改本机照片数量的减数
#define V6M_CMD_XY_ZOOM      0xBFUL		   	//用USB看坐标 位置放大
#define V6M_CMD_C_Sign_NUM	 0xC0UL		    // 签发数量 

#define V6M_CMD_UV_365_EX1		0xC1UL		//紫光手动曝光值1
#define V6M_CMD_UV_365_EX2		0xC2UL		//紫光手动曝光值2

#define V6M_CMD_Photo_Eight  0xC5UL		   	//8连拍

#define V6M_CMD_DeepComPs    0xC6UL               //设置拍照等级



int32_t DrvFMC_Read(uint32_t u32addr, uint32_t * u32data);
int32_t DrvFMC_Erase(uint32_t u32addr);
int32_t DrvFMC_Write(uint32_t u32addr, uint32_t u32data);
int32_t DrvFMC_WriteConfig(uint32_t u32data0, uint32_t u32data1);
void DrvFMC_DisableISP(void);
void DrvFMC_EnableISP(void);

#define V6M_MAX_COMMAND_LENGTH	(HID_MAX_PACKET_SIZE_EP0-2)

    uint32_t LED_on(const uint8_t *pu8Buffer, uint32_t u32Len, uint8_t u8LedNum);
    uint32_t LED_off(const uint8_t *pu8Buffer, uint32_t u32Len, uint8_t u8LedNum);
    void V6M_ProcessCommand(const uint8_t *pu8Buffer, uint32_t u32Len);


#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
