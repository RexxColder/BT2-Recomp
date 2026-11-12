#include "common.h"

s32 Dma_BeginDirect(void);
void Dma_EndDirect(s32 arg0);
s64 func_0026E310(s32 arg0, s32 arg1, s64 arg2);
s32 func_0026E468(s32 arg0, s32 arg1, s64 arg2);
s32 func_00271370(void);

void func_0026E6D8(s32 arg0, s32 arg1) {
    s64 s1;
    s32 t;
    s32 v1;
    s64 var_v0;

    s1 = 0;
    if (arg0 != 0) {
        s1 = func_0026E310(arg0, *(s32 *)(arg1 + 0x34), 0x3000);
        func_00271370();
    }
    t = Dma_BeginDirect();
    *(s64 *)(t + 0x00) = ((s64)0x10000000 << 32) | 0x8005;
    *(s64 *)(t + 0x08) = 0xE;
    *(s64 *)(t + 0x10) = 1;
    *(s64 *)(t + 0x18) = 0x46;
    v1 = *(s32 *)arg1;
    if (v1 & 8) {
        var_v0 = 0x48;
    } else {
        var_v0 = 0x42;
        if (!(v1 & 0x10)) {
            var_v0 = 0x44;
        }
    }
    *(s64 *)(t + 0x20) = var_v0;
    *(s64 *)(t + 0x28) = 0x42;
    *(s64 *)(t + 0x30) = 0x60;
    *(s64 *)(t + 0x38) = 0x14;
    *(s64 *)(t + 0x40) = 0x30000;
    *(s64 *)(t + 0x48) = 0x47;
    if (*(s32 *)arg1 & 4) {
        *(s64 *)(t + 0x50) = 0;
    } else {
        *(s64 *)(t + 0x50) = 5;
    }
    *(s64 *)(t + 0x58) = 8;
    Dma_EndDirect(func_0026E468(t + 0x60, arg1, s1));
}
