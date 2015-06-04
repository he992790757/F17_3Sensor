#define __V6MDEBUG


#include "V6MDebug.h"
#include "DrvGPIO.h"
#include "DrvSys.h"
#include "DrvUART.h"
#include "HIDSysIO.h"
#include "HID_API.h"
#include "config.h"
//#include "led.h"
//#include "DS1307.h"
#include "Led.h"
#include "communication.h" 
#include "global.h"
#include "performance.h"
#include "dspperf.h"
//#include "keyscan.h"
//extern uint8_t ATUO_UV1[] ;	
//extern uint8_t ATUO_UV2[] ;	

//extern volatile uint8_t USB_COMM;

//extern uint8_t KeyScan(void);
//extern void SendByte(uint8_t data);
//extern void USB_SendBackData(uint8_t bError, const uint8_t *pu8Buffer, uint32_t u32Size);
//void DSP_SEND_USB(uint8_t cnt, uint8_t *DSP_DATA);
// extern volatile uint32_t	SysData[18];					   //系统信息存储	


//volatile uint8_t Struct_Status;		//指令执行状态，00接收成功，01执行成功，02失败，03其他
//volatile uint8_t Sys_Status;		//系统状态，01 U盘 02 PC-CAM 03机器显示状态（接了USB）
//volatile uint8_t Sen_Status;		//sensor状态，01 全幅 02 局部 03 细节局部 04 C608 
//volatile uint8_t Scale_Status;		//显示比例状态，01 16:9  02 4:3 
//volatile uint8_t Menu_Status;		//菜单状态，01 预览模式 02 回放 03其他
//volatile uint8_t SD_Status;			//SD卡状态，01 插入 02 拔出 

static void VCMD_AckCommand(uint32_t u32Errno, const uint8_t *pu8Buffer, uint32_t u32Len)
{
    USB_SendBackData((u32Errno == 0 ? FALSE : TRUE), pu8Buffer, u32Len);
}

static uint32_t VCMD_WillResetCommandSerial(const uint8_t *pu8Buffer, uint32_t u32Len)
{
    return 0;	//Reset in V6M_ProcessCommand
}

static uint32_t V6M_ProcessOneCommand(const uint8_t *pu8Buffer, uint32_t u32Len)
{
    uint8_t u32Cmd[18];					 //最大指令包长度
	uint8_t	 temp[2];

	memcpy(&temp, pu8Buffer, 2);			 //ISP

//   GR_DBG_PRINTF("%d",temp[0]);
//   GR_DBG_PRINTF("%d",temp[1]);
//   GR_DBG_PRINTF("%d",temp[2]);
//   GR_DBG_PRINTF("%d",temp[3]);
//   GR_DBG_PRINTF("receive data");
   if((temp[0]==0x03)&&(temp[1]==0x04))
   { 	
/***********************FMC配置**************************/
			UNLOCKREG();

			DrvFMC_EnableISP();
		
			DrvFMC_WriteConfig (0xFFFFFF7E, 0x1E000);
		
			DrvFMC_Erase (0x1F000); 
		
			DrvFMC_Write (0x1F000, 0x12345678); 
		
			DrvFMC_DisableISP();
		
			CPU_RST();		//CPU复位
/***********************end**************************/
	}
    memcpy(&u32Cmd, pu8Buffer, sizeof(u32Cmd));
	if(u32Cmd[0]==0x47)							  //G
	{
		if(u32Cmd[1]==0x52)						  //R
		{
			if(u32Cmd[3]==0x23)					
			{
			    switch (u32Cmd[4])
			    {
				    case V6M_CMD_TOP_W:
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_TOP_W );//	 3
				
				    case V6M_CMD_SIDE_W:
				        return LED_on(pu8Buffer, u32Len,V6M_CMD_SIDE_W );
				    case V6M_CMD_SIDE_W_90:
				        return LED_on(pu8Buffer, u32Len,V6M_CMD_SIDE_W_90 );					
				
				    case V6M_CMD_IR_850:
				        return LED_on(pu8Buffer, u32Len,V6M_CMD_IR_850 );
				
				    case V6M_CMD_IR_940:
				        return LED_on(pu8Buffer, u32Len,V6M_CMD_IR_940 );
	
				    case V6M_CMD_IR_940_test:
				        return LED_on(pu8Buffer, u32Len,V6M_CMD_IR_940_test );
				
				    case V6M_CMD_UV_365:
				        return LED_on(pu8Buffer, u32Len,V6M_CMD_UV_365);
				    case V6M_CMD_UV_365_EX1:
				        return LED_on(pu8Buffer, u32Len,V6M_CMD_UV_365_EX1);
				    case V6M_CMD_UV_365_EX2:
				        return LED_on(pu8Buffer, u32Len,V6M_CMD_UV_365_EX2);										
				    case V6M_CMD_SIDE_IR:
				        return LED_on(pu8Buffer, u32Len,V6M_CMD_SIDE_IR );
	
				    case V6M_CMD_SIDE_IR_90:
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_SIDE_IR_90);			
				    case V6M_CMD_BOT_W:
				        return LED_on(pu8Buffer, u32Len,V6M_CMD_BOT_W );
				
				    case V6M_CMD_BOT_IR:
				        return LED_on(pu8Buffer, u32Len,V6M_CMD_BOT_IR );
				
				    case V6M_CMD_COUN_PIC:
				        return LED_on(pu8Buffer, u32Len,V6M_CMD_COUN_PIC );
				
				//=================	上面7个按键============
				
					case V6M_CMD_Left:
				        return LED_on(pu8Buffer, u32Len,V6M_CMD_Left );
				
					case V6M_CMD_Up:
				        return LED_on(pu8Buffer, u32Len,V6M_CMD_Up );
				
				//	case V6M_CMD_UpLong:
				//        return LED_on(pu8Buffer, u32Len, 15);
				
					case V6M_CMD_Down:
				        return LED_on(pu8Buffer, u32Len,V6M_CMD_Down );
				
				//	case V6M_CMD_DownLong:									 //
				//        return LED_on(pu8Buffer, u32Len, 17);
				
					case V6M_CMD_Right:
				        return LED_on(pu8Buffer, u32Len,V6M_CMD_Right );
				
					case V6M_CMD_ZoomUp:
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_ZoomUp);
				
					case V6M_CMD_ZoomDown:
				        return LED_on(pu8Buffer, u32Len,V6M_CMD_ZoomDown );
				
				//	case V6M_CMD_ZoomLong:
				//        return LED_on(pu8Buffer, u32Len, 21);
				
					case V6M_CMD_Photo:
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_Photo);
					case V6M_CMD_Photo_Four :
						
				        return LED_on(pu8Buffer, u32Len,V6M_CMD_Photo_Four );	
					case V6M_CMD_AUTO_VIEW:
						
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_AUTO_VIEW);						
					case V6M_CMD_Del_Photo:
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_Del_Photo);
				
					case V6M_CMD_PhotoLong:
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_PhotoLong);
	
					case V6M_CMD_FORMAT_SD:
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_FORMAT_SD);
					case V6M_CMD_RESET_DSP:
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_RESET_DSP);
						
				
				//=====================视场调节==================
				
					case V6M_CMD_OverView:							   	//全幅
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_OverView);
				
					case V6M_CMD_PartView:							   	//局部
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_PartView);
				
					case V6M_CMD_SpecView:							   	//细节局部
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_SpecView);
				
				 	case V6M_CMD_C608:							   		//c608
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_C608);
				
					case V6M_CMD_HDMI:							  		//HDMI
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_HDMI);
				
					case V6M_CMD_HDMI_OUT:							  	//退出HDMI
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_HDMI_OUT);
				
					case V6M_CMD_RESET:							  		// 复位系统
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_RESET);
				
				//=============查询=======================
					case V6M_CMD_C_Sys_Inf:							   	//系统信息
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_C_Sys_Inf);
				
					case V6M_CMD_C_Mac_Ver:							  	//机器型号
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_C_Mac_Ver);
				
					case V6M_CMD_C_Pro_Num:							  	//产品序列号
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_C_Pro_Num);
				
					case V6M_CMD_C_Mac_Num:							  	//机器编号
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_C_Mac_Num);
				
					case V6M_CMD_C_Sof_Ver:							  	//软件版本
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_C_Sof_Ver);
					case V6M_CMD_C_Hrd_Ver:							  	//生产日期
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_C_Hrd_Ver);				
					case V6M_CMD_C_Pro_Dat:							  	//生产日期
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_C_Pro_Dat);
				//=============修改=======================
					case V6M_CMD_M_Mac_Ver:							  	//机器型号
					{ 
						System.Sys.Data.info.MachineType[0]  =	((uint32_t)u32Cmd[5] <<24) + ((uint32_t)u32Cmd[6] <<16)+ ((uint32_t)u32Cmd[7] <<8)+(uint32_t)u32Cmd[8];
						System.Sys.Data.info.MachineType[1]  =	((uint32_t)u32Cmd[9] <<24) + ((uint32_t)u32Cmd[10] <<16)+( (uint32_t)u32Cmd[11] <<8)+(uint32_t)u32Cmd[12];
						System.Sys.Data.info.MachineType[2]  =	((uint32_t)u32Cmd[13] <<24) + ((uint32_t)u32Cmd[14] <<16)+( (uint32_t)u32Cmd[15] <<8)+(uint32_t)u32Cmd[16];
						return LED_on(pu8Buffer, u32Len, V6M_CMD_M_Mac_Ver);
					}
				    case V6M_CMD_DeepComPs:
					{
						DeepCompression	=  u32Cmd[5] ; 
					  	return LED_on(pu8Buffer, u32Len, V6M_CMD_DeepComPs);
					}    
					case V6M_CMD_M_Pro_Num:							  	//产品序列号
					{
						System.Sys.Data.info.CdKey[0] =	((uint32_t)u32Cmd[5] <<24) + ((uint32_t)u32Cmd[6] <<16)+ ((uint32_t)u32Cmd[7] <<8)+(uint32_t)u32Cmd[8];
						System.Sys.Data.info.CdKey[1] =	((uint32_t)u32Cmd[9] <<24) + ((uint32_t)u32Cmd[10] <<16)+( (uint32_t)u32Cmd[11] <<8)+(uint32_t)u32Cmd[12];
						System.Sys.Data.info.CdKey[2] =	((uint32_t)u32Cmd[13] <<24) + ((uint32_t)u32Cmd[14] <<16)+( (uint32_t)u32Cmd[15] <<8)+(uint32_t)u32Cmd[16];
						return LED_on(pu8Buffer, u32Len, V6M_CMD_M_Pro_Num);
					}
				       
				
					case V6M_CMD_M_Mac_Num:							    //机器编号
					{
						System.Sys.Data.info.MachineNum[0] = ((uint32_t)u32Cmd[5] <<24) + ((uint32_t)u32Cmd[6] <<16)+ ((uint32_t)u32Cmd[7] <<8)+(uint32_t)u32Cmd[8];
						System.Sys.Data.info.MachineNum[1]= ((uint32_t)u32Cmd[9] <<24) + ((uint32_t)u32Cmd[10] <<16)+( (uint32_t)u32Cmd[11] <<8)+(uint32_t)u32Cmd[12];
						System.Sys.Data.info.MachineNum[2]= ((uint32_t)u32Cmd[13] <<24) + ((uint32_t)u32Cmd[14] <<16)+( (uint32_t)u32Cmd[15] <<8)+(uint32_t)u32Cmd[16];
						return LED_on(pu8Buffer, u32Len, V6M_CMD_M_Mac_Num);
					}
				        
				
					case V6M_CMD_M_Sof_Ver:	 				  	//软件版本
				    {
	//					System.Sys.Data.info.SoftwareVer[0] =	((uint32_t)u32Cmd[5] <<24) + ((uint32_t)u32Cmd[6] <<16)+ ((uint32_t)u32Cmd[7] <<8)+(uint32_t)u32Cmd[8];
	//					System.Sys.Data.info.SoftwareVer[1] =	((uint32_t)u32Cmd[9] <<24) + ((uint32_t)u32Cmd[10] <<16)+( (uint32_t)u32Cmd[11] <<8)+(uint32_t)u32Cmd[12];
	//					System.Sys.Data.info.SoftwareVer[2] =	((uint32_t)u32Cmd[13] <<24) + ((uint32_t)u32Cmd[14] <<16)+( (uint32_t)u32Cmd[15] <<8)+(uint32_t)u32Cmd[16];
						return LED_on(pu8Buffer, u32Len, V6M_CMD_M_Sof_Ver);
					}
					case V6M_CMD_M_Hrd_Ver:	 				  	//软件版本
				    {
	 					System.Sys.Data.info.HardwareVer[0] =	((uint32_t)u32Cmd[5] <<24) + ((uint32_t)u32Cmd[6] <<16)+ ((uint32_t)u32Cmd[7] <<8)+(uint32_t)u32Cmd[8];
	 					System.Sys.Data.info.HardwareVer[1] =	((uint32_t)u32Cmd[9] <<24) + ((uint32_t)u32Cmd[10] <<16)+( (uint32_t)u32Cmd[11] <<8)+(uint32_t)u32Cmd[12];
	 					System.Sys.Data.info.HardwareVer[2] =	((uint32_t)u32Cmd[13] <<24) + ((uint32_t)u32Cmd[14] <<16)+( (uint32_t)u32Cmd[15] <<8)+(uint32_t)u32Cmd[16];
						return LED_on(pu8Buffer, u32Len, V6M_CMD_M_Hrd_Ver);
					}
									
					case V6M_CMD_M_Pro_Dat:	 			  	//生产日期
					{
						System.Sys.Data.info.ProductDate[0]=	((uint32_t)u32Cmd[5] <<24) + ((uint32_t)u32Cmd[6] <<16)+ ((uint32_t)u32Cmd[7] <<8)+(uint32_t)u32Cmd[8];
						System.Sys.Data.info.ProductDate[1]=	((uint32_t)u32Cmd[9] <<24) + ((uint32_t)u32Cmd[10] <<16)+( (uint32_t)u32Cmd[11] <<8)+(uint32_t)u32Cmd[12];
						System.Sys.Data.info.ProductDate[2]=	((uint32_t)u32Cmd[13] <<24) + ((uint32_t)u32Cmd[14] <<16)+( (uint32_t)u32Cmd[15] <<8)+(uint32_t)u32Cmd[16];
						return LED_on(pu8Buffer, u32Len, V6M_CMD_M_Pro_Dat);
					}
	                
					case V6M_CMD_PH_ARGV:	 			  	//照片参数设定
					{   
	                    System.Dsp.photo.Scene[u32Cmd[5]].Num        =u32Cmd[5]; 
	                    System.Dsp.photo.Scene[u32Cmd[5]].FB1        =u32Cmd[6]; 
	                    System.Dsp.photo.Scene[u32Cmd[5]].FB2        =u32Cmd[7]; 
	                    System.Dsp.photo.Scene[u32Cmd[5]].FC1        =u32Cmd[8]; 
	                    System.Dsp.photo.Scene[u32Cmd[5]].FC2        =u32Cmd[9]; 
	                    System.Dsp.photo.Scene[u32Cmd[5]].Sharpness  =u32Cmd[10]; 
	                    System.Dsp.photo.Scene[u32Cmd[5]].Contrast   =u32Cmd[11]; 
	                    System.Dsp.photo.Scene[u32Cmd[5]].Brightness =u32Cmd[12]; 
	                    System.Dsp.photo.Scene[u32Cmd[5]].Saturation =u32Cmd[13]; 
	                    System.Dsp.photo.Scene[u32Cmd[5]].WB1        =u32Cmd[14]; 
	                    System.Dsp.photo.Scene[u32Cmd[5]].WB2        =u32Cmd[15]; 
	                    System.Dsp.photo.Flag = u32Cmd[5];
	
						return LED_on(pu8Buffer, u32Len, V6M_CMD_PH_ARGV);
					}

					case V6M_CMD_PH_ADJUST:	 			  	//照片参数设定
					{   
	                    System.Dsp.photo.Scene[u32Cmd[5]].Num        =u32Cmd[5]; 
	                    System.Dsp.photo.Scene[u32Cmd[5]].FB1        =u32Cmd[6]; 
	                    System.Dsp.photo.Scene[u32Cmd[5]].FB2        =u32Cmd[7]; 
	                    System.Dsp.photo.Scene[u32Cmd[5]].FC1        =u32Cmd[8]; 
	                    System.Dsp.photo.Scene[u32Cmd[5]].FC2        =u32Cmd[9]; 
	                    System.Dsp.photo.Scene[u32Cmd[5]].Sharpness  =u32Cmd[10]; 
	                    System.Dsp.photo.Scene[u32Cmd[5]].Contrast   =u32Cmd[11]; 
	                    System.Dsp.photo.Scene[u32Cmd[5]].Brightness =u32Cmd[12]; 
	                    System.Dsp.photo.Scene[u32Cmd[5]].Saturation =u32Cmd[13]; 
	                    System.Dsp.photo.Scene[u32Cmd[5]].WB1        =u32Cmd[14]; 
	                    System.Dsp.photo.Scene[u32Cmd[5]].WB2        =u32Cmd[15]; 
					    System.Dsp.photo.Scene[u32Cmd[5]].Mode       =u32Cmd[16]; 
	                    System.Dsp.photo.Flag = u32Cmd[5];
	
						return LED_on(pu8Buffer, u32Len, V6M_CMD_PH_ADJUST);
					}

					case V6M_CMD_PH_NUM:	 			  	//照片参数设定
					{   
	                    System.SignOutCount    = ((uint8_t)u32Cmd[5]<<8)+u32Cmd[6]; 
						return LED_on(pu8Buffer, u32Len, V6M_CMD_PH_NUM);
					}	
					case V6M_CMD_PH_NUM_Dec:	 			  	//照片参数设定
					{   
					   if(	u32Cmd[5] == 0xFF )	u32Cmd[5] = 0 ; 				
	                    System.SignOutCount    = (((uint8_t)u32Cmd[5]<<8)+u32Cmd[6])<System.SignOutCount ?(System.SignOutCount-(((uint8_t)u32Cmd[5]<<8)+u32Cmd[6])):0   ; 
						Local_SignOutCount 	   = (((uint8_t)u32Cmd[5]<<8)+u32Cmd[6])<Local_SignOutCount ?(Local_SignOutCount-(((uint8_t)u32Cmd[5]<<8)+u32Cmd[6])):0   ;  
						return LED_on(pu8Buffer, u32Len, V6M_CMD_PH_NUM_Dec);
					}
															                
					case V6M_CMD_SETTIME :
					{
	//					date[6] = u32Cmd[5]; 
	//					date[5] = u32Cmd[6]; 
	//					date[4] = u32Cmd[7]; 
	//					date[3] = u32Cmd[8]; 
	//					date[2] = u32Cmd[9]; 
	//					date[1] = u32Cmd[10]; 
	//					date[0] = u32Cmd[11]; 
	//				//  OSTimeDly(10);
	//					  DS1307_WR(&date[0]); 
	//				//	  OSTimeDly(10); 
	//	 				  DS1307_RD(&date[0]);  
	//				//	  GR_DBG_PRINTF("TIme isok33\n\n！！！")	 ;
	//				 	 //	  OSTimeDly(10);
	//				//	GR_DBG_PRINTF("TIme isok44\n\n！！！")	 ;
	//				      DSP_SENDA(7,&date_dsp[0] );
	//				//	  OSTimeDly(10);
	
						return  LED_on(pu8Buffer, u32Len, V6M_CMD_SETTIME);	
						
					}
					case V6M_CMD_SETUVC :
					{
	//					ATUO_UV1[2]= u32Cmd[5]; 
	//					ATUO_UV1[3]= u32Cmd[6]; 
	//					ATUO_UV2[2]= u32Cmd[7]; 
	//					ATUO_UV2[3]= u32Cmd[8]; 
						return LED_on(pu8Buffer, u32Len, V6M_CMD_SETUVC);		
					}

					case V6M_CMD_XY_ZOOM :
					{
						System.XyZoom[0]= u32Cmd[5]; 
						System.XyZoom[1]= u32Cmd[6]; 
						System.XyZoom[2]= u32Cmd[7]; 
	//					ATUO_UV1[3]= u32Cmd[6]; 
	//					ATUO_UV2[2]= u32Cmd[7]; 
	//					ATUO_UV2[3]= u32Cmd[8]; 
						return LED_on(pu8Buffer, u32Len, V6M_CMD_XY_ZOOM);		
					}
					case V6M_CMD_SETUVC71 :
					{
	//					ATUO_UV1[2]= u32Cmd[5]; 
	//					ATUO_UV1[3]= u32Cmd[6]; 
	//					ATUO_UV2[2]= u32Cmd[7]; 
	//					ATUO_UV2[3]= u32Cmd[8]; 
						return LED_on(pu8Buffer, u32Len, V6M_CMD_SETUVC71);		
					}
					case V6M_CMD_SETUVC72 :
					{
	//					ATUO_UV1[2]= u32Cmd[5]; 
	//					ATUO_UV1[3]= u32Cmd[6]; 
	//					ATUO_UV2[2]= u32Cmd[7]; 
	//					ATUO_UV2[3]= u32Cmd[8]; 
						return LED_on(pu8Buffer, u32Len, V6M_CMD_SETUVC72);		
					}
					case V6M_CMD_AlarmSound:							//机器报警声音控制
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_AlarmSound);
				
				
				
					case V6M_CMD_Check_Stat:							//查询系统状态
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_Check_Stat);
				
					case V6M_CMD_USB_U:							  		//进入U盘模式
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_USB_U);
				
					case V6M_CMD_USB_U_Out:							  	//退出U盘模式
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_USB_U_Out);
				
					case V6M_CMD_USB_PC:							  	//进入PC-CAM
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_USB_PC);
				
					case V6M_CMD_USB_PC_Out:							//退出PC-CAM
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_USB_PC_Out);
				
				
				//=====================系统功能=======================
				
					case V6M_CMD_View:							  	//预览
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_View);
				
					case V6M_CMD_Play:							  	//回放
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_Play);
				
					case V6M_CMD_SL:							  	//休眠
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_SL);
				
					case V6M_CMD_WU:							  	//唤醒
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_WU);
				
					case V6M_CMD_FZ:							  	//照片分组，连拍用
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_FZ);	
						
					case V6M_CMD_ZHUANFA:							//转发指令
						{
							DSP_SEND_USB((u32Cmd[2]-4),&u32Cmd[5]);		//直接将接受到的数据转发
							return LED_on(pu8Buffer, u32Len, V6M_CMD_ZHUANFA);
						}
				
				    case V6M_CMD_RESET_CMD_SRIAL:
				        return VCMD_WillResetCommandSerial(pu8Buffer, u32Len);
					case V6M_CMD_PASSWRD:							  	//生产日期
					{
						uint8_t i ; 
						for(i =0 ; i<PASSWORD_LENGTH; i++)
						{
							System.Sys.PassWrd.Code[i]=(i+1); 
						}
						return LED_on(pu8Buffer, u32Len, V6M_CMD_PASSWRD);
					} 				
					case  V6M_CMD_UNLOCK_TM:							  	//解除锁定
					{
						System.Sys.PassWrd.InputErrCount = 0 ; 
						System.Sys.PassWrd.LockTime = 0 ; 
						return LED_on(pu8Buffer, u32Len, V6M_CMD_UNLOCK_TM);
					} 
					case  V6M_CMD_Chk_Phot :
					{
						return LED_on(pu8Buffer, u32Len, V6M_CMD_Chk_Phot);
					}
					case  V6M_CMD_Chk_Phot_2 :
					{
						return LED_on(pu8Buffer, u32Len, V6M_CMD_Chk_Phot_2);
					}		 
					case  V6M_CMD_Sign_Cnt :
					{
						return LED_on(pu8Buffer, u32Len, V6M_CMD_Sign_Cnt);
					}	  
					case  V6M_CMD_Sign_Chk :
					{
						return LED_on(pu8Buffer, u32Len, V6M_CMD_Sign_Chk);
					}
	
					case  V6M_CMD_Sign_F1 :
					{
						return LED_on(pu8Buffer, u32Len, V6M_CMD_Sign_F1);
					}	  
					case  V6M_CMD_Sign_F2 :
					{
						return LED_on(pu8Buffer, u32Len, V6M_CMD_Sign_F2);
					}
					case  V6M_CMD_Sign_F3 :
					{
						return LED_on(pu8Buffer, u32Len, V6M_CMD_Sign_F3);
					}	  
					case  V6M_CMD_Sign_F4 :
					{
						return LED_on(pu8Buffer, u32Len, V6M_CMD_Sign_F4);
					}
					case  V6M_CMD_Ext_Black:
					{
						return LED_on(pu8Buffer, u32Len, V6M_CMD_Ext_Black);
					}
					case  V6M_CMD_AutoExposure:
					{
						return LED_on(pu8Buffer, u32Len, V6M_CMD_AutoExposure);
					}				
				    default:			
				        return 1;
			    }
			}
		}
	}
	return 1;
}


void V6M_ProcessCommand(const uint8_t *pu8Buffer, uint32_t u32Len)
{

    static uint8_t au8CmdBuffer[V6M_MAX_COMMAND_LENGTH];
    static uint32_t u32BufferLen = 0;

    memcpy(au8CmdBuffer, pu8Buffer, 62);

    V6M_ProcessOneCommand(au8CmdBuffer, u32BufferLen);

}

uint32_t LED_on(const uint8_t *pu8Buffer, uint32_t u32Len, uint8_t u8LedNum)
{
    uint8_t au32Data[13];
    uint32_t u32Errno = 0;
	uint8_t Select_LED=0;

	MCU_Status.Struct_Status=0x00;			//指令接收成功，正在执行，请稍后

	au32Data[0]=0x47;						//G
	au32Data[1]=0x52;						//R
	au32Data[2]=0x09;						//指令数据长度，包括指令头和指令尾

	au32Data[3]=0x23;
	au32Data[4]=pu8Buffer[4];			    // 指令 原来指令，现在指令
	MCU_Status.Struct_Name=pu8Buffer[4];	//存储指令名称
	au32Data[5]=MCU_Status.Struct_Status;
	au32Data[6]=System.Uart.UsbFlag	;		//MCU_Status.Sys_Status;
	au32Data[7]=System.Uart.Sensor;			//MCU_Status.Sen_Status;
	au32Data[8]=System.Uart.Display;		//MCU_Status.Scale_Status;
	au32Data[9]=System.Uart.PhotoFlag;							//MCU_Status.Menu_Status;
 	au32Data[10]= System.Process_TakePht ; //  System.Uart.SdFlag; 		//MCU_Status.SD_Status;
	au32Data[11]=System.Led.Statu ;			//MCU_Status.LED_Status;
	au32Data[12]=0xAA;
	// 此处返回机器信息
  	VCMD_AckCommand(u32Errno, (const uint8_t *)&au32Data, 13);		  //暂时只发送13字节

	Select_LED=u8LedNum;

	switch(Select_LED)
	{
		case V6M_CMD_TOP_W	:  	{	ptr = Top_W_On	; 		}break;
		case V6M_CMD_SIDE_W	: 	{	ptr = Left_W_On	; 		}break;
		case V6M_CMD_SIDE_W_90: {	ptr = Right_W_On;		}break;		
		case V6M_CMD_IR_850:	{	ptr = Top_IR850_On;		}break;
		case V6M_CMD_IR_940: 	{	ptr = Top_IR940_On;		}break;
		case V6M_CMD_IR_940_test: 	{	ptr = Top_IR940_On_test;		}break;
		case V6M_CMD_UV_365:	{	ptr = Double_UV_On;		}break;
		case V6M_CMD_UV_365_EX1:	{	ptr = Double_UV_Exposure1_On;		}break;
		case V6M_CMD_UV_365_EX2:	{	ptr = Double_UV_Exposure2_On;		}break;
		case V6M_CMD_SIDE_IR_90:{	ptr = Right_IR850_On;	}break;			
		case V6M_CMD_SIDE_IR:	{	ptr = Left_IR850_On;	}break;
		case V6M_CMD_BOT_W:		{	ptr = Bot_W_On;			}break;
		case V6M_CMD_BOT_IR:	{	ptr = Bot_IR_On;		}break;

		
//  V6M_CMD_COUN_PIC: {ptr = }break;
	
//=================	上面7个按键============

		
		case V6M_CMD_Play:		{ptr = 	ViewMode ;	}break;	
		case V6M_CMD_USB_U:		{ptr = 	TfMode	 ;	}break;	
		case V6M_CMD_USB_PC:	{ptr = 	PccamMode;	}break;				//PC-CAM
				
		case V6M_CMD_View: 		{ptr = 	CheckMode; 	}break;
		case V6M_CMD_USB_U_Out:	{ptr = 	CheckMode; 	}break;				//退出U盘
		case V6M_CMD_USB_PC_Out:{ptr =  CheckMode;	}break; 			//退出PC-CAM
		
		case V6M_CMD_Left:	{ptr = PhotoMvLeft;		}break;			//13:							   //左移
		case V6M_CMD_Up:	{ptr = PhotoMvUp;		}break;			//14:							  //上移
		case V6M_CMD_Down:	{ptr = PhotoMvDown;		}break;			//16:							 //下移	
		case V6M_CMD_Right:	{ptr = PhotoMvRight;	}break;			//18:							//右移
		
		case V6M_CMD_ZoomUp:	{ptr = PhotoZoomUp ;}break;			//19:							//放大
		case V6M_CMD_ZoomDown:	{ptr = PhotoZoomDown;}break;			//20:							//缩小
		
		case V6M_CMD_Del_Photo: {ptr = PhotoDelOne ;}break;			//22:							//删除单张

		case V6M_CMD_PhotoLong:	{ptr = PhotoDelAll;}break;			// 23:							//删除所有

		case V6M_CMD_AUTO_VIEW:{ptr = PhotoAutoView ;}break;			//0xB6:
			
		case V6M_CMD_Photo:			{ptr = 	PhotographOne	;}break;			//21:
		case V6M_CMD_Photo_Four:	{ptr =  PhotographFour	;}break;			//0xB5:
		case V6M_CMD_Photo_Eight:	{ptr =  PhotographEight;}break;				//0xC5:
		
		case V6M_CMD_OverView:		{ptr = Sensor1 ;}break;						//24:					//全幅
		case V6M_CMD_PartView:		{ptr = Sensor2 ;}break;						//25:					//局部
		case V6M_CMD_SpecView:		{ptr = Sensor3 ;}break;			 			//26:					//细节局部
		case V6M_CMD_C608: 			{ptr = C608_On ;}break;			 			//27:					//C608
//		case V6M_CMD_HDMI:			{ 				}break;						//28:					//HDMI
//		case V6M_CMD_HDMI_OUT:		{	 			}break;						//29:					//退出HDMI
		case V6M_CMD_SETTIME :		{ptr = TimeSet ;}break;			//0xA2:   //设置时间		
		case V6M_CMD_SETUVC : 		{ptr = UV365_70ExpSet  ;}break;			//0xA3:   //设置紫光曝光值
		case V6M_CMD_SETUVC71 :		{ptr = UV365_71ExpSet  ;}break;			//0xA4:   //设置紫光曝光值	71
		case V6M_CMD_SETUVC72 :		{ptr = UV365_72ExpSet  ;}break;			 //0xA5:   //设置紫光曝光值  72
		case V6M_CMD_FORMAT_SD:		{ptr = Format_SDcard   ;}break;	
		case V6M_CMD_RESET_DSP:		{ptr = DspRst   ;}break;	

//=====================系统查询====================
		case V6M_CMD_C_Sys_Inf:	{ptr = QueryInfo ; }break;			 //31:									   //查询系统信息

		case V6M_CMD_C_Mac_Ver:	{ptr = QueryInfo ; }break;			//32:									   //机器型号

		case V6M_CMD_C_Pro_Num:	{ptr = QueryInfo ; }break;			//33:									   //产品序列号

		case V6M_CMD_C_Mac_Num:	{ptr = QueryInfo ; }break;			 //34:									   //机器编号

		case V6M_CMD_C_Sof_Ver:{ptr = QueryInfo ; }break;				//35:									   //软件版本

		case V6M_CMD_C_Pro_Dat:{ptr =  QueryInfo ; }break;			//36:									   //生产日期
		case V6M_CMD_C_Hrd_Ver:{ptr =  QueryInfo ; }break;			//36:
		case V6M_CMD_Check_Stat:{ptr = QueryInfo ; }break;			// 43:									 //查询系统状态 

//=====================系统信息修改====================
		case V6M_CMD_M_Mac_Ver:	{ptr = ModifyInfo;}break;			//37:									   //机器型号

		case V6M_CMD_DeepComPs:	{ptr = ModifyInfo;}break;			//37:									   //机器型号

		case V6M_CMD_M_Hrd_Ver:	{ptr = ModifyInfo;}break;			//37:									   //机器型号

		case V6M_CMD_M_Pro_Num:	{ptr = ModifyInfo ;}break;			//38:									  //产品序列号 

		case V6M_CMD_M_Mac_Num:	{ptr = ModifyInfo;}break;			//39:									  //机器编号 

		case V6M_CMD_M_Sof_Ver:	{ptr = ModifyInfo;}break;			//40:									 //软件版本 
											 
		case V6M_CMD_M_Pro_Dat:	{ptr = ModifyInfo;}break;			//41:									   

		case V6M_CMD_PASSWRD: 	{ptr = ModifyInfo;}break;			//54:   //密码重置

		case V6M_CMD_UNLOCK_TM:	{ptr = ModifyInfo;}break;			    //55:   // 

		case V6M_CMD_PH_ARGV  :	{ptr = ArguPriorExposure; }break;			//41:	

		case V6M_CMD_PH_ADJUST  :{ptr = ArguPriorExposureAdjust; }break;			//41:	

	    case V6M_CMD_PH_NUM        :{ptr = PhotoNumAdjust; }break;			//41:	
		case V6M_CMD_PH_NUM_Dec    :{ptr = PhotoNumAdjust; }break;			//41:	
// 		case V6M_CMD_RESET: 	{ptr =    }break;			//30:									 //系统复位  

//		case V6M_CMD_AlarmSound:{ptr = }break;			 //42:									 //机器报警控制  

//==========================xiumian唤醒==============
		case V6M_CMD_SL:{ptr = MacSleep  ;	}break;			 //50:									  
		
		case V6M_CMD_WU:{ptr = MacWakeup ; 	}break;			//51: 

		case V6M_CMD_ZHUANFA:{ptr = Zhuanfa; }break;			//53: 
		case V6M_CMD_XY_ZOOM:{ptr = XyZoomFuc; }break ;
		case V6M_CMD_Chk_Phot: {ptr = ShowChkPhotOne; }break; 
		case V6M_CMD_Chk_Phot_2: {ptr = ShowChkPhotAgain; }break; 
		case V6M_CMD_Ext_Black:{ptr = ExtBlackScreen; }break; 
		case V6M_CMD_Sign_Cnt:{ptr = Photo_SignAndCount; }break; 	// 签发					  Photo_SignAndCount
		case V6M_CMD_Sign_Chk:{ptr = Photo_SignAndChk; }break;    //审验
		case V6M_CMD_Sign_F1:{ptr = ViewMode_F1; }break;    //
		case V6M_CMD_Sign_F2:{ptr = ViewMode_F2; }break;    //审验
		case V6M_CMD_Sign_F3:{ptr = ViewMode_F3; }break;    //审验
		case V6M_CMD_Sign_F4:{ptr = ViewMode_F4; }break;    //审验

  		case V6M_CMD_SLP_DIS:{ptr = Slp_disable ; 	}break;			//51: 

		case V6M_CMD_SLP_EN:{ptr = Slp_enable; }break;			//53: 
		
		case V6M_CMD_AutoExposure :{ptr = PriorExposure;} break;	 
		default:  ptr =NULL  ; 	break;	
	}	
    return 0;
}

uint32_t LED_off(const uint8_t *pu8Buffer, uint32_t u32Len, uint8_t u8LedNum)
{
    uint8_t i, au32Data[62] = {0};
    uint32_t u32Errno = 0;

    GR_DBG_PRINTF("PC Send command\n");

    if (u8LedNum == 5)
	{
        GR_DBG_PRINTF("BOT_W OFF\n");
		BOT_W=1;
	}
    else if (u8LedNum == 6)
	{
        GR_DBG_PRINTF("BOT_IR OFF\n");
		BOT_IR=1;
	}
    else if (u8LedNum == 7)
        GR_DBG_PRINTF("GPC2 Output High\n");
    else if (u8LedNum == 8)
        GR_DBG_PRINTF("GPC0 Output High\n");
    else
        GR_DBG_PRINTF("GPC0~3 Output High\n");

    if (u8LedNum != 15)
    {
        // Defined GPC0~GPC3
        DrvGPIO_Open(E_GPC, u8LedNum - 5, E_IO_OUTPUT);
        DrvGPIO_SetBit(E_GPC, u8LedNum - 5);
    }
    else
    {
        for (i = 0;i < 4;i++)
        {
            DrvGPIO_Open(E_GPC, i, E_IO_OUTPUT);
            DrvGPIO_SetBit(E_GPC, i);
        }
    }

    VCMD_AckCommand(u32Errno, (const uint8_t *)&au32Data, 62);
    return 0;
}

