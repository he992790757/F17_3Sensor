;********************************************************************************************************
;                                               uC/OS-II
;                                         The Real-Time Kernel
;
;                               (c) Copyright 1992-2010, Micrium, Weston, FL
;                                          All Rights Reserved
;
;                               ARM Cortex-M0 Port (without OS extensions)
;
; File      : OS_CPU_A.ASM
; Version   : V2.86
; By        : Jean J. Labrosse
;
; For       : ARMv6M Cortex-M0 (without OS extensions)
; Mode      : Thumb2
; Toolchain : RealView Development Suite
;             RealView Microcontroller Development Kit (MDK)
;             ARM Developer Suite (ADS)
;             Keil uVision
;********************************************************************************************************

;********************************************************************************************************
;                                           PUBLIC FUNCTIONS
;********************************************************************************************************

    EXTERN  OSRunning                                           ; External references
    EXTERN  OSPrioCur
    EXTERN  OSPrioHighRdy
    EXTERN  OSTCBCur
    EXTERN  OSTCBHighRdy
    EXTERN  OSIntNesting
    EXTERN  OSIntExit
    EXTERN  OSTaskSwHook
    EXTERN  OS_CPU_ExceptHndlr
    EXTERN  OS_CPU_ExceptStkBase
    EXTERN  OS_CPU_CtxSw

    
    EXPORT  OS_CPU_SR_Save                                      ; Functions declared in this file
    EXPORT  OS_CPU_SR_Restore
    EXPORT  OSStartHighRdy
    EXPORT  OSCtxSw
    EXPORT  OSIntCtxSw
    EXPORT  OS_CPU_CM0_ExceptHndlr


;********************************************************************************************************
;                                                EQUATES
;********************************************************************************************************

CM0_SETPEND     EQU     0xE000E200
CM0_IRQ0SET     EQU     0xFFFFFFFF

;********************************************************************************************************
;                                      CODE GENERATION DIRECTIVES
;********************************************************************************************************

    AREA |.text|, CODE, READONLY, ALIGN=2
	THUMB
	REQUIRE8
	PRESERVE8
        
;*********************************************************************************************************
;                                   CRITICAL SECTION METHOD 3 FUNCTIONS
;
; Description: Disable/Enable interrupts by preserving the state of interrupts.  Generally speaking you
;              would store the state of the interrupt disable flag in the local variable 'cpu_sr' and then
;              disable interrupts.  'cpu_sr' is allocated in all of uC/OS-II's functions that need to
;              disable interrupts.  You would restore the interrupt disable state by copying back 'cpu_sr'
;              into the CPU's status register.
;
; Prototypes :     OS_CPU_SR  OS_CPU_SR_Save(void);
;                  void       OS_CPU_SR_Restore(OS_CPU_SR cpu_sr);
;
;
; Note(s)    : 1) These functions are used in general like this:
;
;                 void Task (void *p_arg)
;                 {
;                 #if OS_CRITICAL_METHOD == 3          /* Allocate storage for CPU status register */
;                     OS_CPU_SR  cpu_sr;
;                 #endif
;
;                          :
;                          :
;                     OS_ENTER_CRITICAL();             /* cpu_sr = OS_CPU_SaveSR();                */
;                          :
;                          :
;                     OS_EXIT_CRITICAL();              /* OS_CPU_RestoreSR(cpu_sr);                */
;                          :
;                          :
;                 }
;*********************************************************************************************************

OS_CPU_SR_Save
        MRS     R0, PRIMASK                 ; Set prio int mask to mask all (except faults)
        CPSID   I
        BX      LR


OS_CPU_SR_Restore
        MSR     PRIMASK, R0
        BX      LR


;*********************************************************************************************************
;                                          START MULTITASKING
;                                       void OSStartHighRdy(void)
;
; Note(s) : 1) OSStartHighRdy() MUST:
;              a) Call OSTaskSwHook() then,
;              b) Set OSRunning to TRUE,
;              c) Switch to the highest priority task.
;
;           2) When tested with IAR EWARM, the processor reaches the startup code in handler mode.
;              Consequently, to re-enable interrupts, it is necessary to return from OSStartHighRdy()
;              as if returning from an exception.  The commented code at the end of this function
;              performs the 'normal' function return and MIGHT need to be substituted for the last three
;              lines of code in this function, which load the link register with the exception return
;              value and then return.
;*********************************************************************************************************

OSStartHighRdy
    LDR     R0, __OS_TaskSwHook                                 ; OSTaskSwHook();
    BLX     R0

    LDR     R0, __OS_Running                                    ; OSRunning = TRUE;
    MOVS    R1, #1
    STRB    R1, [R0]
    
                                                                ; SWITCH TO HIGHEST PRIORITY TASK:
    LDR     R0, __OS_TCBHighRdy                                 ;   Get highest priority task TCB address,
    LDR     R1, [R0]                                            ;   Get stack pointer,
    LDR     R2, [R1]
    MSR     MSP, R2                                             ;   Switch to the new stack,
    
    POP    {R0-R7}                                              ;   Pop new task's R8-R11 (into R0-R3), R4-R7
    MOV     R8,  R0                                              
    MOV     R9,  R1
    MOV     R10, R2
    MOV     R11, R3    
        
                                                                ; NORMAL FUNCTION RETURN (see Note #2)
    ADD     SP, #0x10
    POP    {R0-R3}                                              ;   Pop new task's R12, PC, LR, PSR into (R0, R1, R2, R3, respectively)
    MOV     R12, R0
    MOV     LR,  R1
    MSR     PSR, R3
    
    PUSH   {R2}                                                 ;   Save PC
    
    SUB     SP, #0x1C                                           
    POP    {R0-R3}                                              ;   Pop new task's R0-R3
    ADD     SP, #0x0C
    
    CPSIE   I                                                   ;   Enable interrupts
    
    POP    {PC}                                                 ;   Pop new task's PC
    
                                                                ; EXCEPTION FUNCTION RETURN (see Note #2)
;   LDR     R0, =CM1_EXCEPTRTN                                  ; Load LR (R14) with exception return value.
;   MOV     LR,  R0
;
;   BX      LR                                                  ; Return, as if from exception.
   
    
;*********************************************************************************************************
;                                PERFORM A CONTEXT SWITCH (From task level)                               
;                                                OSCtxSw()                                                    
;
; Note(s) : 1) OSCtxSw() is called when OS wants to do a task context switch.
;
;           2) This function triggers an IRQ #0, which will perform the context switch.  The variable
;              OS_CPU_CtxSw is set to '1' to indicate that a context switch should be performed.
;*********************************************************************************************************

OSCtxSw
 ;   LDR     R0, __OS_CPU_CtxSw                                  ; OS_CPU_CtxSw = TRUE
 ;   MOVS    R1, #1
 ;   STRB    R1, [R0]
    
 ;   LDR     R0, =CM0_SETPEND                                    ; Trigger interrupt
 ;   LDR     R1, =CM0_IRQ0SET
 ;   STR     R1, [R0]
	CPSID   I
	SUB     SP,#0x10
	PUSH    {R0-R3}

	ADD     SP,#0x20
	MRS     R3, PSR
	MOV		R2, LR
	MOV		R1, LR
	MOV     R0, R12
	PUSH    {R0-R3}

	SUB     SP, #0x10
	MOV 	R0, R8
	MOV 	R1, R9
	MOV 	R2, R10
	MOV 	R3, R11
	PUSH    {R0-R7}

;    LDR     R0, __OS_CPU_CtxSw                                  ; OS_CPU_CtxSw = TRUE
;    MOVS    R1, #1
;    STRB    R1, [R0]

    MRS     R0, MSP
    LDR     R1, __OS_TCBCur                                     ; OSTCBCur->OSTCBStkPtr = SP;
    LDR     R1, [R1]
    STR     R0, [R1]    
 
    LDR     R0, __OS_TaskSwHook                                 ; OSTaskSwHook();
    BLX     R0
;    POP    {R0}
;    MOV     LR, R0
   
    LDR     R0, __OS_PrioCur                                    ; OSPrioCur = OSPrioHighRdy;
    LDR     R1, __OS_PrioHighRdy
    LDRB    R2, [R1]
    STRB    R2, [R0]

    LDR     R0, __OS_TCBCur                                     ; OSTCBCur  = OSTCBHighRdy;
    LDR     R1, __OS_TCBHighRdy
    LDR     R2, [R1]
    STR     R2, [R0]
    
    LDR     R0, [R2]                                            ; SP = OSTCBHighRdy->OSTCBStkPtr;
    MSR     MSP, R0                                             
    
;    LDR     R0, __OS_CPU_CtxSw                                  ; OS_CPU_CtxSw = 0;
;    MOVS    R1, #0
;    STRB    R1, [R0] 
	                                                               ; RESTORE TASK's CONTEXT
    POP    {R0-R7}                                              ;   Pop new task's R8-R11 (into R0-R3), R4-R7
    MOV     R8,  R0                                              
    MOV     R9,  R1
    MOV     R10, R2
    MOV     R11, R3  
	
	ADD     SP, #0x10
    POP    {R0-R3}                                              ;   Pop new task's R12, PC, LR, PSR into (R0, R1, R2, R3, respectively)
    MOV     R12, R0
    MOV     LR,  R1
    MSR     PSR, R3
    
    PUSH   {R2}                                                 ;   Save PC
    
    SUB     SP, #0x1C                                           
    POP    {R0-R3}                                              ;   Pop new task's R0-R3
    ADD     SP, #0x0C 
    CPSIE   I                                                   ;   Enable interrupts
	;CPSID   I
;    BX      LR
    POP    {PC}    
    NOP

;*********************************************************************************************************
;                             PERFORM A CONTEXT SWITCH (From interrupt level)                                
;                                               OSIntCtxSw()                                               
;
; Notes:    1) OSIntCtxSw() is called by OSIntExit() when it determines a context switch is needed as 
;              the result of an interrupt.
;
;           2) This function triggers an IRQ #0, which will perform the context switch.  The variable
;              OS_CPU_CtxSw is set to '1' to indicate that a context switch should be performed.
;*********************************************************************************************************

OSIntCtxSw
 ;   LDR     R0, __OS_CPU_CtxSw                                  ; OS_CPU_CtxSw = TRUE
 ;  MOVS    R1, #1
 ;  STRB    R1, [R0]
    
 ;   LDR     R0, =CM0_SETPEND                                    ; Trigger interrupt
 ;   LDR     R1, =CM0_IRQ0SET
 ;   STR     R1, [R0]
 ;   BX      LR
	CPSID   I
	SUB     SP,#0x10
	PUSH    {R0-R3}

	ADD     SP,#0x20
	MRS     R3, PSR
	MOV		R2, LR
	MOV		R1, LR
	MOV     R0, R12
	PUSH    {R0-R3}

	SUB     SP, #0x10
	MOV 	R0, R8
	MOV 	R1, R9
	MOV 	R2, R10
	MOV 	R3, R11
	PUSH    {R0-R7}

;    LDR     R0, __OS_CPU_CtxSw                                  ; OS_CPU_CtxSw = TRUE
;    MOVS    R1, #1
;    STRB    R1, [R0]

    MRS     R0, MSP
    LDR     R1, __OS_TCBCur                                     ; OSTCBCur->OSTCBStkPtr = SP;
    LDR     R1, [R1]
    STR     R0, [R1]    
 
    LDR     R0, __OS_TaskSwHook                                 ; OSTaskSwHook();
    BLX     R0
;    POP    {R0}
;    MOV     LR, R0
   
    LDR     R0, __OS_PrioCur                                    ; OSPrioCur = OSPrioHighRdy;
    LDR     R1, __OS_PrioHighRdy
    LDRB    R2, [R1]
    STRB    R2, [R0]

    LDR     R0, __OS_TCBCur                                     ; OSTCBCur  = OSTCBHighRdy;
    LDR     R1, __OS_TCBHighRdy
    LDR     R2, [R1]
    STR     R2, [R0]
    
    LDR     R0, [R2]                                            ; SP = OSTCBHighRdy->OSTCBStkPtr;
    MSR     MSP, R0                                             
    
;    LDR     R0, __OS_CPU_CtxSw                                  ; OS_CPU_CtxSw = 0;
;    MOVS    R1, #0
;    STRB    R1, [R0] 
	                                                               ; RESTORE TASK's CONTEXT
    POP    {R0-R7}                                              ;   Pop new task's R8-R11 (into R0-R3), R4-R7
    MOV     R8,  R0                                              
    MOV     R9,  R1
    MOV     R10, R2
    MOV     R11, R3  
	
	ADD     SP, #0x10
    POP    {R0-R3}                                              ;   Pop new task's R12, PC, LR, PSR into (R0, R1, R2, R3, respectively)
    MOV     R12, R0
    MOV     LR,  R1
    MSR     PSR, R3
    
    PUSH   {R2}                                                 ;   Save PC
    
    SUB     SP, #0x1C                                           
    POP    {R0-R3}                                              ;   Pop new task's R0-R3
    ADD     SP, #0x0C 
    CPSIE   I                                                   ;   Enable interrupts
;    BX      LR
    POP    {PC}    
    NOP         


;*********************************************************************************************************
;                                         HANDLE EXTERNAL IRQ #0
;                                        OS_CPU_CM1_ExceptHndlr()                                            
;
; Note(s) : 1) This function handles external IRQ #0.  This port requires that this be the ONLY 
;              external IRQ (though multiple interrupt sources may be multiplexed onto the single vector
;              via an external controller).
;
;           2) A context switch is accomplished by triggering an IRQ from OSCtxSw().  If the exception
;              is going to be used for this purpose, the variable OS_CPU_CtxSw will have been assigned 
;              the value '1' in OSCtxSw().
;*********************************************************************************************************

OS_CPU_CM0_ExceptHndlr    
    CPSID   I
                                                                ; SAVE CONTEXT ONTO TASK STACK:
    MOV     R0, R8                                              
    MOV     R1, R9
    MOV     R2, R10
    MOV     R3, R11
    PUSH   {R0-R7}                                              ;   Push task's R8-R11, R4-R7.

;    LDR     R0, __OS_CPU_CtxSw                                  ; if (OS_CPU_CtxSw == TRUE)
    LDRB    R1, [R0]
    CMP     R1, #1
    BEQ     OS_CPU_CM0_ExceptHndlr_CtxSw
    
    
;*********************************************************************************************************
;                                         HANDLE EXTERNAL IRQ #0
;                                     OS_CPU_CM0_ExceptHndlr_Except()                                            
;
; Note(s) : 1) This function handles external IRQ #0.  This port requires that this be the ONLY 
;              external IRQ (though multiple interrupt sources may be multiplexed onto the single vector
;              via an external controller).
;
;           2) The pseudo-code for OS_CPU_CM1_ExceptHndlr_Except() is:
;              a) Save registers r4-r11 on task stack (which is the current stack);
;              b) OSTCBCur->OSTCBStkPtr = SP;
;              c) OSIntNesting++;
;              d) SP = OS_CPU_ExceptStkBase;
;              e) OS_CPU_ExceptHndlr();
;              f) OSIntExit();
;              g) SP = OSTCBCur->OSTCBStkPtr;
;              h) Restore new task's R4-R11 from new task's stack;
;              i) Perform exception return which will restore R0-R3, R12, LR, PC, PSR.
;
;           3) On entry into this function:
;              a) OS_CPU_CtxSw == 0
;              b) The following have been saved on the task stack (by processor):
;                 xPSR, PC, LR, R12, R0-R3
;              c) The following have been saved on the task stack (by OS_CPU_CM1_ExceptHndlr):
;                 R8-R11, R4-R7
;              d) OSTCBCur points to the OS_TCB of the current task
;*********************************************************************************************************

OS_CPU_CM0_ExceptHndlr_Except
    LDR     R0, __OS_TCBCur                                     ;   OSTCBCur->OSTCBStkPtr = SP;
    LDR     R1,  [R0]
    MRS     R2,  MSP
    STR     R2,  [R1]

                                                                ; HANDLE NESTING COUNTER:
    LDR     R0, __OS_IntNesting                                 ;   OSIntNesting++;
    LDRB    R1, [R0]
    ADDS    R1, #1
    STRB    R1, [R0]

    LDR     R0, __OS_CPU_ExceptStkBase                          ; SP = OS_CPU_ExceptStkBase;
    LDR     R1, [R0]
    MSR     MSP, R1
    
    PUSH   {LR}                                                 ; Push exception return.
    
                                                                ; EXECUTE EXCEPTION HANDLER:
    LDR     R0, __OS_CPU_ExceptHndlr                            ;   OS_CPU_ExceptHndlr()
    BLX     R0
 
    LDR     R0, __OS_IntExit                                    ; OSIntExit()
    BLX     R0
    
    POP    {R0}                                                 ; Pop exception return.
    MOV     LR, R0

    LDR     R0, __OS_TCBCur                                     ; SP = OSTCBCur->OSTCBStkPtr;
    LDR     R1,  [R0]
    LDR     R2,  [R1]
    MSR     MSP,  R2
    
                                                                ; RESTORE TASK's CONTEXT
    POP    {R0-R7}                                              ;   Pop new task's R8-R11 (into R0-R3), R4-R7
    MOV     R8,  R0                                              
    MOV     R9,  R1
    MOV     R10, R2
    MOV     R11, R3    

    CPSIE   I
    BX      LR                                                  ; Exception return restores R0-R3, R12, LR, PC, PSR
    
;*********************************************************************************************************
;                                         EXECUTE CONTEXT SWTICH
;                                      OS_CPU_CM0_ExceptHndlr_CtxSw()                                            
;
; Note(s) : 1) OS_CPU_CM1_ExceptHndlr_CtxSw(), called from OS_CPU_CM1_ExceptHndlr(), is used to cause a
;              context switch, similar to the use of OSPendSV on a Cortex-M3.  Using the exception this way
;              means that context saving and restoring is identical whether it is initiated from a thread 
;              or occurs due to an interrupt or exception. 
;
;           2) The pseudo-code for OS_CPU_CM1_ExceptHndlr_CtxSw() is:
;              b) OSTCBCur->OSTCBStkPtr = SP;
;              c) OSTaskSwHook();
;              d) OSPrioCur    = OSPrioHighRdy;
;              e) OSTCBCur     = OSTCBHighRdy;
;              f) SP           = OSTCBHighRdy->OSTCBStkPtr;
;              g) Restore new task's R4-R11 from new task's stack;
;              h) OS_CPU_CtxSw = 0;
;              i) Perform exception return which will restore R0-R3, R12, LR, PC, PSR.
;
;           3) On entry into this function:
;              a) OS_CPU_CtxSw == 1
;              b) The following have been saved on the task stack (by processor):
;                 xPSR, PC, LR, R12, R0-R3
;              c) The following have been saved on the task stack (by OS_CPU_CM1_ExceptHndlr):
;                 R8-R11, R4-R7
;              d) OSTCBCur     points to the OS_TCB of the task to suspend
;                 OSTCBHighRdy points to the OS_TCB of the task to resume
;*********************************************************************************************************

OS_CPU_CM0_ExceptHndlr_CtxSw
    PUSH   {LR}
    LDR     R0, __OS_TaskSwHook                                 ; OSTaskSwHook();
    BLX     R0
    POP    {R0}
    MOV     LR, R0

    MRS     R0, MSP
    LDR     R1, __OS_TCBCur                                     ; OSTCBCur->OSTCBStkPtr = SP;
    LDR     R1, [R1]
    STR     R0, [R1]    
    
    LDR     R0, __OS_PrioCur                                    ; OSPrioCur = OSPrioHighRdy;
    LDR     R1, __OS_PrioHighRdy
    LDRB    R2, [R1]
    STRB    R2, [R0]

    LDR     R0, __OS_TCBCur                                     ; OSTCBCur  = OSTCBHighRdy;
    LDR     R1, __OS_TCBHighRdy
    LDR     R2, [R1]
    STR     R2, [R0]
    
    LDR     R0, [R2]                                            ; SP = OSTCBHighRdy->OSTCBStkPtr;
    MSR     MSP, R0                                             
    
                                                                ; RESTORE NEW TASK's CONTEXT
    POP    {R0-R7}                                              ;   Pop new task's R8-R11 (into R0-R3), R4-R7
    MOV     R8,  R0                                              
    MOV     R9,  R1
    MOV     R10, R2
    MOV     R11, R3    
    
;    LDR     R0, __OS_CPU_CtxSw                                  ; OS_CPU_CtxSw = 0;
;    MOVS    R1, #0
;    STRB    R1, [R0] 
    
    CPSIE   I
    BX      LR                                                  ; Exception return restores R0-R3, R12, LR, PC, PSR
    
    NOP
    
;*********************************************************************************************************
;                                     POINTERS TO VARIABLES
;*********************************************************************************************************

__OS_CPU_CtxSw
    DCD     OS_CPU_CtxSw

__OS_CPU_ExceptStkBase
    DCD     OS_CPU_ExceptStkBase
    
__OS_CPU_ExceptHndlr
    DCD     OS_CPU_ExceptHndlr

__OS_TaskSwHook
    DCD     OSTaskSwHook

__OS_IntExit
    DCD     OSIntExit

__OS_IntNesting
    DCD     OSIntNesting

__OS_PrioCur
    DCD     OSPrioCur

__OS_PrioHighRdy
    DCD     OSPrioHighRdy

__OS_Running
    DCD     OSRunning

__OS_TCBCur
    DCD     OSTCBCur

__OS_TCBHighRdy
    DCD     OSTCBHighRdy

    END
