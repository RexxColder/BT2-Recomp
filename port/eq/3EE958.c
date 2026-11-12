#include "common.h"

extern u8 *D_00428F4C __attribute__((section(".data")));
extern s32 D_003B0C34 __attribute__((section(".data")));
extern u8 D_0042A128[], D_0042A140[], D_0042A150[], D_0042A160[], D_0042A170[], D_0042A180[], D_00429B10[],
    D_00429AF8[], D_0042A190[];

extern s32 func_003ECEE8();
extern s32 func_001018B8();
extern s32 func_002493C0();
extern s32 func_003EE8D8();
extern s32 func_0026E9E8();
extern s32 func_0026EB70();
extern s32 func_0026EB78();
extern s32 func_0026EB60();
extern s32 func_00297FE0();
extern s32 ColorFade_IsFadingOut();

#define DD (D_00428F4C)
#define W(o) (*(s32 *)(DD + (o)))
#define F(o) (*(f32 *)(DD + (o)))

s32 func_003EE958(void) {
    u8 *D;
    s32 a0;
    s32 s1;
    s32 i;
    s32 state;
    s32 r;
    f32 step = *(f32 *)&(u32){0x3D999999};

    D = DD;
    a0 = W(0x174);
    if (a0 & 0x100) {
        F(0x1F0) = F(0x1F0) - step;
        if (F(0x1F0) < 0.0f) {
            F(0x1F0) = 0.0f;
            func_003ECEE8();
            W(0x174) = W(0x174) & ~0x100;
        }
    } else if (a0 & 0x80) {
        F(0x1F0) = F(0x1F0) + step;
        if (1.0f < F(0x1F0)) {
            F(0x1F0) = 1.0f;
        }
    }
    s1 = 0;
    if (W(0x1A0) != 0) {
        s32 v1 = W(0x17C);
        if (v1 == 0) {
            if (func_001018B8() == 5) {
                if (W(0x180) == 0) {
                    W(0x17C) = 1;
                    W(0x190) = 2;
                    func_002493C0(W(0xC), 0x3711, 0x3B2A, 0, W(0x17C));
                } else {
                    func_003EE8D8();
                    W(0x174) = W(0x174) & ~0x10;
                }
            }
        } else if (v1 == 1) {
            if (func_001018B8() == 5) {
                W(0x17C) = W(0x178) * 2 + 3;
                W(0x190) = 0;
                func_002493C0(W(0xC), 0x3711, 0x3B2A, 0, W(0x17C));
                W(0x174) = W(0x174) & ~0x10;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        func_0026E9E8(DD + s1 + 0x28);
        s1 += 0x28;
    }
    state = W(0x194);
    if (state == 0) {
        return 0;
    }
    if ((u32)(state - 1) >= 0x2E) {
        return 0;
    }
    switch (state) {
    case 1:
        r = W(0x184);
        if (r <= 0) {
            W(0x194) = 0;
            return r;
        }
    call_cat:
        func_0026EB78(DD + 0x78, D_0042A128);
        func_00297FE0(0, 0, 0x40, 0x40, 1);
        goto inc_state;
    case 0x15:
        r = W(0x184);
        if (r <= 0) {
            goto call_cat;
        }
        W(0x194) = 0;
        return r;
    case 2:
        if (!(func_0026EB70(DD + 0x78) & 0x200)) {
            return 0;
        }
        W(0x184) = W(0x184) - 1;
        if (W(0x184) < 0) {
            W(0x184) = 0;
        }
        W(0x10C) = *(s32 *)(*(u8 **)(DD + 0xD4) + 0x10) + 0x40;
        W(0x118) = *(s32 *)(*(u8 **)(DD + 0xD4) + 0x10) + 0x80;
        W(0x188) = 0;
        W(0x18C) = 0;
        goto inc_state;
    case 0x16:
        if (!(func_0026EB70(DD + 0x78) & 0x200)) {
            return 0;
        }
        W(0x184) = W(0x184) + 1;
        if (W(0x184) >= 2) {
            W(0x184) = 1;
        }
        W(0x10C) = *(s32 *)(*(u8 **)(DD + 0xD4) + 0x10) + 0x100;
        W(0x118) = *(s32 *)(*(u8 **)(DD + 0xD4) + 0x10) + 0x140;
        W(0x188) = 0;
        W(0x18C) = 0;
        goto inc_state;
    case 3:
    case 0x17:
        if (!(func_0026EB70(DD + 0x78) & 0x200)) {
            return 0;
        }
        goto clear_state;
    case 0x2E:
    clear_state:
        D = DD;
        W(0x194) = 0;
        return (s32)D;
    case 0x29:
        if (W(0x174) & 4) {
            func_0026EB78(DD + 0x50, D_0042A140);
        } else {
            func_0026EB78(DD + 0x50, D_0042A150);
        }
        func_0026EB78(DD + 0xA0, D_0042A160);
        func_0026EB78(DD + 0x78, D_0042A170);
        W(0x174) = W(0x174) | 0x100;
        goto inc_state;
    case 0x2A:
    case 0x2D:
        if (!(func_0026EB70(DD + 0x78) & 0x200)) {
            return 0;
        }
        goto inc_state;
    case 0x2C:
        if (W(0x174) & 4) {
            func_0026EB78(DD + 0x50, D_0042A180);
        } else {
            func_0026EB78(DD + 0x50, D_00429B10);
        }
        func_0026EB78(DD + 0xA0, D_00429AF8);
        func_0026EB78(DD + 0x78, D_0042A190);
        goto inc_state;
    case 0x2B:
        r = ColorFade_IsFadingOut();
        if (!r && func_0026EB60(DD + 0xA0) && (D_003B0C34 & 0x4000)) {
            s32 k;
            W(0x1A4) = W(0x1A4) + 1;
            k = W(0x1A4);
            if (*(s32 *)(*(u8 **)(DD + 0x1C8) + k * 8) < 0) {
                W(0x1A4) = k - 1;
                W(0x194) = W(0x194) + 1;
            } else {
                u8 *t = *(u8 **)(DD + 0x1C4);
                s32 v = *(s32 *)(t + (*(s32 *)(t + (W(0x188) + W(0x18C)) * 4) + W(0x1A4) * 2) * 4 + 4);
                if (W(0x24) != v) {
                    W(0x174) = W(0x174) | 0x100;
                }
                t = *(u8 **)(DD + 0x1C4);
                v = *(s32 *)(t + (*(s32 *)(t + (W(0x188) + W(0x18C)) * 4) + W(0x1A4) * 2) * 4 + 4);
                W(0x24) = v;
            }
            return func_00297FE0(0, 1, 0x40, 0x40, 1);
        }
        r = ColorFade_IsFadingOut();
        if (r) {
            return r;
        }
        r = func_0026EB60(DD + 0xA0);
        if (!r) {
            return r;
        }
        r = D_003B0C34 & 0x1000;
        if (!r) {
            return r;
        }
        W(0x194) = W(0x194) + 1;
        return func_00297FE0(0, 2, 0x40, 0x40, 1);
    default:
        return (state - 1) * 4;
    }
inc_state:
    W(0x194) = W(0x194) + 1;
    return W(0x194);
}
