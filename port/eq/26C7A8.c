#include "common.h"

void *memcpy(void *dst, const void *src, u32 n);
void func_0026F930(s32 arg0, s32 arg1, s32 arg2);
void func_0026E170(s32 arg0, void *arg1);

/* asm: a1/a2 pass untouched to 26F930 (a2 was dropped: worked only while rdx survived; crashed the trace build) */
void func_0026C7A8(s32 arg0, s32 arg1, s32 arg2) {
    u8 *p;
    u8 *t;
    u8 *a;
    u8 v32[96];
    s32 k;
    s32 flags;
    s32 flag8;
    f32 v33;
    f32 v34;
    f32 v35;
    f32 v36;
    f32 v37;
    f32 v38;
    f32 arr;
    s32 ival;
    s32 sv;
    s32 s_a;
    s32 s_b;

    p = (u8 *)arg0;
    a = (u8 *)arg1;
    if (*(s32 *)p != 0) {
        func_0026F930(*(s32 *)p, arg1, arg2);
    }
    t = (u8 *)*(s32 *)(p + 8);
    if (t == 0) {
        return;
    }
    if ((*(u32 *)(t + 0x44) & 2) == 0) {
        return;
    }

    memcpy(v32, t + 0x48, 96);

    if (a != 0) {
        v33 = *(f32 *)(v32 + 0x30) * *(f32 *)(a + 0x30);
        v34 = *(f32 *)(v32 + 0x34) * *(f32 *)(a + 0x34);
        v35 = *(f32 *)(v32 + 0x38) + *(f32 *)(a + 0x38);
        v36 = *(f32 *)(v32 + 0x3C) * *(f32 *)(a + 0x3C);
        v37 = *(f32 *)(v32 + 0x40) * *(f32 *)(a + 0x40);
        v38 = *(f32 *)(v32 + 0x44) + *(f32 *)(a + 0x44);

        flags = *(s32 *)a;
        if ((flags & 2) != 0) {
            v35 = v35 + *(f32 *)(a + 4);
            v38 = v38 + *(f32 *)(a + 8);
        }
        *(f32 *)(v32 + 0x30) = v33;
        *(f32 *)(v32 + 0x34) = v34;
        *(f32 *)(v32 + 0x38) = v35;
        *(f32 *)(v32 + 0x3C) = v36;
        *(f32 *)(v32 + 0x40) = v37;
        *(f32 *)(v32 + 0x44) = v38;

        flag8 = flags & 8;
        for (k = 0; k < 4; k++) {
            f32 *dst = (f32 *)(v32 + 8 + 0x40 + 4 * k);
            f32 src = *(f32 *)(a + 8 + 0x40 + 4 * k);
            arr = *dst * src;
            *dst = arr;
            if (flag8 != 0) {
                *dst = arr * *(f32 *)(a + 0xC);
            }
            arr = *dst;
            if (1.0f < arr) {
                *dst = 1.0f;
            } else if (arr < 0.0f) {
                *dst = 0.0f;
            }

            s_a = *(s16 *)(a + 8 + 0x50 + 2 * k);
            s_b = *(s16 *)(v32 + 8 + 0x50 + 2 * k);
            sv = s_b + s_a;
            if (sv < 0) {
                ival = 0;
            } else {
                if (sv >= 256) {
                    sv = 255;
                }
                ival = sv;
            }
            *(s16 *)(v32 + 8 + 0x50 + 2 * k) = (s16)ival;
        }
    }

    func_0026E170((s32)(t + 0xA8), v32);
}
