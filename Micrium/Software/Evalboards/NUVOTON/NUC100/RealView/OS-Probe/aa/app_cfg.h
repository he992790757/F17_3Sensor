/*

*********************************************************************************************************

*                                       APPLICATION CONFIGURATION

*

*                             (c) Copyright 2010, Micrium, Inc., Weston, FL

*                                          All Rights Reserved

*


*********************************************************************************************************

*/

/*
*********************************************************************************************************
*
*                                       APPLICATION CONFIGURATION
*
*                                             NUCVTON NUC1XX
*                                                on the
*                                  NUC100 Evaluation Board
*
* Filename      : app_cfg.h
* Version       : V1.00
* Programmer(s) : Ken
*********************************************************************************************************
*/

/*

*********************************************************************************************************

*                                            TASK PRIORITIES

*********************************************************************************************************

*/
#ifndef __UCOS_APP_CFG_H
#define __UCOS_APP_CFG_H

#include <stdint.h>

#define OS_TASK_TMR_PRIO	26//The priority of the Timer management task

int32_t OS_UART_HANDLE(void);

//#define SEM_TEST
//#define THREAD_TEST
//#define MBOX_TEST
//#define FLAG_TEST   
//#define MALLOC_TEST
//#define MEM_TEST
//#define MUTEX_TEST
//#define QUEUE_TEST
//#define TMR_TEST
//#define USER_TEST   
//===============================≤‚ ‘=======================
#define THREAD_TEST //We use this macro for test sample.


//==========================================================

#define   DEF_FALSE 0
#define   DEF_TRUE  1

/*
*********************************************************************************************************
*                                       ADDITIONAL uC/MODULE ENABLES
*********************************************************************************************************
*/

#define  uC_PROBE_OS_PLUGIN              DEF_DISABLED            /* DEF_ENABLED = Present, DEF_DISABLED = Not Present        */
#define  uC_PROBE_COM_MODULE             DEF_DISABLED

/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/

#define  APP_TASK_START_PRIO                   3
#define  APP_TASK_KBD_PRIO                     4
#define  APP_TASK_USER_IF_PRIO                 5
#define  APP_TASK_PROBE_STR_PRIO               6

#define  OS_PROBE_TASK_PRIO                    8
#define  OS_PROBE_TASK_ID                      8

//#define  OS_TASK_TMR_PRIO              (OS_LOWEST_PRIO - 2)

/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*********************************************************************************************************
*/
//#define  APP_TASK_START_STK_SIZE             128
//#define  APP_TASK_USER_IF_STK_SIZE           256						   
//#define  APP_TASK_KBD_STK_SIZE               256

#define  APP_TASK_START_STK_SIZE             1
#define  APP_TASK_USER_IF_STK_SIZE           1						   
#define  APP_TASK_KBD_STK_SIZE               1

//#define  APP_TASK_PROBE_STR_STK_SIZE         64
//
//#define  OS_PROBE_TASK_STK_SIZE              64

#define  APP_TASK_PROBE_STR_STK_SIZE         64

#define  OS_PROBE_TASK_STK_SIZE              64
/*
*********************************************************************************************************
*                               uC/Probe plug-in for uC/OS-II CONFIGURATION
*********************************************************************************************************
*/

#define  OS_PROBE_TASK                         1                /* Task will be created for uC/Probe OS Plug-In             */
#define  OS_PROBE_TMR_32_BITS                  0                /* uC/Probe OS Plug-In timer is a 16-bit timer              */
#define  OS_PROBE_TIMER_SEL                    2
#define  OS_PROBE_HOOKS_EN                     1

#endif//__UCOS_APP_CFG_H
