#include "common.h"

s32 func_002EA050(s32 arg0);
void func_002EBB38(s32 arg0);
s32 func_002EA3D0(s32 arg0, s32 arg1);
s32 func_002EB9F8(s32 arg0, s32 arg1);
s32 func_002ECBA8(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2);
s32 func_002EB818(s32 a0, s32 a1, s32 a2, s32 a3);
s32 func_002EC120(s32 a0, s32 a1, s32 a2);
void *memset(void *arg0, s32 arg1, s32 arg2);
s32 strncpy(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_00367410[] __attribute__((section(".data")));
extern u8 D_00367408[] __attribute__((section(".data")));
extern u8 D_0036740C[] __attribute__((section(".data")));
extern u8 D_00367404[] __attribute__((section(".data")));
extern u8 D_00366ED8[] __attribute__((section(".data")));
extern u8 D_00348D5C[] __attribute__((section(".data")));
extern u8 D_00348D58[] __attribute__((section(".data")));
extern u8 D_0037BB30[] __attribute__((section(".rodata")));
extern u8 D_0037BB70[] __attribute__((section(".rodata")));
extern u8 D_0037BBA0[] __attribute__((section(".rodata")));
extern u8 D_0037BBC8[] __attribute__((section(".rodata")));
extern u8 D_0037BBF8[] __attribute__((section(".rodata")));

/* 0x002EAC10: ADX load-request setup. Args: a0 handle, a1 src, a2 aux, a3 flag,
 * t0/t1/t2 values, t3 object, then 9th/10th/11th stack args. */
s32 func_002EAC10(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2, s32 t3,
                  s32 n9, s32 n10, s32 n11) {
    s32 s4 = (s32)D_00367410;
    s32 s6 = (s32)D_00367408;
    s32 s1;
    s32 s0 = t3;
    s32 s3 = n10;
    s32 msg;
    s32 v0;
    s32 buf[6];
    s32 r;

    if (*(s32 *)s4 == 2) {
        func_002EA050((s32)D_0037BB30);
        return -1;
    }
    if (*(s32 *)s6 != 0) {
        func_002EBB38(*(s32 *)s6);
        *(s32 *)s6 = 0;
    }
    s1 = (s32)D_0036740C;
    *(s32 *)s1 = -1;
    *(s32 *)s4 = 1;
    if (n9 != 0) {
        if (n10 > 0) {
            /* AD00 */
            v0 = func_002EA3D0(a0, s0);
            if (v0 < 0) {
                *(s32 *)s4 = 4;
                return v0;
            }
            if (*(s32 *)s1 >= 0) {
                msg = (s32)D_0037BBC8;
                func_002EA050(msg);
                *(s32 *)s4 = 4;
                return -1;
            }
            /* AD28 */
            *(s32 *)s4 = 2;
            *(s32 *)s1 = a0;
            memset((void *)s0, 0, 0x11C);
            *(s32 *)D_00367404 = 0;
            *(s32 *)((s32)D_00366ED8 + a0 * 4) = s0;
            *(s32 *)s0 = 0;
            if (a3 == 0) {
                r = func_002EB9F8(a1, a2);
                *(s32 *)s6 = r;
                if (r == 0) {
                    func_002EA050((s32)D_0037BBF8);
                    *(s32 *)s4 = 4;
                    return -1;
                }
                buf[0] = t0;
                buf[4] = t1;
                buf[5] = t2;
                r = func_002ECBA8(a1, a2, s0 + 0x10, (s32)&buf[0], (s32)&buf[1], (s32)&buf[2], (s32)&buf[3]);
                if (r < 0) {
                    *(s32 *)s4 = 4;
                    return r;
                }
                v0 = buf[1];
                *(s32 *)(s0 + 0x114) = v0;
            } else {
                buf[0] = t0;
                buf[4] = t1;
                buf[5] = t2;
                r = func_002EB818(a3, t0, t1, t2);
                *(s32 *)s6 = r;
                if (r == 0) {
                    func_002EA050((s32)D_0037BBF8);
                    *(s32 *)s4 = 4;
                    return -1;
                }
                strncpy(s0 + 0x10, a3, 0x100);
                *(s32 *)(s0 + 0x114) = t1;
            }
            /* AE10 */
            *(u8 *)(s0 + 0xE) = 0;
            *(u8 *)(s0 + 0xF) = (u8)n11;
            if (s3 < 0) {
                s3 += 0x7FF;
            }
            *(s32 *)(s0 + 0x110) = t0;
            *(s32 *)D_00348D5C = s3 >> 11;
            *(s32 *)D_00348D58 = n9;
            s1 = func_002EC120(*(s32 *)s6, s3 >> 11, n9);
            if (s1 >= 0) {
                *(s32 *)(s0 + 8) = 0;
                return 0;
            }
            func_002EBB38(*(s32 *)s6);
            *(s32 *)s4 = 4;
            return s1;
        }
        msg = (s32)D_0037BBA0;
    } else {
        msg = (s32)D_0037BB70;
    }
    func_002EA050(msg);
    *(s32 *)s4 = 4;
    return -3;
}
