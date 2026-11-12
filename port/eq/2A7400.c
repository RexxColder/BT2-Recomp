#include "common.h"

#define AT(T, p, off) (*(T *)((u8 *)(p) + (off)))

s32 Gsc_GetCurrentTime(void);
s32 Gsc_GetInt(void);
void func_001017F0(s32 arg0, s32 arg1, s32 arg2);
s32 func_001018B8(void);
void func_001018D0(void);
void func_002615F0(s32 arg0, s32 arg1);
s32 func_002A0010(s32 arg0);
void func_002A3E28(s32 arg0);
s32 func_002A3E38(void);
u8 *func_002A3E48(void);
s32 func_002A3EA8(s32 arg0, s32 arg1);
void func_002A4098(s32 arg0);

extern u8 *D_00387F2C;
extern s32 D_003B0C34 __attribute__((section(".data")));
extern u8 D_003B0F40[] __attribute__((section(".data")));
extern s32 D_003B29BC __attribute__((section(".data")));

s32 func_002A7400(s32 arg0, u8 *arg1) {
    u8 *s1;
    s32 s2;
    s32 a2;
    s32 v0;
    s32 v1;
    s32 t;

    s2 = 0;

    if (arg0 == 1) {
        if (AT(u8, arg1, 0x18) != 0) {
            func_002A4098(AT(s32, arg1, 0));
        }
        if (AT(s32, arg1, 4) >= 0) {
            func_002615F0((u16)AT(s32, arg1, 4), 0);
        }
        func_001018D0();
        return s2;
    }

    if (arg0 == 0) {
        if (func_002A0010(0x73) != 0) {
            func_002A3E28(Gsc_GetInt());
        }
        v0 = func_002A3E38();
        AT(s32, arg1, 8) = -1;
        AT(s32, arg1, 4) = -1;
        AT(s32, arg1, 0) = v0;
        AT(s32, arg1, 0x14) = 0;
        AT(u8, arg1, 0x19) = 0;
        s1 = func_002A3E48();
        D_003B29BC = AT(s32, arg1, 0);
        AT(u8, arg1, 0x18) = (u8)(func_002A0010(0x6E) == 0);
        a2 = AT(s32, s1, 8);
        if (a2 >= 0) {
            AT(s32, arg1, 8) = a2;
            AT(s32, arg1, 0xC) = 0;
            AT(u8, arg1, 0x10) = 0;
            func_001017F0(((AT(s32, D_00387F2C, 0x1008) & 1) ? a2 + 0x13F6 : a2), 0, a2);
        }
        if (AT(s8, s1, 6) >= 0) {
            t = AT(s8, s1, 7);
            if (t >= 0) {
                AT(s32, arg1, 4) = t;
                func_002615F0((u16)AT(s32, arg1, 4), AT(s8, s1, 6));
            }
        }
        if ((AT(s32, D_003B0F40, 0x1600) != -1) && (AT(s32, D_003B0F40, 0x1600) == AT(s8, s1, 4)) &&
            (AT(s32, D_003B0F40, 0x1604) == AT(s8, s1, 3))) {
            AT(u8, arg1, 0x19) = 1;
        }
        return s2;
    }

    if (arg0 == 2) {
        if (AT(s32, arg1, 0x14) != 0) {
            s2 = 1;
        } else {
            v0 = Gsc_GetCurrentTime();
            v1 = AT(u8, arg1, 0x19);
            if ((func_002A3EA8(AT(s32, arg1, 0), (v1 == 0) ? v0 : v0 + 0x25) != 0) &&
                (D_003B0C34 & 0x4000)) {
                AT(s32, arg1, 0x14) = AT(s32, arg1, 0x14) + 1;
            }
        }
        if (AT(s32, arg1, 4) >= 0) {
            if (AT(s32, arg1, 8) >= 0) {
                if (func_001018B8() != 3) {
                    v1 = AT(s32, arg1, 0xC);
                    if (AT(u8, arg1, 0x10) != 0 && v1 >= 0x96) {
                        AT(s32, arg1, 8) = -1;
                        func_002615F0((u16)AT(s32, arg1, 4), 0);
                        AT(s32, arg1, 0xC) = AT(s32, arg1, 0xC) + 0xA;
                    } else {
                        AT(s32, arg1, 0xC) = v1 + 0xA;
                    }
                } else {
                    AT(u8, arg1, 0x10) = 1;
                }
            }
        }
        return s2;
    }

    return 0;
}
