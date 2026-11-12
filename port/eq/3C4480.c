#include "common.h"

extern u8 *D_00421CF4 __attribute__((section(".data")));
extern char D_00423000[] __attribute__((section(".data")));
extern char D_00423020[] __attribute__((section(".data")));
extern char D_00423048[] __attribute__((section(".data")));

void func_298528(u8 *a0);
void *memset(void *arg0, s32 arg1, s32 arg2);
s32 strcmp(const char *a0, const char *a1);
s32 func_003BC798(u8 *a0, s32 a1);
s32 OldPass_DecodeChar(u8 *a0, u8 *a1);
s32 func_24B4F0(s32 a0, s32 a1, u8 *a2);
s32 func_003C2F58(s32 a0);

s32 func_003C4480(void) {
    u8 *g;
    u8 *base;
    u8 sp[0xD0];
    s32 s0;
    s32 s1;
    s32 s2;
    s32 i;
    s32 k;
    s32 t1;
    s32 key;
    s32 cls;
    s32 n;
    s32 n2;
    s32 v;
    s32 a0v;
    s32 hval;
    s32 found;
    s32 w;
    s32 and;
    s32 ret;
    s32 c;

    g = D_00421CF4;
    func_298528(g + 0x640);
    memset(sp, 0, 0x68);

    if (strcmp((const char *)(g + 0x1D4), D_00423000) == 0) {
        return -1;
    }
    if (strcmp((const char *)(g + 0x1D4), D_00423020) == 0) {
        return -1;
    }
    if (strcmp((const char *)(g + 0x1D4), D_00423048) == 0) {
        return -1;
    }

    for (i = 0; i < 36; i++) {
        *(s16 *)(sp + 0x20 + 2 * i) = (s16)(s8)g[0x1D4 + i];
    }

    if (func_003BC798(sp, 1) == 0) {
        /* table lookup on D_00421CF4 + 0x24 (stride 0x1C) */
        t1 = -1;
        a0v = 0;
        n = *(s32 *)(g + 0x20);
        key = *(s16 *)(sp + 0);
        if (n > 0) {
            base = *(u8 **)(g + 0x24);
            for (s0 = 0; s0 < n; s0++) {
                u8 *ent = base + 0x1C * s0;
                if (*(s32 *)ent == key) {
                    cls = (s32)*(s16 *)(sp + 2);
                    if (cls >= 0x51) {
                        cls = 4;
                    } else if (cls >= 0x3D) {
                        cls = 3;
                    } else if (cls >= 0x29) {
                        cls = 2;
                    } else {
                        cls = (cls >= 0x15) ? 1 : 0;
                    }
                    t1 = *(s32 *)(ent + 4);
                    a0v = *(s32 *)(ent + 4 * cls + 8);
                    break;
                }
            }
        }

        if (t1 < 0) {
            s1 = 0;
        } else {
            *(u16 *)(g + 0x65C) = (u16)t1;
            found = 0;
            n2 = *(s32 *)(g + 0x28);
            if (n2 > 0) {
                base = *(u8 **)(g + 0x2C);
                for (s0 = 0; s0 < n2; s0++) {
                    u8 *ent2 = base + 32 * s0;
                    if (*(s32 *)ent2 == a0v) {
                        found = 1;
                        for (k = 0; k < 7; k++) {
                            w = *(s32 *)(ent2 + 4 + 4 * k);
                            if (w >= 0) {
                                *(u16 *)(g + 0x640 + 4 * k) = (u16)*(u16 *)(ent2 + 4 + 4 * k);
                            }
                        }
                        break;
                    }
                }
            }
            (void)found;
            *(u16 *)(g + 0x660) = 1;
            s1 = 1;
        }
    } else {
        /* decode path (L46C8) */
        a0v = 0;
        s0 = 0;
        while (s0 < 0x24) {
            c = (s32)(s8)g[0x1D4 + s0];
            if (a0v == 0) {
                a0v = (c == 0);
                s0++;
            } else {
                s0++;
                if (c != 0) {
                    return 0;
                }
            }
        }

        s1 = OldPass_DecodeChar(sp + 0x70, g + 0x1D4);
        if (s1 > 0) {
            if ((u32)*(u32 *)(sp + 0x90) >= 3) {
                return 0;
            }
            *(u16 *)(g + 0x65C) = *(u16 *)(sp + 0x70);
            for (k = 0; k < 7; k++) {
                *(u16 *)(g + 0x640 + 4 * k) = *(u16 *)(sp + 0x74 + 4 * k);
            }
            *(u16 *)(g + 0x65E) = *(u16 *)(sp + 0x90);
            *(u16 *)(g + 0x660) = 1;
        }
    }

    /* L47A4: fold seven halfwords through func_24B4F0 */
    s2 = 0x640;
    for (s0 = 6; s0 >= 0; s0--) {
        hval = (s32)*(s16 *)(g + s2);
        s2 += 4;
        if (hval != 0) {
            u8 *a2p = *(u8 **)(g + 0x1C);
            and = *(s32 *)(a2p + 48 * hval - 0x30) & 0x41;
            if (and != 0) {
                s1 = 0;
            }
            ret = func_24B4F0(hval - 1, (s32)*(s16 *)(g + 0x65C), a2p);
            if (ret == 0) {
                s1 = 0;
            }
        }
    }

    /* L47FC */
    if (s1 <= 0) {
        return s1;
    }
    if (func_003C2F58((s32)*(s16 *)(g + 0x65C)) == 0) {
        return 0;
    }
    return s1;
}
