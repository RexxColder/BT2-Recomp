#include "common.h"

/* 0x001FBEB0: if (func_00211310(a0, 0xE, 1)) DemoCam_Stop(a0); if (func_00211310(a0, 0xE, 2)) func_0025AE48(a0->+0x1534);
   if (func_00211310(a0, 0xE, 4)) func_0025AEB8(a0->+0x1534); if (func_00211310(a0, 0xE, 8)) tail func_0025AF28(a0->+0x1534). */
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void DemoCam_Stop(void);
void func_0025AE48(s32 arg0);
void func_0025AEB8(s32 arg0);
void func_0025AF28(s32 arg0);

void func_001FBEB0(s32 a0) {
    if (func_00211310(a0, 0xE, 1) != 0) {
        DemoCam_Stop();
    }
    if (func_00211310(a0, 0xE, 2) != 0) {
        func_0025AE48(*(s32 *)((u8 *)a0 + 0x1534));
    }
    if (func_00211310(a0, 0xE, 4) != 0) {
        func_0025AEB8(*(s32 *)((u8 *)a0 + 0x1534));
    }
    if (func_00211310(a0, 0xE, 8) != 0) {
        func_0025AF28(*(s32 *)((u8 *)a0 + 0x1534));
    }
}
