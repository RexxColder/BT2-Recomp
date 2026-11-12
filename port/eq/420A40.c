#include "common.h"

extern u8 *D_0042FD78 __attribute__((section(".data")));
extern u8 D_00430540[], D_00430550[], D_00430560[], D_00430570[];

s32 func_0026EB70(u8 *arg0);
void func_0026EB78(u8 *arg0, u8 *arg1);
void func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_001018B8();
s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsOutDone(void);
void func_00243A80(s32 arg0, s32 arg1, s32 arg2);
void func_004209F0(void);
void func_0026EBC0(u8 *arg0, u8 *arg1, u8 *arg2);
f32 func_0026F148(u8 *arg0, u8 *arg1);
void func_0026E9E8(u8 *arg0);

#define G (D_0042FD78)
#define GW(o) (*(s32 *)(G + (o)))
#define GF(o) (*(f32 *)(G + (o)))
#define F GW(0xB4)

void func_00420A40(void) {
    u8 sp[16];
    u8 *s0;
    u8 *e;
    s32 i, go;

    if (func_0026EB70(G + 0x40) & 8) {
        func_0026EB78(G + 0x18, D_00430540);
    }
    if (func_0026EB70(G + 0x40) & 0x10) {
        func_00297FE0(2, 0, 0x40, 0x40, 1);
    }
    go = 0;
    if (F & 8) {
        if (func_001018B8() == 5) {
            go = 1;
        } else if (func_001018B8() == 5) {
            go = 1;
        } else if (F & 0x10) {
            go = 1;
        }
    }
    if (go) {
        if (!(F & 1) && GF(0xE4) >= 1.0f) {
            if (GW(0xB8) < 4) {
                GW(0xB8) = GW(0xB8) + 1;
                F = F | 1;
                e = G + GW(0xB8) * 8;
                if (*(s32 *)(e + 0xC0) > 0) {
                    F = F | 2;
                }
                e = G + GW(0xB8) * 8;
                if (*(s32 *)(e + 0xBC) > 0) {
                    F = F | 4;
                }
            } else if (!ColorFade_IsFadingOut()) {
                if (!ColorFade_IsOutDone()) {
                    func_00243A80(0, 0, 0);
                }
            }
        }
        if (!(F & 1)) {
            goto grow;
        }
        /* fade-out of the 0xE4 value */
        GF(0xE4) = GF(0xE4) - 0.075f;
        if (GF(0xE4) <= 0.0f) {
            GF(0xE4) = 0.0f;
            F = F & ~1;
        }
        goto after;
grow:
        if (!(1.0f <= GF(0xE4))) {
            GF(0xE4) = GF(0xE4) + 0.075f;
            if (1.0f <= GF(0xE4)) {
                GF(0xE4) = 1.0f;
                func_004209F0();
                F = F & ~0x10;
            }
        }
after:
        if (F & 2) {
            GF(0xEC) = GF(0xEC) - 0.075f;
            if (GF(0xEC) < 0.0f) {
                GF(0xEC) = 0.0f;
                F = F & ~2;
                e = G + GW(0xB8) * 8;
                GW(0x98) = *(s32 *)(*(u8 **)(G + 0x10) + 0x10) + *(s32 *)(e + 0xC0) * 64;
            }
        } else {
            GF(0xEC) = GF(0xEC) + 0.075f;
            if (1.0f < GF(0xEC)) {
                GF(0xEC) = 1.0f;
            }
        }
        if (F & 4) {
            GF(0xE8) = GF(0xE8) - 0.075f;
            if (GF(0xE8) < 0.0f) {
                GF(0xE8) = 0.0f;
                F = F & ~4;
                e = G + GW(0xB8) * 8;
                GW(0x9C) = *(s32 *)(*(u8 **)(G + 0x10) + 0x10) + *(s32 *)(e + 0xBC) * 64;
            }
        } else {
            GF(0xE8) = GF(0xE8) + 0.075f;
            if (1.0f < GF(0xE8)) {
                GF(0xE8) = 1.0f;
            }
        }
    }
    i = 0;
    if (func_0026EB70(G + 0x40) & 0x200) {
        F = F | 8;
        s0 = G + 0x40;
        func_004209F0();
        F = F & ~0x10;
        func_0026EBC0(s0, D_00430550, sp);
        GF(0xE4) = func_0026F148(s0, sp);
        func_0026EBC0(s0, D_00430560, sp);
        GF(0xEC) = func_0026F148(s0, sp);
        func_0026EBC0(s0, D_00430570, sp);
        GF(0xE8) = func_0026F148(s0, sp);
    }
    for (i = 0; i < 2; i++) {
        func_0026E9E8(G + i * 0x28 + 0x18);
    }
}
