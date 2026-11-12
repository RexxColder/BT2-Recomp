#include "common.h"

s32 strcmp(const char *a, const char *b);
extern u8 D_00387A48[] __attribute__((section(".data")));
extern u8 D_00376808[] __attribute__((section(".data")));
extern u8 D_00387A50[] __attribute__((section(".data")));
extern u8 D_00387A58[] __attribute__((section(".data")));
extern u8 D_00387A60[] __attribute__((section(".data")));
extern u8 D_00387A68[] __attribute__((section(".data")));
extern u8 D_00376818[] __attribute__((section(".data")));
extern u8 D_00376828[] __attribute__((section(".data")));

void func_0026C1F0(u8 *arg0, u8 *arg1) {
    u8 buf[0x50];   /* tamano de locales del original (antes 0x44) */
    s32 s0;
    s32 n;
    s32 val;
    u8 c;

    s0 = 1;
    n = 0;
    buf[0] = arg1[0];
    if (arg1[0] != 0) {
        do {
            c = arg1[s0];
            s0 += 1;
            n += 1;
            buf[n] = c;
        } while (c != 0);
    }
    buf[0x40] = arg1[s0];
    buf[0x41] = arg1[s0 + 1];
    if (buf[0x40] == 0 && buf[0x41] == 0) {
        return;
    }
    s0 += 2;
    val = (s32)(long)(arg1 + s0);
    if (strcmp((const char *)buf, (const char *)D_00387A48) == 0) {
        *(s32 *)(arg0 + 0xC) = val;
    } else if (strcmp((const char *)buf, (const char *)D_00376808) == 0) {
        *(s32 *)(arg0 + 0x10) = val;
    } else if (strcmp((const char *)buf, (const char *)D_00387A50) == 0) {
        *(s32 *)(arg0 + 0x4) = val;
    } else if (strcmp((const char *)buf, (const char *)D_00387A58) == 0) {
        *(s32 *)(arg0 + 0x8) = val;
    } else if (strcmp((const char *)buf, (const char *)D_00387A60) == 0) {
        *(s32 *)(arg0 + 0x2C) = val;
    } else if (strcmp((const char *)buf, (const char *)D_00387A68) == 0) {
        *(s32 *)(arg0 + 0x30) = val;
    } else if (strcmp((const char *)buf, (const char *)D_00376818) == 0) {
        *(s32 *)(arg0 + 0x34) = 0;
    } else if (strcmp((const char *)buf, (const char *)D_00376828) == 0) {
        *(s32 *)(arg0 + 0x38) = 0;
    }
}
