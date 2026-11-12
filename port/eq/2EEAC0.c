#include "common.h"

void func_002EEA70(void);
void func_002EEC28(void);
void func_002EECF8(void);
void func_002EEDC8(void);
void func_002EEFC8(void);
void func_003077D8(s32 arg0, s32 arg1);
void func_003077F0(s32 arg0, s32 arg1);
void func_00307B38(void);
void func_0032EAF0(s32 arg0, s32 arg1);
extern s32 D_0034BC08 __attribute__((section(".data")));
extern s32 D_00353498 __attribute__((section(".data")));
extern s32 gFileReq __attribute__((section(".data")));

void func_002EEAC0(void) {
    s32 v;

    v = gFileReq - 1;
    gFileReq = v;
    if (v == 0) {
        func_002EEA70();
        func_002EEC28();
        func_002EEDC8();
        func_002EECF8();
        func_002EEFC8();
        func_0032EAF0(D_0034BC08, D_00353498);
        func_003077D8(0, 0);
        func_003077F0(0, 0);
        func_00307B38();
    }
}
