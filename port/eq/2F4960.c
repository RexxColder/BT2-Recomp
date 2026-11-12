#include "common.h"

#define W(o, off) (*(s32 *)((u8 *)(o) + (off)))
#define RNDW(x) (((x) >= 8388608.0f || (x) <= -8388608.0f) ? (s32)(x) : (s32)(((x) + 8388608.0f) - 8388608.0f))

extern u8 D_0037C808[] __attribute__((section(".data")));
extern s32 D_00354EC8 __attribute__((section(".data")));
extern s32 D_00354EEC __attribute__((section(".data")));
extern s32 D_0034AED8 __attribute__((section(".data")));
extern s32 D_00354F14 __attribute__((section(".data")));
extern f32 D_00354F18 __attribute__((section(".data")));

void func_002EA050(void *a0);
void func_002F47C8(void *a0, s32 *a1, s32 *a2);
void func_002F48F8(void);
s32 func_002F1540(s32 a0);
s32 func_002F14C8(s32 a0);
s32 func_002F14F8(s32 a0);

void func_002F4960(u8 *obj, s32 *out1, s32 *out2) {
    s32 sp[2];
    s32 v;
    s32 saved;
    s32 prod;
    s32 r1540;
    s32 r14c8;
    s32 r14f8;
    u8 mode;
    f32 f;
    f32 r;

    if (obj == NULL || out1 == NULL || out2 == NULL) {
        func_002EA050(D_0037C808);
        return;
    }
    if (D_00354EC8 == 0) {
        func_002F47C8(obj, out1, out2);
        return;
    }
    D_00354F18 = 0.0f;
    mode = obj[1];
    if ((u32)(mode - 3) < 2U) {
        if (*(s8 *)(obj + 0x72) != 0) {
            v = W(obj, 0x9C);
        } else {
            v = (D_0034AED8 - W(obj, 0xA0)) * 0x64 + W(obj, 0x9C);
        }
        *out1 = v;
        func_002F47C8(obj, sp, &sp[1]);
        f = (((f32)sp[0] / (f32)sp[1]) - ((f32)*out1 / (f32)D_00354F14)) * 1000.0f;
        D_00354F18 = f;
        if ((f > 60.0f) || (f < -60.0f)) {
            if (D_00354EEC == 1) {
                saved = D_00354EC8;
                D_00354EC8 = 0;
                func_002F4960(obj, sp, &sp[1]);
                D_00354EC8 = saved;
                func_002F48F8();
            }
            r = ((f32)sp[0] / (f32)sp[1]) * (f32)D_00354F14;
            if (r < 2147483648.0f) {
                W(obj, 0x9C) = RNDW(r);
            } else {
                W(obj, 0x9C) = RNDW(r - 2147483648.0f) | (s32)0x80000000;
            }
            W(obj, 0xA0) = D_0034AED8;
        }
    } else if ((s8)mode != 5) {
        *out1 = 0;
    } else {
        r1540 = func_002F1540(W(obj, 4));
        sp[0] = r1540;
        r14c8 = func_002F14C8(W(obj, 4));
        sp[1] = r14c8;
        r14f8 = func_002F14F8(W(obj, 4));
        prod = r1540 * (16 / r14f8);
        sp[0] = prod;
        r = (((f32)prod / (f32)sp[1]) * (f32)D_00354F14);
        *out1 = RNDW(r);
        *out1 = *out1 + (W(obj, 0x9C) + 1);
    }
    /* the mode-5 and the not-5 branches both continue here */
    *out1 += W(obj, 0x88);
    *out2 = D_00354F14;
}
