#include "common.h"

void func_002C7AF8(void *arg0, void *arg1, s32 arg2, s32 arg3);
void func_002C8398(void *arg0, void *arg1);
void func_002C9700(void *arg0, void *arg1);

void func_002C7870(void *arg0, void *arg1, s32 arg2) {
    u8 *s2 = (u8 *)arg0;
    u8 *s1 = s2 + 0x11E0;
    u8 *s5 = s2 + 0xD30;
    u8 *s3;
    u8 *ap = (u8 *)arg1;
    u8 *m;
    u8 *p;
    u8 *elemT;
    s32 a2;
    s32 a3;
    s32 t0;
    s32 t1;
    s32 t2;
    s32 vv;
    s32 a1t;
    s32 vsel;
    s32 neg;
    s32 k;
    s32 sum;
    s32 a2m;
    s32 idx;
    u16 a1v;

    s3 = *(u8 **)(s2 + 0x1FC0);
    func_002C8398(arg1, s2 + 0xD4C);

    if (arg2 != 0) {
        p = s2 + 0x12DC;
        k = 0x3F;
        do {
            k -= 1;
            *(s16 *)p = -1;
            p -= 4;
        } while (k >= 0);
        *(s16 *)(s1 + 2) = -1;
        a3 = *(s32 *)(ap + 0x14);
        t2 = *(s32 *)(ap + 0x18);
    } else {
        a3 = *(s32 *)(ap + 0x14);
        t2 = *(s32 *)(ap + 0x18);
        if ((u32)(t2 - 1) < 2U) {
            u8 *g = *(u8 **)(s3 + 0x164);
            s32 lim = *(s32 *)(g + 0x70);
            a2 = lim + 1;
            t0 = (a3 < lim) ? (a3 + 0x400) : a3;
            if (a2 < t0) {
                do {
                    idx = a2 - (((a2 < 0 ? a2 + 0x3F : a2) >> 6) << 6);
                    *(s16 *)(s1 + idx * 4) = -1;
                    a2 += 1;
                } while (a2 < t0);
            }
        }
    }

    /* 797C: */
    neg = (a3 < 0);
    a1v = *(u16 *)(s5 + 0x38);
    t0 = a3 - (((neg ? a3 + 0x3F : a3) >> 6) << 6);
    t1 = t0 * 4;
    elemT = s1 + t1;
    *(u16 *)elemT = a1v;
    if (arg2 != 0) {
        *(s16 *)(elemT + 2) = 0;
    } else {
        if (a3 == 0 && *(s16 *)(s1 + 2) == -1) {
            *(s16 *)(s1 + 2) = 0;
            goto L7A38;
        }
        a3 = -1;
        a2 = 0;
        vv = t0;
        do {
            a2 += 1;
            a1t = vv + 0x3F;
            vsel = (a1t < 0) ? (vv + 0x7E) : a1t;
            p = s1 + (a1t - ((vsel >> 6) << 6)) * 4;
            if (*(s16 *)p != a3) {
                *(s16 *)(elemT + 2) = (s16)((u16)*(u16 *)p + *(u16 *)(p + 2));
                goto L7A38;
            }
            vv = t0 - a2;
        } while (a2 < 0x40);
    }

L7A38:
    *(u16 *)(s5 + 0x3A) = *(u16 *)(elemT + 2);
    if (t2 != 3) {
        return;
    }
    if (*(s16 *)elemT == 0) {
        return;
    }
    m = *(u8 **)(s3 + 0x164);
    sum = (u16)*(u16 *)elemT + (u16)*(u16 *)(elemT + 2);
    a2m = *(s32 *)(m + 0x70);
    idx = a2m - (((a2m < 0 ? a2m + 0x3F : a2m) >> 6) << 6);
    *(s16 *)(s1 + idx * 4 + 2) = (s16)sum;
    *(s16 *)(m + 0x2E) = (s16)sum;
    func_002C7AF8(arg0, m, a2m, sum);
    func_002C9700(arg0, *(u8 **)(s3 + 0x164));
}
