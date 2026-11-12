#include "common.h"

s32 func_002E7308(void);
void func_002EA0C8(void *arg0, void *arg1);
s32 func_002E7918(u8 *arg0, u8 *arg1, s32 arg2);
void func_002E7878(u8 *arg0);
s32 func_002E7AB8(u8 *arg0);
void func_003061A8(void *arg0, s32 arg1, void *arg2, void *arg3);
void *memcpy(void *arg0, const void *arg1, u32 arg2);

extern void (*D_003534AC)(void *, s32) __attribute__((section(".data")));
extern u8 D_0037C5B0[] __attribute__((section(".data")));
extern u8 D_0037C5D0[] __attribute__((section(".data")));
extern u8 D_0037C5F0[] __attribute__((section(".data")));
extern u8 D_0037C610[] __attribute__((section(".data")));

void func_002F04B0(u8 *arg0) {
    u8 sp[0x20];
    u8 *s0;
    u8 *s2;
    u8 *data;
    s32 size;
    s32 i;
    s32 s1;
    s32 v;
    s32 temp;

    s0 = *(u8 **)(arg0 + 8);
    s2 = *(u8 **)(arg0 + 4);
    (*(void (**)(void *, s32, s32, void *))(*(u8 **)s0 + 0x18))(s0, 1, 0xC800, sp);

    i = 0;
    size = *(s32 *)(sp + 4);
    if (size > 0) {
        data = *(u8 **)sp;
        if (*(s8 *)data == 0) {
            i = 1;
            while ((i < size) && (*(s8 *)(data + i) == 0)) {
                i += 1;
            }
        }
    }

    if ((((i + (s32)((u32)i >> 31)) >> 1) * 2) == (i - 1)) {
        (*(void (**)(void *, s32, void *))(*(u8 **)s0 + 0x1C))(s0, 1, sp);
        if (func_002E7308() == 0) {
            func_002EA0C8(D_0037C5B0, D_0037C5D0);
        }
        v = 4;
    } else {
        func_003061A8(sp, i, sp + 0x10, sp);
        (*(void (**)(void *, s32, void *))(*(u8 **)s0 + 0x20))(s0, 0, sp + 0x10);
        size = *(s32 *)(sp + 4);
        if (size < 0x10) {
            (*(void (**)(void *, s32, void *))(*(u8 **)s0 + 0x1C))(s0, 1, sp);
            return;
        }
        data = *(u8 **)sp;
        s1 = func_002E7918(s2, data, size);
        if ((s1 == 0) || (size < s1)) {
            (*(void (**)(void *, s32, void *))(*(u8 **)s0 + 0x1C))(s0, 1, sp);
            return;
        }
        if (s1 >= 0) {
            *(s32 *)(arg0 + 0x98) = s1;
        } else if (*(s16 *)(s2 + 0x9A) != 0) {
            s1 = 0;
            func_002E7878(s2);
            *(s32 *)(arg0 + 0x98) = 0;
        } else {
            (*(void (**)(void *, s32, void *))(*(u8 **)s0 + 0x1C))(s0, 1, sp);
            if (func_002E7308() == 0) {
                func_002EA0C8(D_0037C5F0, D_0037C610);
            }
            v = 4;
            goto block_44;
        }

        if (func_002E7AB8(s2) == 4) {
            *(u8 *)(arg0 + 3) = 1;
        }
        if (func_002E7AB8(s2) == 2) {
            size = *(s32 *)(sp + 4);
            data = *(u8 **)sp;
            memcpy(arg0 + 0x58, data, (size < 0x41) ? size : 0x40);
        }
        temp = func_002E7AB8(s2);
        if ((((u32)(temp - 0xA)) < 3U) || (temp == 0x14) || (temp == 0xF)) {
            (*(void (**)(void *, s32, void *))(*(u8 **)s0 + 0x1C))(s0, 1, sp);
        } else {
            func_003061A8(sp, s1, sp, sp + 0x10);
            (*(void (**)(void *, s32, void *))(*(u8 **)s0 + 0x20))(s0, 0, sp);
            (*(void (**)(void *, s32, void *))(*(u8 **)s0 + 0x1C))(s0, 1, sp + 0x10);
        }
        if ((*(s32 *)(s2 + 0xE8) != 0) && (D_003534AC != 0)) {
            D_003534AC(s2, *(s32 *)(s2 + 0x14));
        }
        v = 2;
    }
block_44:
    *(u8 *)(arg0 + 1) = (u8)v;
}
