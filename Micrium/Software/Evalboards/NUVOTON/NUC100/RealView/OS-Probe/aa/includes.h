/*
*********************************************************************************************************
*                                              EXAMPLE CODE
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
*                                             MASTER INCLUDES
*
*                                         Nuvoton Cortex M0
*                                                 on the
*                                             NUC1xx Board
*
* Filename      : includes.h
* Version       : V1.00
* Programmer(s) : BAN
*********************************************************************************************************
*/

#ifndef __INCLUDES_H__
#define __INCLUDES_H__

#include    <stdio.h>
#include    <string.h>
#include    <ctype.h>
#include    <stdlib.h>
#include    <stdarg.h>

#include    <ucos_ii.h>

#include    <cpu.h>

#include    <app_cfg.h>
#include    <bsp.h>

//#include    "NUC1xx.h"

#if (uC_SERIAL_MODULE > 0)
#include    <serial.h>
#include    <serial_hw.h>
#endif

#endif
