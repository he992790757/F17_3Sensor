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

V6MDEBUG_EXT volatile Status  MCU_Status;			//���Ͷ���ṹ��	
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
//#define V6M_CMD_USB_U		0x0FUL		 	//u��

#define V6M_CMD_Down		0x10UL

#define V6M_CMD_Right		0x12UL
#define V6M_CMD_ZoomUp		0x13UL
#define V6M_CMD_ZoomDown	0x14UL		   //
#define V6M_CMD_Photo		0x15UL		   //����
#define V6M_CMD_Del_Photo	0x16UL		   //ɾ������
#define V6M_CMD_PhotoLong	0x17UL		   //ɾ��ȫ��
#define V6M_CMD_OverView	0x18UL		   //ȫ��
#define V6M_CMD_PartView	0x19UL		   //�ֲ�
#define V6M_CMD_SpecView	0x1AUL		   //ϸ�ھֲ�
#define V6M_CMD_C608		0x1BUL		   //c608
#define V6M_CMD_HDMI		0x1CUL		   // HDMI
#define V6M_CMD_HDMI_OUT	0x1DUL		   // �˳�HDMI
#define V6M_CMD_RESET		0x1EUL		   // ��λϵͳ
#define V6M_CMD_FORMAT_SD	0x1FUL		   // ��ʽ��SD
#define V6M_CMD_RESET_DSP	0x20UL		   // ��λDSP
#define V6M_CMD_IR_940_test	0x21UL

//#define V6M_CMD_SHARPNESS  	0x21UL			//���
//#define V6M_CMD_CONTRAST	0x22UL			//�Աȶ�
//#define V6M_CMD_SATURATION	0x23UL			//���Ͷ�
//#define V6M_CMD_BRIGHTNESS	0x24UL			//����



#define V6M_CMD_View		0x33UL		   //Ԥ��
#define V6M_CMD_Play		0x34UL		   //�ط�
#define V6M_CMD_SL			0x35UL		   //����
#define V6M_CMD_WU			0x36UL		   //����
#define V6M_CMD_FZ			0x37UL		   //��Ƭ���飬������

#define V6M_CMD_SLP_DIS		0x38UL		   //��������
#define V6M_CMD_SLP_EN		0x39UL		   //��������


//=============��ѯ=======================
#define V6M_CMD_C_Sys_Inf	0x80UL		   //ϵͳ��Ϣ
#define V6M_CMD_C_Mac_Ver	0x81UL		   //�����ͺ�
#define V6M_CMD_C_Pro_Num	0x82UL		   //��Ʒ���к�
#define V6M_CMD_C_Mac_Num	0x83UL		   //�������
#define V6M_CMD_C_Sof_Ver	0x84UL		   //����汾
#define V6M_CMD_C_Pro_Dat	0x85UL		   //��������

//=============�޸�=======================
#define V6M_CMD_M_Mac_Ver	0x86UL		   //�����ͺ�
#define V6M_CMD_M_Pro_Num	0x87UL		   //��Ʒ���к�
#define V6M_CMD_M_Mac_Num	0x88UL		   //�������
#define V6M_CMD_M_Sof_Ver	0x89UL		   //����汾
#define V6M_CMD_M_Hrd_Ver	0x8CUL		   //Ӳ���汾
#define V6M_CMD_M_Pro_Dat	0x8AUL		   //��������


#define V6M_CMD_AlarmSound	0x8FUL		   //����������������


#define V6M_CMD_Check_Stat	0x90UL		   //��ѯϵͳ״̬
#define V6M_CMD_USB_U		0x91UL		   //����U��ģʽ  
#define V6M_CMD_USB_U_Out	0x92UL		   //�˳�U��ģʽ
#define V6M_CMD_USB_PC		0x93UL		   //����PC-CAM
#define V6M_CMD_USB_PC_Out	0x94UL		   //�˳�PC-CAM

//=============ָ��=======================
#define V6M_CMD_ZHUANFA		0xA0UL		   //ת��ָ��
#define V6M_CMD_PASSWRD		0xA1UL		   // �ָ�ԭ������	
#define V6M_CMD_SETTIME		0xA2UL		   // ����ʱ��	
#define V6M_CMD_SETUVC		0xA3UL		   // �����Ϲ��ع�ֵ
#define V6M_CMD_UNLOCK_TM	0xA4UL		   // ȡ�������������
#define V6M_CMD_SETUVC71	0xA6UL		   // ����sen2�Ϲ��ع�ֵ
#define V6M_CMD_SETUVC72	0xA7UL		   // ����sen3�Ϲ��ع�ֵ
#define V6M_CMD_C_Hrd_Ver	0xA8UL		   // Ӳ���汾 


#define V6M_CMD_Chk_Phot	0xA9UL		   // ���һ����� 
#define V6M_CMD_Ext_Black	0xAAUL		   // �˳�������ʾ�ַ�
#define V6M_CMD_Chk_Phot_2	0xABUL		   // ���ɣ� ���һ�����
#define	V6M_CMD_Sign_Cnt	0xACUL		   // ǩ��
#define	V6M_CMD_Sign_Chk	0xADUL		   // ����
#define	V6M_CMD_Sign_F1  	0xAEUL		   // F1���� 
#define	V6M_CMD_Sign_F2  	0xAFUL		   // F2���� 
#define	V6M_CMD_Sign_F3  	0xB0UL		   // F3���� 
#define	V6M_CMD_Sign_F4  	0xB1UL		   // F4���� 

#define V6M_CMD_SIDE_W_90   0xB4UL			//��׹⣨ǰ����
#define V6M_CMD_Photo_Four  0xB5UL		   	//4����
#define V6M_CMD_AUTO_VIEW	0xB6UL	  		//�Զ�Ԥ��
#define V6M_CMD_PH_ARGV	    0xB7UL	  		//��Ƭ�����趨

#define V6M_CMD_AutoExposure 0xB9UL		   	//  У��
#define V6M_CMD_PH_ADJUST	 0xBAUL	  		//��Ƭ�����趨 ����ÿ�ֹ�Դ����,�鿴


#define V6M_CMD_PH_NUM	 	 0xBCUL	  		//��������޸ı�����Ƭ������ֵ
#define V6M_CMD_PH_NUM_Dec 	 0xBDUL	  		//��������޸ı�����Ƭ�����ļ���
#define V6M_CMD_XY_ZOOM      0xBFUL		   	//��USB������ λ�÷Ŵ�
#define V6M_CMD_C_Sign_NUM	 0xC0UL		    // ǩ������ 

#define V6M_CMD_UV_365_EX1		0xC1UL		//�Ϲ��ֶ��ع�ֵ1
#define V6M_CMD_UV_365_EX2		0xC2UL		//�Ϲ��ֶ��ع�ֵ2

#define V6M_CMD_Photo_Eight  0xC5UL		   	//8����

#define V6M_CMD_DeepComPs    0xC6UL               //�������յȼ�



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
