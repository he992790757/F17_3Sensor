/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright (c) Nuvoton Technology Corp. All rights reserved.                                             */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#ifndef _HID_API_H
#define _HID_API_H

#ifdef  __cplusplus
extern "C"
{
#endif

    extern const uint8_t gau8MouseReport[];
    extern const uint8_t gau8MouseReportDescriptor[];
    extern const uint32_t gu32MouseReportDescriptorSize;
    extern const uint8_t gau8StringLang[];
    extern const uint8_t gau8StringSerial[];
    extern const uint8_t gau8DeviceDescriptor[];
    extern const uint8_t gau8ConfigDescriptor[];
    extern const uint8_t gau8VendorStringDescriptor[];
    extern const uint8_t gau8ProductStringDescriptor[];
    extern const uint8_t gau8StringSerial[];
	extern void HID_Init(void *pfGetInReport, void *pfSetOutReport);
	extern void HID_GetInReport(uint8_t *buf);
	extern void HID_SetOutReport(uint8_t *pu8EpBuf);
	
	extern void SendByte(uint8_t data); 
	void USB_SendBackData(uint8_t bError, const uint8_t *pu8Buffer, uint32_t u32Size)  ;
#ifdef  __cplusplus
}
#endif

#endif // #ifndef _HID_API_H



