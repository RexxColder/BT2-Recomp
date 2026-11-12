#include "common.h"

#define W(p, off) (*(s32 *)((u8 *)(p) + (off)))

void func_00269A40(void *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_0026BB48(u8 *arg0, s32 unused1, s32 arg2, s32 arg3) {
    u8 *s0, *s2, *p, *entry, *a1p;
    void *sp[12];
    s32 a2, a3, s1, k, v;

    s1 = 0;
    s2 = arg0 + 0xFD0;
    W(s2, 0x300) = 0;
    p = s2;
    k = 0xB;
    do {
        k -= 1;
        *(s8 *)(p + 0x20) = -1;
        W(p, 0x00) = 0;
        W(p, 0x04) = 0;
        W(p, 0x08) = 0;
        *(f32 *)(p + 0x0C) = 1.0f;
        p += 0x40;
    } while (k >= 0);

    s0 = *(u8 **)(arg0 + 0x48);
    a2 = arg2;
    a3 = arg3;
    for (;;) {
        func_00269A40(arg0, *(u16 *)(s0 + 0xA), a2, a3);
        a2 = *(u16 *)(s0 + 0xA);
        a3 = -1;
        if (a2 >= 0x47) {
            a1p = *(u8 **)(arg0 + 0x95C);
            if (a1p[0] == a2) {
                a3 = 0;
            } else {
                for (k = 1; k < 0xC; k++) {
                    if (a1p[k] == a2) {
                        a3 = k;
                        break;
                    }
                }
            }
        }
        if (a3 >= 0) {
            entry = s2 + (W(s2, 0x300) << 6);
            *(s8 *)(entry + 0x20) = (s8)a3;
            sp[s1] = entry;
            *(u8 *)(entry + 0x21) = (u8)*(u16 *)(s0 + 0xA);
            *(s8 *)(entry + 0x22) = (s8)s1;
            if (s1 > 0) {
                W(entry, 0x24) = (s32)sp[s1 - 1];
            } else {
                W(entry, 0x24) = 0;
            }
            W(s2, 0x300) = W(s2, 0x300) + 1;
            s1 += 1;
            v = *(u16 *)(s0 + 4);
            if (v != 0) {
                s1 = s1 - v;
                if (s1 < 0) {
                    s1 = 0;
                }
            }
        }
        if (*(u16 *)(s0 + 6) != 0) {
            break;
        }
        s0 += *(s32 *)s0;
    }
}
