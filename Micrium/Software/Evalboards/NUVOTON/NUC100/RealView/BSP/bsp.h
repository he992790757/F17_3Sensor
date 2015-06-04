/*
*********************************************************************************************************
*                                      MICRIUM BOARD SUPPORT SUPPORT
*
*                              (c) Copyright 2007; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                          BOARD SUPPORT PACKAGE
*
*                                         Analog Devices ADuC7026
*                                                 on the
*                                        ADuC7026 Evaluation Board
*
* Filename      : bsp.h
* Version       : V1.00
* Programmer(s) : BAN
*********************************************************************************************************
*/

#ifndef  __BSP_H__
#define  __BSP_H__

/*
*********************************************************************************************************
*                                                 EXTERNS
*********************************************************************************************************
*/

#ifdef   BSP_GLOBALS
#define  BSP_EXT
#else
#define  BSP_EXT  extern
#endif

/*
*********************************************************************************************************
*                                                 DEFINES
*********************************************************************************************************
*/

#define  MAIN_OSC_FRQ                               41780000L
#define  RTC_OSC_FRQ                                   32768L

#define  BSP_IRQ_SWI                                       1
#define  BSP_IRQ_TIMER0                                    2
#define  BSP_IRQ_TIMER1                                    3
#define  BSP_IRQ_TIMER2                                    4
#define  BSP_IRQ_TIMER3                                    5
#define  BSP_IRQ_FLASH                                     6
#define  BSP_IRQ_ADC                                       7
#define  BSP_IRQ_PLL                                       8
#define  BSP_IRQ_I2C0_SLAVE                                9
#define  BSP_IRQ_I2C0_MASTER                              10
#define  BSP_IRQ_I2C1_MASTER                              11
#define  BSP_IRQ_SPI_SLAVE                                12
#define  BSP_IRQ_SPI_MASTER                               13
#define  BSP_IRQ_UART                                     14
#define  BSP_IRQ_IRQ0                                     15
#define  BSP_IRQ_COMPARATOR                               16
#define  BSP_IRQ_PSM                                      17
#define  BSP_IRQ_IRQ1                                     18
#define  BSP_IRQ_PLA_IRQ0                                 19
#define  BSP_IRQ_PLA_IRQ1                                 20
#define  BSP_IRQ_IRQ2                                     21
#define  BSP_IRQ_IRQ3                                     22
#define  BSP_IRQ_PWM                                      23

/*
*********************************************************************************************************
*                                            GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                                 MACRO'S
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void         BSP_Init           (void);
void         BSP_IntDisAll      (void);
void         BSP_IntVectSet     (CPU_INT08U     irq_id,
                                 CPU_FNCT_VOID  isr_hndlr);
void         BSP_IntEn          (CPU_INT08U     irq_id);
CPU_INT32U   BSP_CPU_ClkFreq    (void);


/*
*********************************************************************************************************
*                                              LED SERVICES
*********************************************************************************************************
*/

void         LED_On             (CPU_INT08U  led);
void         LED_Off            (CPU_INT08U  led);
void         LED_Toggle         (CPU_INT08U  led);

/*
*********************************************************************************************************
*                                              PB SERVICES
*********************************************************************************************************
*/

CPU_BOOLEAN  PB_GetStatus       (CPU_INT08U  pb);

/*
*********************************************************************************************************
*                                              ADC SERVICES
*********************************************************************************************************
*/

CPU_INT16U   ADC_GetStatus      (CPU_INT08U   adc);

/*
*********************************************************************************************************
*                                              DAC SERVICES
*********************************************************************************************************
*/

void         DAC_SetOutput      (CPU_INT08U   dac,
                                 CPU_INT16U   output);

/*
*********************************************************************************************************
*                                              TICK SERVICES
*********************************************************************************************************
*/

void         Tmr_TickISR_Handler(void);




#endif
