#include "common.h"

s32 func_002E9688(void *a0, void *a1, s16 *a2, void *a3, void *t0, void *t1, void *t2, void *t3, void *s8a, void *s8b);
s32 func_002E9808(void *a0, void *a1, u8 *a2, u8 *a3);
s32 func_002E7D68(void *a0, u8 a1, u8 a2, s32 a3, s16 *t0, s16 *t1, s16 *t2);
s32 func_002E9788(void *a0, void *a1, void *a2);
s32 func_002E9880(void *a0, void *a1, void *a2, void *a3);
void func_002E9A80(void *a0, void *a1, void *a2, void *a3, void *t0, void *t1, void *t2, void *t3, void *s8a);
void func_002E9CE0(void *a0, void *a1, void *a2, void *a3, void *t0, void *t1);
void func_002EA0C8(void *a0, void *a1);
void func_002F8D38(s32 a0, s32 a1, s16 a2);
void func_002F8D60(s32 a0, void *a1, void *a2);
void func_002F8DB0(s32 a0, s16 a1, s16 a2, s16 a3);
extern void (*D_00347BE0)(s32 a0, s16 *a1) __attribute__((section(".data")));
extern u8 D_0037BA10[] __attribute__((section(".data")));
extern u8 D_0037BA30[] __attribute__((section(".data")));

s32 func_002E7580(u8 *arg0, void *arg1, void *arg2) {
    s64 fr[10];
    u8 *sp;

    sp = (u8 *)fr;
    *(s16 *)(arg0 + 2) = 1;
    if (func_002E9688(arg1, arg2, (s16 *)(sp + 0x40), arg0 + 0xC, arg0 + 0xD, arg0 + 0xF, arg0 + 0xE,
                      arg0 + 0x14, arg0 + 0x18, arg0 + 0x10) < 0) {
        return 0;
    }

    if (*(s8 *)(arg0 + 0xC) >= 5) {
        if (*(s32 *)(arg0 + 0xB4) == 0) {
            func_002EA0C8(D_0037BA10, D_0037BA30);
            return -1;
        }
        *(s8 *)(arg0 + 0xD) = 8;
        *(u8 *)(arg0 + 0xF) = (u8)(*(s8 *)(arg0 + 0xE) * 0xC0);
        *(s32 *)(arg0 + 0x10) = 0x60;
        *(s16 *)(arg0 + 0x98) = 0xA;
        *(s16 *)(arg0 + 0x1C) = 0;
        *(s16 *)(arg0 + 0x24) = 0;
        *(s16 *)(arg0 + 0x26) = 0;
        *(s32 *)(arg0 + 0x20) = 0;
        *(s32 *)(arg0 + 0x28) = 0;
        *(s32 *)(arg0 + 0x2C) = 0;
        *(s32 *)(arg0 + 0x30) = 0;
        *(s32 *)(arg0 + 0x34) = 0;
        *(s32 *)(arg0 + 0x88) = 0;
        if (func_002E9808(arg1, arg2, sp + 0x42, sp + 0x43) < 0) {
            return 0;
        }
        *(s16 *)(sp + 0x30) = 0;
        if (func_002E7D68(arg0, sp[0x42], sp[0x43], *(s32 *)(arg0 + 0x18), (s16 *)(sp + 0x32),
                          (s16 *)(sp + 0x34), (s16 *)(sp + 0x36)) < 0) {
            return -1;
        }
        if (D_00347BE0 != NULL) {
            D_00347BE0(*(s32 *)(arg0 + 0xB4), (s16 *)(sp + 0x30));
        }
    } else {
        if (func_002E9808(arg1, arg2, sp + 0x42, sp + 0x43) < 0) {
            return 0;
        }
        if (func_002E7D68(arg0, sp[0x42], sp[0x43], *(s32 *)(arg0 + 0x18), (s16 *)(sp + 0x44),
                          (s16 *)(sp + 0x46), (s16 *)(sp + 0x48)) < 0) {
            return -1;
        }
        func_002F8DB0(*(s32 *)(arg0 + 0x8), *(s16 *)(sp + 0x44), *(s16 *)(sp + 0x46), *(s16 *)(sp + 0x48));
        if (func_002E9788(arg1, arg2, arg0 + 0x1C) < 0) {
            return 0;
        }
        if (func_002E9880(arg1, arg2, sp + 0x10, sp + 0x20) < 0) {
            return 0;
        }
        func_002F8D38(*(s32 *)(arg0 + 0x8), *(s32 *)(arg0 + 0x14), *(s16 *)(arg0 + 0x1C));
        func_002F8D60(*(s32 *)(arg0 + 0x8), sp + 0x10, sp + 0x20);
        func_002E9A80(arg1, arg2, arg0 + 0x20, arg0 + 0x24, arg0 + 0x26, arg0 + 0x28, arg0 + 0x2C,
                      arg0 + 0x30, arg0 + 0x34);
        func_002E9CE0(arg1, arg2, arg0 + 0xCC, arg0 + 0xD0, arg0 + 0xE0, arg0 + 0xE2);
        *(s16 *)(arg0 + 0x98) = 0;
    }

    *(s32 *)(arg0 + 0x50) = *(s8 *)(arg0 + 0xE);
    *(s32 *)(arg0 + 0x54) = *(s8 *)(arg0 + 0xF);
    *(s32 *)(arg0 + 0x58) = *(s32 *)(arg0 + 0x10);
    *(s32 *)(arg0 + 0x5C) = *(s32 *)(arg0 + 0x3C);
    *(s32 *)(arg0 + 0x60) = *(s32 *)(arg0 + 0x40);
    *(s32 *)(arg0 + 0x64) = *(s32 *)(arg0 + 0x44);
    *(s32 *)(arg0 + 0x8C) = 0;
    return *(s16 *)(sp + 0x40);
}
