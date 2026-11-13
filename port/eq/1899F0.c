#include "common.h"

void *memset(void *arg0, s32 arg1, s32 arg2);
void Mtx_StoreIdentity(s32 arg0);
void Vu0Screen_StoreMtx(s32 arg0);
s32 func_00126598(s32 arg0);
void func_0018A5A0(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4);
void func_0018A9C0(s64 arg0, s64 arg1, s64 arg2, s64 arg3, s64 arg4, s32 arg5, s64 arg6, s64 arg7);

#include <stdio.h>
#define RB(v) __asm__ volatile("mov %%rbx,%0" : "=r"(v))
#define RB13(v) __asm__ volatile("mov %%r13,%0" : "=r"(v))
#define CHKREG(name, a, b, c, d) do { if ((a) != (b) || (c) != (d)) \
    fprintf(stderr, "1899F0: %s clobbered rbx %llx->%llx r13 %llx->%llx\n", name, (a), (b), (c), (d)); } while (0)

void func_001899F0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0, f32 farg1) {
    u8 sp[0xA0];
    u8 *s0;
    u8 *s1;
    u8 *e;
    unsigned long long rb0, rb1, r130, r131; /* 64 bits también en Windows (long es de 32) */
    s32 s4;
    s32 s5;
    s32 s6;
    s32 s7;
    s32 idx;
    f32 f1;

    s6 = arg3 & 0xFF;
    s7 = arg2 & 0xFF;
    s4 = 0;

    memset(sp, 0, 0x40);
    memset(sp + 0x40, 0, 0x40);
    if ((*(s32 *)(arg0 + 0x1D8) & 0x200) != 0) {
        s4 = 1;
        if (func_00126598(*(s32 *)(arg0 + 0xD0)) == 0) {
            return;
        }
    }

    Mtx_StoreIdentity((s32)(sp + 0x40));
    s0 = (u8 *)*(s32 *)(arg0 + 0x1E0);
    s5 = *(s32 *)arg0 + (*(u8 *)(arg0 + 0x1D4) << 4);
    s1 = arg0 + 4;
    if (s0 == NULL) {
        return;
    }

    do {
        RB(rb0); RB13(r130);
        if (s7 == 0) {
            func_0018A5A0((s32)s0, (s32)(sp + 0x40), (s32)(arg0 + 0x40),
                          *(f32 *)(arg0 + 0x88) * *(f32 *)(arg0 + 0x80),
                          *(f32 *)(arg0 + 0x94), *(f32 *)(arg0 + 0xA0), farg0, farg1);
        }
        RB(rb1); RB13(r131); CHKREG("18A5A0", rb0, rb1, r130, r131);
        f1 = *(f32 *)(s0 + 0xA8);
        idx = *(u8 *)(s0 + 0xBD);
        e = s1 + idx * 16;
        if (f1 < 0.0f && s6 != 0) {
            *(f32 *)(sp + 0x80) = *(f32 *)(e + 0xD0);
            *(f32 *)(sp + 0x84) = *(f32 *)(e + 0xD4);
            *(f32 *)(sp + 0x88) = *(f32 *)(e + 0xD0);
            *(f32 *)(sp + 0x8C) = *(f32 *)(e + 0xDC);
            *(f32 *)(sp + 0x90) = *(f32 *)(e + 0xD8);
            *(f32 *)(sp + 0x94) = *(f32 *)(e + 0xD4);
            *(f32 *)(sp + 0x98) = *(f32 *)(e + 0xD8);
            *(f32 *)(sp + 0x9C) = *(f32 *)(e + 0xDC);
        } else {
            *(f32 *)(sp + 0x80) = *(f32 *)(e + 0xD8);
            *(f32 *)(sp + 0x84) = *(f32 *)(e + 0xD4);
            *(f32 *)(sp + 0x88) = *(f32 *)(e + 0xD8);
            *(f32 *)(sp + 0x8C) = *(f32 *)(e + 0xDC);
            *(f32 *)(sp + 0x90) = *(f32 *)(e + 0xD0);
            *(f32 *)(sp + 0x94) = *(f32 *)(e + 0xD4);
            *(f32 *)(sp + 0x98) = *(f32 *)(e + 0xD0);
            *(f32 *)(sp + 0x9C) = *(f32 *)(e + 0xDC);
        }
        RB(rb0); RB13(r130);
        Vu0Screen_StoreMtx((s32)sp);
        RB(rb1); RB13(r131); CHKREG("StoreMtx", rb0, rb1, r130, r131);
        func_0018A9C0((s32)(s0 + 0x40), (s32)sp, (s32)(sp + 0x80), (s32)(sp + 0x90),
                      (s32)(s0 + 0x20), arg1, s4, s5);
        RB(rb1); RB13(r131); CHKREG("18A9C0", rb0, rb1, r130, r131);
        s0 = (u8 *)*(s32 *)(s0 + 0xC0);
    } while (s0 != NULL);
}
