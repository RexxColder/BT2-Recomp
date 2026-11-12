#include "common.h"

void *func_0010B078(void);
void func_001017F0(s32 arg0, s32 arg1, u8 *arg2);
void *memset(void *arg0, s32 arg1, u32 arg2);
extern u8 *D_003876A0;
extern u8 *D_00387F2C;
void func_00118200(void);

void func_0010B278(void) {
    u8 *s0;
    s32 t;

    s0 = func_0010B078();
    if (*(s32 *)(D_003876A0 + 0xB8) != 6 && *(s32 *)(s0 + 0x1350) == 0) {
        t = *(s32 *)(D_003876A0 + 0xC4) * 7;
        func_001017F0(!(*(s32 *)(D_00387F2C + 0x1008) & 1) ? (t + 0x37DB) : (t + 0x3BF4), 0, D_00387F2C);
        memset(s0, 0, 0x3C);
        *(s32 *)(s0 + 0x1350) = (s32)func_00118200;
    }
}
