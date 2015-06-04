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
// extern volatile uint32_t	SysData[18];					   //ϵͳ��Ϣ�洢	


//volatile uint8_t Struct_Status;		//ָ��ִ��״̬��00���ճɹ���01ִ�гɹ���02ʧ�ܣ�03����
//volatile uint8_t Sys_Status;		//ϵͳ״̬��01 U�� 02 PC-CAM 03������ʾ״̬������USB��
//volatile uint8_t Sen_Status;		//sensor״̬��01 ȫ�� 02 �ֲ� 03 ϸ�ھֲ� 04 C608 
//volatile uint8_t Scale_Status;		//��ʾ����״̬��01 16:9  02 4:3 
//volatile uint8_t Menu_Status;		//�˵�״̬��01 Ԥ��ģʽ 02 �ط� 03����
//volatile uint8_t SD_Status;			//SD��״̬��01 ���� 02 �γ� 

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
    uint8_t u32Cmd[18];					 //���ָ�������
	uint8_t	 temp[2];

	memcpy(&temp, pu8Buffer, 2);			 //ISP

//   GR_DBG_PRINTF("%d",temp[0]);
//   GR_DBG_PRINTF("%d",temp[1]);
//   GR_DBG_PRINTF("%d",temp[2]);
//   GR_DBG_PRINTF("%d",temp[3]);
//   GR_DBG_PRINTF("receive data");
   if((temp[0]==0x03)&&(temp[1]==0x04))
   { 	
/***********************FMC����**************************/
			UNLOCKREG();

			DrvFMC_EnableISP();
		
			DrvFMC_WriteConfig (0xFFFFFF7E, 0x1E000);
		
			DrvFMC_Erase (0x1F000); 
		
			DrvFMC_Write (0x1F000, 0x12345678); 
		
			DrvFMC_DisableISP();
		
			CPU_RST();		//CPU��λ
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
				
				//=================	����7������============
				
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
						
				
				//=====================�ӳ�����==================
				
					case V6M_CMD_OverView:							   	//ȫ��
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_OverView);
				
					case V6M_CMD_PartView:							   	//�ֲ�
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_PartView);
				
					case V6M_CMD_SpecView:							   	//ϸ�ھֲ�
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_SpecView);
				
				 	case V6M_CMD_C608:							   		//c608
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_C608);
				
					case V6M_CMD_HDMI:							  		//HDMI
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_HDMI);
				
					case V6M_CMD_HDMI_OUT:							  	//�˳�HDMI
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_HDMI_OUT);
				
					case V6M_CMD_RESET:							  		// ��λϵͳ
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_RESET);
				
				//=============��ѯ=======================
					case V6M_CMD_C_Sys_Inf:							   	//ϵͳ��Ϣ
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_C_Sys_Inf);
				
					case V6M_CMD_C_Mac_Ver:							  	//�����ͺ�
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_C_Mac_Ver);
				
					case V6M_CMD_C_Pro_Num:							  	//��Ʒ���к�
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_C_Pro_Num);
				
					case V6M_CMD_C_Mac_Num:							  	//�������
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_C_Mac_Num);
				
					case V6M_CMD_C_Sof_Ver:							  	//����汾
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_C_Sof_Ver);
					case V6M_CMD_C_Hrd_Ver:							  	//��������
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_C_Hrd_Ver);				
					case V6M_CMD_C_Pro_Dat:							  	//��������
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_C_Pro_Dat);
				//=============�޸�=======================
					case V6M_CMD_M_Mac_Ver:							  	//�����ͺ�
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
					case V6M_CMD_M_Pro_Num:							  	//��Ʒ���к�
					{
						System.Sys.Data.info.CdKey[0] =	((uint32_t)u32Cmd[5] <<24) + ((uint32_t)u32Cmd[6] <<16)+ ((uint32_t)u32Cmd[7] <<8)+(uint32_t)u32Cmd[8];
						System.Sys.Data.info.CdKey[1] =	((uint32_t)u32Cmd[9] <<24) + ((uint32_t)u32Cmd[10] <<16)+( (uint32_t)u32Cmd[11] <<8)+(uint32_t)u32Cmd[12];
						System.Sys.Data.info.CdKey[2] =	((uint32_t)u32Cmd[13] <<24) + ((uint32_t)u32Cmd[14] <<16)+( (uint32_t)u32Cmd[15] <<8)+(uint32_t)u32Cmd[16];
						return LED_on(pu8Buffer, u32Len, V6M_CMD_M_Pro_Num);
					}
				       
				
					case V6M_CMD_M_Mac_Num:							    //�������
					{
						System.Sys.Data.info.MachineNum[0] = ((uint32_t)u32Cmd[5] <<24) + ((uint32_t)u32Cmd[6] <<16)+ ((uint32_t)u32Cmd[7] <<8)+(uint32_t)u32Cmd[8];
						System.Sys.Data.info.MachineNum[1]= ((uint32_t)u32Cmd[9] <<24) + ((uint32_t)u32Cmd[10] <<16)+( (uint32_t)u32Cmd[11] <<8)+(uint32_t)u32Cmd[12];
						System.Sys.Data.info.MachineNum[2]= ((uint32_t)u32Cmd[13] <<24) + ((uint32_t)u32Cmd[14] <<16)+( (uint32_t)u32Cmd[15] <<8)+(uint32_t)u32Cmd[16];
						return LED_on(pu8Buffer, u32Len, V6M_CMD_M_Mac_Num);
					}
				        
				
					case V6M_CMD_M_Sof_Ver:	 				  	//����汾
				    {
	//					System.Sys.Data.info.SoftwareVer[0] =	((uint32_t)u32Cmd[5] <<24) + ((uint32_t)u32Cmd[6] <<16)+ ((uint32_t)u32Cmd[7] <<8)+(uint32_t)u32Cmd[8];
	//					System.Sys.Data.info.SoftwareVer[1] =	((uint32_t)u32Cmd[9] <<24) + ((uint32_t)u32Cmd[10] <<16)+( (uint32_t)u32Cmd[11] <<8)+(uint32_t)u32Cmd[12];
	//					System.Sys.Data.info.SoftwareVer[2] =	((uint32_t)u32Cmd[13] <<24) + ((uint32_t)u32Cmd[14] <<16)+( (uint32_t)u32Cmd[15] <<8)+(uint32_t)u32Cmd[16];
						return LED_on(pu8Buffer, u32Len, V6M_CMD_M_Sof_Ver);
					}
					case V6M_CMD_M_Hrd_Ver:	 				  	//����汾
				    {
	 					System.Sys.Data.info.HardwareVer[0] =	((uint32_t)u32Cmd[5] <<24) + ((uint32_t)u32Cmd[6] <<16)+ ((uint32_t)u32Cmd[7] <<8)+(uint32_t)u32Cmd[8];
	 					System.Sys.Data.info.HardwareVer[1] =	((uint32_t)u32Cmd[9] <<24) + ((uint32_t)u32Cmd[10] <<16)+( (uint32_t)u32Cmd[11] <<8)+(uint32_t)u32Cmd[12];
	 					System.Sys.Data.info.HardwareVer[2] =	((uint32_t)u32Cmd[13] <<24) + ((uint32_t)u32Cmd[14] <<16)+( (uint32_t)u32Cmd[15] <<8)+(uint32_t)u32Cmd[16];
						return LED_on(pu8Buffer, u32Len, V6M_CMD_M_Hrd_Ver);
					}
									
					case V6M_CMD_M_Pro_Dat:	 			  	//��������
					{
						System.Sys.Data.info.ProductDate[0]=	((uint32_t)u32Cmd[5] <<24) + ((uint32_t)u32Cmd[6] <<16)+ ((uint32_t)u32Cmd[7] <<8)+(uint32_t)u32Cmd[8];
						System.Sys.Data.info.ProductDate[1]=	((uint32_t)u32Cmd[9] <<24) + ((uint32_t)u32Cmd[10] <<16)+( (uint32_t)u32Cmd[11] <<8)+(uint32_t)u32Cmd[12];
						System.Sys.Data.info.ProductDate[2]=	((uint32_t)u32Cmd[13] <<24) + ((uint32_t)u32Cmd[14] <<16)+( (uint32_t)u32Cmd[15] <<8)+(uint32_t)u32Cmd[16];
						return LED_on(pu8Buffer, u32Len, V6M_CMD_M_Pro_Dat);
					}
	                
					case V6M_CMD_PH_ARGV:	 			  	//��Ƭ�����趨
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

					case V6M_CMD_PH_ADJUST:	 			  	//��Ƭ�����趨
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

					case V6M_CMD_PH_NUM:	 			  	//��Ƭ�����趨
					{   
	                    System.SignOutCount    = ((uint8_t)u32Cmd[5]<<8)+u32Cmd[6]; 
						return LED_on(pu8Buffer, u32Len, V6M_CMD_PH_NUM);
					}	
					case V6M_CMD_PH_NUM_Dec:	 			  	//��Ƭ�����趨
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
	//				//	  GR_DBG_PRINTF("TIme isok33\n\n������")	 ;
	//				 	 //	  OSTimeDly(10);
	//				//	GR_DBG_PRINTF("TIme isok44\n\n������")	 ;
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
					case V6M_CMD_AlarmSound:							//����������������
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_AlarmSound);
				
				
				
					case V6M_CMD_Check_Stat:							//��ѯϵͳ״̬
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_Check_Stat);
				
					case V6M_CMD_USB_U:							  		//����U��ģʽ
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_USB_U);
				
					case V6M_CMD_USB_U_Out:							  	//�˳�U��ģʽ
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_USB_U_Out);
				
					case V6M_CMD_USB_PC:							  	//����PC-CAM
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_USB_PC);
				
					case V6M_CMD_USB_PC_Out:							//�˳�PC-CAM
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_USB_PC_Out);
				
				
				//=====================ϵͳ����=======================
				
					case V6M_CMD_View:							  	//Ԥ��
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_View);
				
					case V6M_CMD_Play:							  	//�ط�
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_Play);
				
					case V6M_CMD_SL:							  	//����
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_SL);
				
					case V6M_CMD_WU:							  	//����
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_WU);
				
					case V6M_CMD_FZ:							  	//��Ƭ���飬������
				        return LED_on(pu8Buffer, u32Len, V6M_CMD_FZ);	
						
					case V6M_CMD_ZHUANFA:							//ת��ָ��
						{
							DSP_SEND_USB((u32Cmd[2]-4),&u32Cmd[5]);		//ֱ�ӽ����ܵ�������ת��
							return LED_on(pu8Buffer, u32Len, V6M_CMD_ZHUANFA);
						}
				
				    case V6M_CMD_RESET_CMD_SRIAL:
				        return VCMD_WillResetCommandSerial(pu8Buffer, u32Len);
					case V6M_CMD_PASSWRD:							  	//��������
					{
						uint8_t i ; 
						for(i =0 ; i<PASSWORD_LENGTH; i++)
						{
							System.Sys.PassWrd.Code[i]=(i+1); 
						}
						return LED_on(pu8Buffer, u32Len, V6M_CMD_PASSWRD);
					} 				
					case  V6M_CMD_UNLOCK_TM:							  	//�������
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

	MCU_Status.Struct_Status=0x00;			//ָ����ճɹ�������ִ�У����Ժ�

	au32Data[0]=0x47;						//G
	au32Data[1]=0x52;						//R
	au32Data[2]=0x09;						//ָ�����ݳ��ȣ�����ָ��ͷ��ָ��β

	au32Data[3]=0x23;
	au32Data[4]=pu8Buffer[4];			    // ָ�� ԭ��ָ�����ָ��
	MCU_Status.Struct_Name=pu8Buffer[4];	//�洢ָ������
	au32Data[5]=MCU_Status.Struct_Status;
	au32Data[6]=System.Uart.UsbFlag	;		//MCU_Status.Sys_Status;
	au32Data[7]=System.Uart.Sensor;			//MCU_Status.Sen_Status;
	au32Data[8]=System.Uart.Display;		//MCU_Status.Scale_Status;
	au32Data[9]=System.Uart.PhotoFlag;							//MCU_Status.Menu_Status;
 	au32Data[10]= System.Process_TakePht ; //  System.Uart.SdFlag; 		//MCU_Status.SD_Status;
	au32Data[11]=System.Led.Statu ;			//MCU_Status.LED_Status;
	au32Data[12]=0xAA;
	// �˴����ػ�����Ϣ
  	VCMD_AckCommand(u32Errno, (const uint8_t *)&au32Data, 13);		  //��ʱֻ����13�ֽ�

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
	
//=================	����7������============

		
		case V6M_CMD_Play:		{ptr = 	ViewMode ;	}break;	
		case V6M_CMD_USB_U:		{ptr = 	TfMode	 ;	}break;	
		case V6M_CMD_USB_PC:	{ptr = 	PccamMode;	}break;				//PC-CAM
				
		case V6M_CMD_View: 		{ptr = 	CheckMode; 	}break;
		case V6M_CMD_USB_U_Out:	{ptr = 	CheckMode; 	}break;				//�˳�U��
		case V6M_CMD_USB_PC_Out:{ptr =  CheckMode;	}break; 			//�˳�PC-CAM
		
		case V6M_CMD_Left:	{ptr = PhotoMvLeft;		}break;			//13:							   //����
		case V6M_CMD_Up:	{ptr = PhotoMvUp;		}break;			//14:							  //����
		case V6M_CMD_Down:	{ptr = PhotoMvDown;		}break;			//16:							 //����	
		case V6M_CMD_Right:	{ptr = PhotoMvRight;	}break;			//18:							//����
		
		case V6M_CMD_ZoomUp:	{ptr = PhotoZoomUp ;}break;			//19:							//�Ŵ�
		case V6M_CMD_ZoomDown:	{ptr = PhotoZoomDown;}break;			//20:							//��С
		
		case V6M_CMD_Del_Photo: {ptr = PhotoDelOne ;}break;			//22:							//ɾ������

		case V6M_CMD_PhotoLong:	{ptr = PhotoDelAll;}break;			// 23:							//ɾ������

		case V6M_CMD_AUTO_VIEW:{ptr = PhotoAutoView ;}break;			//0xB6:
			
		case V6M_CMD_Photo:			{ptr = 	PhotographOne	;}break;			//21:
		case V6M_CMD_Photo_Four:	{ptr =  PhotographFour	;}break;			//0xB5:
		case V6M_CMD_Photo_Eight:	{ptr =  PhotographEight;}break;				//0xC5:
		
		case V6M_CMD_OverView:		{ptr = Sensor1 ;}break;						//24:					//ȫ��
		case V6M_CMD_PartView:		{ptr = Sensor2 ;}break;						//25:					//�ֲ�
		case V6M_CMD_SpecView:		{ptr = Sensor3 ;}break;			 			//26:					//ϸ�ھֲ�
		case V6M_CMD_C608: 			{ptr = C608_On ;}break;			 			//27:					//C608
//		case V6M_CMD_HDMI:			{ 				}break;						//28:					//HDMI
//		case V6M_CMD_HDMI_OUT:		{	 			}break;						//29:					//�˳�HDMI
		case V6M_CMD_SETTIME :		{ptr = TimeSet ;}break;			//0xA2:   //����ʱ��		
		case V6M_CMD_SETUVC : 		{ptr = UV365_70ExpSet  ;}break;			//0xA3:   //�����Ϲ��ع�ֵ
		case V6M_CMD_SETUVC71 :		{ptr = UV365_71ExpSet  ;}break;			//0xA4:   //�����Ϲ��ع�ֵ	71
		case V6M_CMD_SETUVC72 :		{ptr = UV365_72ExpSet  ;}break;			 //0xA5:   //�����Ϲ��ع�ֵ  72
		case V6M_CMD_FORMAT_SD:		{ptr = Format_SDcard   ;}break;	
		case V6M_CMD_RESET_DSP:		{ptr = DspRst   ;}break;	

//=====================ϵͳ��ѯ====================
		case V6M_CMD_C_Sys_Inf:	{ptr = QueryInfo ; }break;			 //31:									   //��ѯϵͳ��Ϣ

		case V6M_CMD_C_Mac_Ver:	{ptr = QueryInfo ; }break;			//32:									   //�����ͺ�

		case V6M_CMD_C_Pro_Num:	{ptr = QueryInfo ; }break;			//33:									   //��Ʒ���к�

		case V6M_CMD_C_Mac_Num:	{ptr = QueryInfo ; }break;			 //34:									   //�������

		case V6M_CMD_C_Sof_Ver:{ptr = QueryInfo ; }break;				//35:									   //����汾

		case V6M_CMD_C_Pro_Dat:{ptr =  QueryInfo ; }break;			//36:									   //��������
		case V6M_CMD_C_Hrd_Ver:{ptr =  QueryInfo ; }break;			//36:
		case V6M_CMD_Check_Stat:{ptr = QueryInfo ; }break;			// 43:									 //��ѯϵͳ״̬ 

//=====================ϵͳ��Ϣ�޸�====================
		case V6M_CMD_M_Mac_Ver:	{ptr = ModifyInfo;}break;			//37:									   //�����ͺ�

		case V6M_CMD_DeepComPs:	{ptr = ModifyInfo;}break;			//37:									   //�����ͺ�

		case V6M_CMD_M_Hrd_Ver:	{ptr = ModifyInfo;}break;			//37:									   //�����ͺ�

		case V6M_CMD_M_Pro_Num:	{ptr = ModifyInfo ;}break;			//38:									  //��Ʒ���к� 

		case V6M_CMD_M_Mac_Num:	{ptr = ModifyInfo;}break;			//39:									  //������� 

		case V6M_CMD_M_Sof_Ver:	{ptr = ModifyInfo;}break;			//40:									 //����汾 
											 
		case V6M_CMD_M_Pro_Dat:	{ptr = ModifyInfo;}break;			//41:									   

		case V6M_CMD_PASSWRD: 	{ptr = ModifyInfo;}break;			//54:   //��������

		case V6M_CMD_UNLOCK_TM:	{ptr = ModifyInfo;}break;			    //55:   // 

		case V6M_CMD_PH_ARGV  :	{ptr = ArguPriorExposure; }break;			//41:	

		case V6M_CMD_PH_ADJUST  :{ptr = ArguPriorExposureAdjust; }break;			//41:	

	    case V6M_CMD_PH_NUM        :{ptr = PhotoNumAdjust; }break;			//41:	
		case V6M_CMD_PH_NUM_Dec    :{ptr = PhotoNumAdjust; }break;			//41:	
// 		case V6M_CMD_RESET: 	{ptr =    }break;			//30:									 //ϵͳ��λ  

//		case V6M_CMD_AlarmSound:{ptr = }break;			 //42:									 //������������  

//==========================xiumian����==============
		case V6M_CMD_SL:{ptr = MacSleep  ;	}break;			 //50:									  
		
		case V6M_CMD_WU:{ptr = MacWakeup ; 	}break;			//51: 

		case V6M_CMD_ZHUANFA:{ptr = Zhuanfa; }break;			//53: 
		case V6M_CMD_XY_ZOOM:{ptr = XyZoomFuc; }break ;
		case V6M_CMD_Chk_Phot: {ptr = ShowChkPhotOne; }break; 
		case V6M_CMD_Chk_Phot_2: {ptr = ShowChkPhotAgain; }break; 
		case V6M_CMD_Ext_Black:{ptr = ExtBlackScreen; }break; 
		case V6M_CMD_Sign_Cnt:{ptr = Photo_SignAndCount; }break; 	// ǩ��					  Photo_SignAndCount
		case V6M_CMD_Sign_Chk:{ptr = Photo_SignAndChk; }break;    //����
		case V6M_CMD_Sign_F1:{ptr = ViewMode_F1; }break;    //
		case V6M_CMD_Sign_F2:{ptr = ViewMode_F2; }break;    //����
		case V6M_CMD_Sign_F3:{ptr = ViewMode_F3; }break;    //����
		case V6M_CMD_Sign_F4:{ptr = ViewMode_F4; }break;    //����

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

