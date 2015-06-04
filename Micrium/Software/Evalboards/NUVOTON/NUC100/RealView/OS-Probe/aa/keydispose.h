#ifndef KEYDISPOSE_H
#define KEYDISPOSE_H


#include"stdint.h"

extern  uint32_t SysVersion[3]; 

 void KeyDispose(void);
void KeyDispose_debug(void);
 void TESTA(void);
 void TESTB(void);
 void TESTC(void);
 void TESTD(void);
 void TESTE(void);
//void InitKeyLed(void);
//void Stand_by(void);
//void TEST(void);
//void TEST_PH(void);
//void Light_Init_test(void);
//  void InitStart(void);
void TestHardWareInit(void);
void  SysVersionChange(void) ;

#endif
