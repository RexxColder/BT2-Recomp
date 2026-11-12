#include "common.h"

void func_002EEA70(void);
void func_002EEB58(void);
void func_002EEC28(void);
void func_002EECF8(void);
void func_002EEDC8(void);
void func_002EEEF8(void);
void func_002EEFC8(void);
void func_0032EAF0(s32 arg0, s32 arg1);
void func_003077D8(s32 arg0, s32 arg1);
void func_003077F0(s32 arg0, s32 arg1);
void func_00307B38(void);
extern s32 D_0034BB68 __attribute__((section(".data")));
extern s32 D_0034BC08 __attribute__((section(".data")));
extern s32 D_00353498 __attribute__((section(".data")));
extern s32 gFileReq __attribute__((section(".data")));

void func_002EF6F8(void) {
    s32 temp_v0;

    temp_v0 = gFileReq - 1;
    gFileReq = temp_v0;
    if (temp_v0 == 0) {
        func_002EEA70();
        func_002EEB58();
        func_002EEC28();
        func_002EEDC8();
        func_002EECF8();
        func_002EEEF8();
        func_002EEFC8();
        func_0032EAF0(D_0034BC08, D_00353498);
        func_003077D8(0, 0);
        func_003077F0(0, 0);
        D_0034BB68 = 0;
        func_00307B38();
    }
}
