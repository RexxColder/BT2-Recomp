#include "common.h"

void func_0026BD80(s32 arg0, s32 arg1);
extern u8 D_003B0B00[] __attribute__((section(".data")));

void func_0026C038(u8 *arg0) {
    s32 s1 = *(s32 *)(*(u8 **)arg0 + 0x18);
    s32 a1;

    if ((*(s32 *)(D_003B0B00 + 0x144) & 0x80) || (*(s32 *)(D_003B0B00 + 0x134) & 0x80)) {
        a1 = *(s32 *)(arg0 + 0xC);
        if (a1 != 0) {
            func_0026BD80(s1, a1);
        }
    }
    if ((*(s32 *)(D_003B0B00 + 0x144) & 0x20) || (*(s32 *)(D_003B0B00 + 0x134) & 0x20)) {
        a1 = *(s32 *)(arg0 + 0x10);
        if (a1 != 0) {
            func_0026BD80(s1, a1);
        }
    }
    if ((*(s32 *)(D_003B0B00 + 0x144) & 0x10) || (*(s32 *)(D_003B0B00 + 0x134) & 0x10)) {
        a1 = *(s32 *)(arg0 + 4);
        if (a1 != 0) {
            func_0026BD80(s1, a1);
        }
    }
    if ((*(s32 *)(D_003B0B00 + 0x144) & 0x40) || (*(s32 *)(D_003B0B00 + 0x134) & 0x40)) {
        a1 = *(s32 *)(arg0 + 8);
        if (a1 != 0) {
            func_0026BD80(s1, a1);
        }
    }
    if (*(s32 *)(D_003B0B00 + 0x134) & 0x4000) {
        a1 = *(s32 *)(arg0 + 0x2C);
        if (a1 != 0) {
            func_0026BD80(s1, a1);
        }
    }
    if (*(s32 *)(D_003B0B00 + 0x134) & 0x1000) {
        a1 = *(s32 *)(arg0 + 0x30);
        if (a1 != 0) {
            func_0026BD80(s1, a1);
        }
    }
}
