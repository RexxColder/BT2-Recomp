#include "common.h"

extern s32 D_00354F28 __attribute__((section(".data")));

void *memset(void *, s32, u32);
s32 func_002EFE50(s32 arg0);
s32 func_002F14E0(s32 arg0);
void func_002E93C0(void);
void func_002E93D8(void);
void func_002EFE08(s32 arg0, s32 arg1);
void func_002EFE20(s32 arg0, s32 arg1);
void func_003031A8(s32 arg0, s32 arg1);
void func_003061A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_002F8410(u8 *arg0) {
    u8 sp[0x20];
    s32 s4;
    s32 s7;
    s32 s0;
    s32 s1;
    u32 s5;
    u32 temp_v1;
    u8 *p;
    u8 *s1p;
    u8 *s2p;
    void *o;
    void (*fn1)(void *, s32, s32, void *);
    void (*fn2)(void *, s32, void *);
    void (*fn3)(void *, s32, void *);
    u32 (*fn4)(void *, s32);

    s4 = 0;
    D_00354F28 = func_002EFE50(*(s32 *)(arg0 + 0xC));
    s7 = func_002F14E0(*(s32 *)(arg0 + 4));
    func_002E93C0();
    s5 = *(u32 *)(arg0 + 0x48);
    if (s7 > 0) {
        p = arg0 + 0x18;
        do {
            o = *(void **)p;
            p += 4;
            s0 = s4 * 8;
            s4 += 1;
            fn1 = *(void (**)(void *, s32, s32, void *))((u8 *)*(void **)o + 0x18);
            fn1(o, 0, (s32)(s5 * 2), (void *)(sp + s0));
            temp_v1 = *(u32 *)(sp + 4 + s0) >> 1;
            if (temp_v1 < s5) {
                s5 = temp_v1;
            }
        } while (s4 < s7);
    }

    s4 = 0;
    if (s7 > 0) {
        p = arg0 + 0x18;
        do {
            s0 = s4 * 8;
            s1p = sp + s0;
            s2p = sp + 0x10 + s0;
            func_003061A8((s32)s1p, (s32)(s5 * 2), (s32)s1p, (s32)s2p);
            s4 += 1;
            memset(*(void **)s1p, 0, *(u32 *)(sp + 4 + s0));
            o = *(void **)p;
            fn2 = *(void (**)(void *, s32, void *))((u8 *)*(void **)o + 0x20);
            fn2(o, 1, (void *)s1p);
            o = *(void **)p;
            fn3 = *(void (**)(void *, s32, void *))((u8 *)*(void **)o + 0x1C);
            p += 4;
            fn3(o, 0, (void *)s2p);
        } while (s4 < s7);
    }

    s1 = 0;
    *(s32 *)(arg0 + 0xA8) = *(s32 *)(arg0 + 0xA8) + (s32)s5;
    func_002E93D8();
    if (s7 > 0) {
        s4 = s7;
        p = arg0 + 0x18;
        do {
            o = *(void **)p;
            p += 4;
            fn4 = *(u32 (**)(void *, s32))((u8 *)*(void **)o + 0x24);
            temp_v1 = fn4(o, 1);
            s4 -= 1;
            if ((s32)(temp_v1 >> 1) >= s1) {
                s1 = (s32)(temp_v1 >> 1);
            }
        } while (s4 != 0);
    }
    if (((s1 + func_002EFE50(*(s32 *)(arg0 + 0xC))) - *(s32 *)(arg0 + 0xA8)) <= 0) {
        func_002EFE08(*(s32 *)(arg0 + 0xC), 0);
        func_002EFE20(*(s32 *)(arg0 + 0xC), 0);
        func_003031A8(*(s32 *)(arg0 + 0xC), 1);
        *(u8 *)(arg0 + 1) = 5;
    }
}
