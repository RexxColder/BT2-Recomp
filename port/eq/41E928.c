#include "common.h"

extern u8 *D_0042FD74 __attribute__((section(".data")));
extern u8 *D_00387F2C __attribute__((section(".data")));
extern u8 *D_003876A4 __attribute__((section(".data")));
extern u8 D_003B0B00[] __attribute__((section(".data")));
extern u8 D_00430130[] __attribute__((section(".data")));
extern u8 D_00430138[] __attribute__((section(".data")));

s32 func_001018B8(void);
void func_0026EB78(u8 *a0, u8 *a1);
s32 func_0026EB70(u8 *a0);
void func_0024C120(void);
void func_002493C0(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0);
void func_00297FE0(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0);
void EftShotFx_Update_2494A0(void);

#define G (D_0042FD74)
#define F(off) (*(s32 *)(G + (off)))
#define PAD34 (*(s32 *)(D_003B0B00 + 0x134))
#define ANIM() func_002493C0(F(0x14), 0x33FA, 0x3813, 0, F(0x13C))

/* Dialog state machine: G = D_0042FD74, F(0x300) = state (0 = idle, jump table over 1..0xD1), F(0x134) flags,
 * F(0x13C) animation index, F(0x324) animation mode. */
void func_0041E928(void) {
    s32 st;
    s32 v;
    s32 m;

    st = F(0x300);
    if (st == 0) {
        return;
    }
    switch (st) {
    case 1:
        F(0x134) = F(0x134) | 0x20;
        F(0x13C) = 0;
        F(0x300) = F(0x300) + 1;
        F(0x324) = 0;
        ANIM();
        return;
    case 2: case 4: case 6: case 8: case 10:
    case 0x36: case 0x38: case 0x3A: case 0x3C: case 0x3E: case 0x40: case 0x42:
    case 0x66: case 0x98: case 0xCA: case 0xCC: case 0xCE: case 0xD0:
    wait5:
        if (func_001018B8() == 5) {
            F(0x300) = F(0x300) + 1;
            return;
        }
    press:
        if (PAD34 & 0x4000) {
            F(0x300) = F(0x300) + 1;
            func_00297FE0(0, 1, 64, 64, 1);
        }
        return;
    case 3:
        F(0x13C) = F(0x13C) + 1;
        F(0x300) = F(0x300) + 1;
        F(0x324) = 0;
        ANIM();
        return;
    case 5: case 7: case 0x37: case 0x39: case 0x3B: case 0x3D:
        m = 1;
        F(0x13C) = F(0x13C) + 1;
        goto next;
    case 9: case 0x3F:
        m = 2;
        F(0x13C) = F(0x13C) + 1;
        goto next;
    case 0xB:
        F(0x300) = F(0x300) + 1;
        func_0026EB78(G + 0x44, D_00430130);
        func_0024C120();
        return;
    case 0xC:
        if (!(func_0026EB70(G + 0x44) & 0x200)) {
            return;
        }
        F(0x300) = 0;
        if (F(0x134) & 0x40) {
            F(0x300) = 0xC9;
        } else if (*(s32 *)(D_00387F2C + 8) & 4) {
            F(0x134) = F(0x134) & ~0x20;
            F(0x13C) = 0x21;
            F(0x324) = 1;
            ANIM();
            *(s32 *)(D_00387F2C + 8) = *(s32 *)(D_00387F2C + 8) & ~4;
        } else {
            F(0x134) = F(0x134) & ~0x20;
            F(0x13C) = 10;
            F(0x324) = 2;
            ANIM();
        }
        return;
    case 0x33:
        F(0x13C) = 15;
        F(0x324) = 2;
        ANIM();
        F(0x300) = F(0x300) + 1;
        F(0x134) = F(0x134) | 0x20;
        goto case34;
    case 0x34:
    case34:
        if (func_001018B8() == 5) {
            v = *(s32 *)(D_003876A4 + 0x18);
            if (v & 0x100) {
                F(0x300) = 0x43;
            } else {
                *(s32 *)(D_003876A4 + 0x18) = v | 0x100;
                F(0x300) = F(0x300) + 1;
            }
        } else if (PAD34 & 0x4000) {
            v = *(s32 *)(D_003876A4 + 0x18);
            m = 0x43;
            if (!(v & 0x100)) {
                *(s32 *)(D_003876A4 + 0x18) = v | 0x100;
                m = F(0x300) + 1;
            }
            F(0x300) = m;
            func_00297FE0(0, 1, 64, 64, 1);
        }
        return;
    case 0x35:
        F(0x13C) = 16;
        m = 1;
        goto next;
    case 0x41:
        m = 3;
        F(0x13C) = F(0x13C) + 1;
        goto next;
    case 0x43:
        F(0x13C) = 0x17;
        m = 1;
    next:
        F(0x300) = F(0x300) + 1;
        F(0x324) = m;
        ANIM();
        return;
    case 0x44:
        if (func_001018B8() == 5) {
            F(0x300) = F(0x300) + 1;
            return;
        }
        if (PAD34 & 0x4000) {
            F(0x300) = F(0x300) + 1;
            func_00297FE0(0, 1, 64, 64, 1);
            F(0x13C) = -1;
            EftShotFx_Update_2494A0();
        }
        return;
    case 0x45:
        func_0026EB78(G + 0x44, D_00430138);
        F(0x300) = F(0x300) + 1;
        return;
    case 0x46:
        if (func_0026EB70(G + 0x44) & 0x200) {
            F(0x300) = 0;
            F(0x134) = F(0x134) | 0x10;
            F(0x134) = F(0x134) & ~0x20;
        }
        return;
    case 0x65:
        F(0x13C) = 28;
        F(0x324) = 1;
        ANIM();
        F(0x300) = F(0x300) + 1;
        F(0x134) = F(0x134) | 0x20;
        goto wait5;
    case 0x67:
        F(0x13C) = 29;
        F(0x324) = 1;
        ANIM();
        F(0x300) = 0;
        F(0x134) = F(0x134) & ~0x20;
        return;
    case 0x97:
        F(0x300) = F(0x300) + 1;
        F(0x134) = F(0x134) | 0x20;
        goto wait5;
    case 0x99:
        F(0x134) = F(0x134) | 1;
        F(0x134) = F(0x134) | 2;
        F(0x2F8) = 15;
        F(0x300) = 0;
        return;
    case 0xC9:
        F(0x13C) = 34;
        F(0x324) = 2;
        ANIM();
        F(0x300) = F(0x300) + 1;
        return;
    case 0xCB: case 0xCF:
        F(0x13C) = F(0x13C) + 1;
        ANIM();
        F(0x300) = F(0x300) + 1;
        return;
    case 0xCD:
        F(0x13C) = F(0x13C) + 1;
        F(0x324) = 3;
        ANIM();
        F(0x300) = F(0x300) + 1;
        return;
    case 0xD1:
        F(0x300) = 0;
        F(0x134) = F(0x134) & ~0x20;
        F(0x13C) = 10;
        F(0x324) = 2;
        ANIM();
        return;
    default:
        return;
    }
}
