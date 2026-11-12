#include "common.h"

void *func_001272E0(s32 arg0);
s32 func_00127480(void *arg0, s32 arg1);
s32 func_00127828(void *arg0, void *arg1);
s32 EftDet_SpheresVsSpheres(void *arg0, void *arg1);
s32 EftDet_CapsuleVsCapsule(void *arg0, void *arg1);
s32 EftDet_CapsuleVsSpheres(void *arg0, void *arg1);
s32 func_00210000(void *arg0, s32 arg1);
void EftHit_SetTaskFlag(s32 arg0, s32 arg1, void *arg2);
s32 func_0020B158(void);
s32 func_00105A48(void);
void func_0020CD70();
s32 EftStruggle_IsActive(void);
void func_001A7840(void *arg0, void *arg1, void *arg2);
s32 func_00211288(s32 arg0);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_0011BCD0(s32 arg0) {
    u8 *base;
    u8 *a;
    u8 *b;
    s32 i;
    s32 j;
    s32 flag;
    s32 r3;
    s32 a70;
    s32 b70;

    base = func_001272E0(arg0);
    if (*(s32 *)(base + 0x6000) - 1 <= 0) {
        return;
    }
    i = 0;
    a = base;
    do {
        if (func_00127480(a, 2) != 0) {
            j = i;
            b = a;
            if (i < *(s32 *)(base + 0x6000)) {
                do {
                    flag = 0;
                    if (*(s32 *)a != *(s32 *)b && func_00127480(b, 2) != 0) {
                        a70 = *(s32 *)(a + 0x70);
                        b70 = *(s32 *)(b + 0x70);
                        if (a70 == 0) {
                            if (b70 == 0) {
                                if (EftDet_SpheresVsSpheres(a + 0x70, b + 0x70) != 0) {
                                    func_00210000(a + 0x20, 0x34);
                                    flag = 1;
                                }
                            }
                        } else if (a70 == 1) {
                            if (b70 == 1) {
                                if (EftDet_CapsuleVsCapsule(a + 0x70, b + 0x70) != 0) {
                                    func_00210000(a + 0x20, 0x35);
                                    flag = 1;
                                }
                            } else if (b70 == 0) {
                                if (EftDet_CapsuleVsSpheres(a + 0x70, b + 0x70) != 0) {
                                    func_00210000(a + 0x20, 0x34);
                                    flag = 1;
                                }
                            }
                        }

                        r3 = func_00127828(a, b);
                        if (flag != 0) {
                            *(s32 *)(a + 0x138) |= 4;
                            if (r3 & 1) {
                                EftHit_SetTaskFlag(i, 8, a + 0x90);
                            }
                            if (r3 & 2) {
                                EftHit_SetTaskFlag(j, 8, b + 0x90);
                            }
                            if (r3 & 4) {
                                if (func_0020B158() != 0 || func_00105A48() >= 4) {
                                    EftHit_SetTaskFlag(i, 8, a + 0x90);
                                    EftHit_SetTaskFlag(j, 8, b + 0x90);
                                } else {
                                    func_0020CD70(0, 8);
                                    func_0020CD70(1);
                                    if (EftStruggle_IsActive() == 0) {
                                        EftHit_SetTaskFlag(i, 0x100, a + 0x90);
                                        EftHit_SetTaskFlag(j, 0x100, b + 0x90);
                                        func_001A7840(a + 0x90, a, b);
                                    }
                                }
                            }
                            if ((r3 & 3) != 0 && *(s32 *)(a + 0xC) == 0 && *(s32 *)(b + 0xC) == 0) {
                                func_002113C0(func_00211288(0), 0x10, 0x10000000, 1);
                                func_002113C0(func_00211288(1), 0x10, 0x10000000, 1);
                            }
                        }
                    }
                    j += 1;
                    b += 0x180;
                } while (j < *(s32 *)(base + 0x6000));
            }
        }
        i += 1;
        a += 0x180;
    } while (i < *(s32 *)(base + 0x6000) - 1);
}
