#include "common.h"

extern u8 D_00376808[] __attribute__((section(".data")));
extern u8 D_00376818[] __attribute__((section(".data")));
extern u8 D_00376828[] __attribute__((section(".data")));
extern u8 D_00387A48[] __attribute__((section(".data")));
extern u8 D_00387A50[] __attribute__((section(".data")));
extern u8 D_00387A58[] __attribute__((section(".data")));
extern u8 D_00387A60[] __attribute__((section(".data")));
extern u8 D_00387A68[] __attribute__((section(".data")));

s32 strcmp(void *arg0, void *arg1);

void func_0026C380(u8 *arg0, u8 *arg1) {
    u8 buf[0x50];   /* tamano de locales del original (antes 0x42) */
    s32 a1i = 1;
    s32 a3i = 0;
    u8 byte;
    u8 *v;

    buf[0] = arg1[0];
    if (arg1[0] != 0) {
        do {
            byte = arg1[a1i];
            a1i += 1;
            a3i += 1;
            buf[a3i] = byte;
        } while (byte != 0);
    }
    v = arg1 + a1i;
    buf[0x40] = v[0];
    buf[0x41] = v[1];
    if ((buf[0x40] | (buf[0x41] << 8)) != 0) {
        if (strcmp(buf, D_00387A48) == 0) {
            *(s32 *)(arg0 + 0x0C) = 0;
        } else if (strcmp(buf, D_00376808) == 0) {
            *(s32 *)(arg0 + 0x10) = 0;
        } else if (strcmp(buf, D_00387A50) == 0) {
            *(s32 *)(arg0 + 0x04) = 0;
        } else if (strcmp(buf, D_00387A58) == 0) {
            *(s32 *)(arg0 + 0x08) = 0;
        } else if (strcmp(buf, D_00387A60) == 0) {
            *(s32 *)(arg0 + 0x2C) = 0;
        } else if (strcmp(buf, D_00387A68) == 0) {
            *(s32 *)(arg0 + 0x30) = 0;
        } else if (strcmp(buf, D_00376818) == 0) {
            *(s32 *)(arg0 + 0x34) = 0;
        } else if (strcmp(buf, D_00376828) == 0) {
            *(s32 *)(arg0 + 0x38) = 0;
        }
    }
}
