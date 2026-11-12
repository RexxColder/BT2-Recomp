#include "common.h"

#define VSLOT(obj, off) (*(void **)((u8 *)*(void **)(obj) + (off)))

s32 func_002E9560(s32 a, s32 b, void *c);
s32 func_002E9F00(s32 a, s32 b, void *c);
void func_003061A8(void *a, s32 b, void *c, void *d);
s32 func_002F0388(s32 a);
void func_002F0450(s32 a);
void func_002F0480(s32 a);
void func_002F0F90(s32 a);
s32 func_002F1330(s32 a);
s32 func_002F1540(s32 a);
void func_002F03E0(s32 a, s32 b);
void func_002F1480(s32 a, s32 b);
void func_002F14A0(s32 a, s32 b);
void func_002F1490(s32 a, s32 b);
void func_002F6838(void *a, s32 b);

void func_002F7A80(void *arg0) {
    u8 sp[0x50];   /* tamano de locales del original (antes 0x48) */
    s32 s2;
    void *s1;
    s32 r;
    s32 s0;
    s32 s6;
    s32 v1;

    s2 = *(s32 *)((u8 *)arg0 + 4);
    s1 = *(void **)((u8 *)arg0 + 0x14);
    if (*(s8 *)((u8 *)arg0 + 0x98) != 0) {
        *(s16 *)(sp + 0x42) = 0;
        ((void (*)(void *, s32, s32, void *))VSLOT(s1, 0x18))(s1, 1, 0x7FFFFFFF, sp);
        ((void (*)(void *, s32, s32, void *))VSLOT(s1, 0x18))(s1, 1, 0x7FFFFFFF, sp + 0x20);
        if (func_002E9F00(*(s32 *)(sp + 0), *(s32 *)(sp + 4), sp + 0x40) != 0) {
            func_002F6838(arg0, 0);
            ((void (*)(void *, s32, void *))VSLOT(s1, 0x1C))(s1, 1, sp + 0x20);
            ((void (*)(void *, s32, void *))VSLOT(s1, 0x1C))(s1, 1, sp);
            return;
        }
        s0 = *(s16 *)(sp + 0x40);
        r = func_002E9560(*(s32 *)(sp + 0) + s0, *(s32 *)(sp + 4) - s0, sp + 0x40);
        v1 = -1;
        if (r != 0) {
            v1 = func_002E9560(*(s32 *)(sp + 0x20), *(s32 *)(sp + 0x24), sp + 0x42);
        }
        s6 = *(s16 *)(sp + 0x42);
        s0 = s0 + *(s16 *)(sp + 0x40);
        if (r != 0) {
            if (v1 != 0) {
                ((void (*)(void *, s32, void *))VSLOT(s1, 0x1C))(s1, 1, sp + 0x20);
                ((void (*)(void *, s32, void *))VSLOT(s1, 0x1C))(s1, 1, sp);
                func_002F6838(arg0, 0);
                return;
            }
            ((void (*)(void *, s32, void *))VSLOT(s1, 0x20))(s1, 0, sp);
            func_003061A8(sp + 0x20, s6, sp + 0x20, sp + 0x30);
            ((void (*)(void *, s32, void *))VSLOT(s1, 0x20))(s1, 0, sp + 0x20);
            ((void (*)(void *, s32, void *))VSLOT(s1, 0x1C))(s1, 1, sp + 0x30);
        } else {
            ((void (*)(void *, s32, void *))VSLOT(s1, 0x1C))(s1, 1, sp + 0x20);
            func_003061A8(sp, s0, sp, sp + 0x10);
            ((void (*)(void *, s32, void *))VSLOT(s1, 0x20))(s1, 0, sp);
            ((void (*)(void *, s32, void *))VSLOT(s1, 0x1C))(s1, 1, sp + 0x10);
        }

        /* block_11 */
        r = func_002F1330(s2);
        *(s32 *)((u8 *)arg0 + 0xA4) = *(s32 *)((u8 *)arg0 + 0xA4) + r;
        func_002F0480(s2);
        func_002F0450(s2);
        func_002F0F90(s2);
        if (func_002F0388(s2) == 2) {
            func_002F03E0(s2, *(s32 *)((u8 *)arg0 + 0x48));
            r = func_002F1540(s2);
            func_002F1480(s2, r);
            func_002F14A0(s2, 0);
            func_002F1490(s2, 0);
        } else {
            func_002F6838(arg0, 0);
        }
    }
}
