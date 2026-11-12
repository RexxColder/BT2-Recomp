#include "common.h"

extern u8 *D_003876A0;

s32 func_00211270(void);
s32 func_0020A658(s32 a0);
u8 *func_00211288(s32 a0);
s32 func_002113C0(u8 *a0, s32 a1, s32 a2, s32 a3);
s32 func_00211310(u8 *a0, s32 a1, s32 a2);
void func_00214A08(u8 *a0);
void func_0020E1D0(u8 *a0);
void func_00260BF8(u8 *a0, s32 a1);
void func_00211688(u8 *a0, s32 a1);
void func_00211FC8(u8 *a0);
void func_002120A8(u8 *a0);
void func_00212170(u8 *a0);
void func_00212240(u8 *a0);
void func_0025F2A0(u8 *a0);
void func_001F9E90(u8 *a0);
void func_0020DE38(u8 *a0);
void func_00260D48(u8 *a0);
void func_002115D0(u8 *a0);
void func_00211908(u8 *a0);
void func_00206F18(u8 *a0);
void func_001FBEB0(u8 *a0);
void func_0020DEA0(void);
u8 *BtlChar_GetPos(u8 *a0);
void func_0020E9A0(u8 *a0, u8 *a1, u8 *a2, s32 a3);
void func_001F70D0(void);
void func_0020E520(void);
void func_00216CF0(u8 *a0);
void func_0020D860(u8 *a0);
void func_00216990(u8 *a0);
void func_00260910(u8 *a0, u8 *a1);
void func_0011D670(u8 *a0, s32 a1);
void func_0011CA40(u8 *a0);
void func_0020D450(u8 *a0);
void func_0026A360(u8 *a0, u8 *a1);
void BtlMove_UpdateAction(u8 *a0);
void func_0023DE40(u8 *a0);
void func_001FB830(u8 *a0);
void func_00206968(u8 *a0);
void func_002119D0(void);
void func_0011A9F0(void);
void func_00201F90(void);
void func_00202078(u8 *a0);
s32 func_0020F9D8();

#define EACH(i, o) for (i = 0; i < func_00211270(); i++) if (!func_0020A658(i)) { o = func_00211288(i);
#define END }
#define CH(o) (*(u8 **)((o) + 0x1530))

#define POS_LOOP(kind) EACH(i, o) p0 = BtlChar_GetPos(o); func_0020E9A0(o, p0, BtlChar_GetPos(o) + 0x10, kind); END

s32 func_001F7860(void) {
    s32 i, s3, s0, v1;
    u8 *o, *p0;

    v1 = (s32)*(s64 *)(D_003876A0 + 0x4D8);
    s3 = 1;
    if (v1 & 0x100) return v1 & 0x100;
    if (v1 & 0x2000) return v1 & 0x2000;
    for (i = 0; i < func_00211270(); i++) {
        if (func_0020A658(i) || (*(s32 *)(CH(func_00211288(i)) + 0xE50) & 0x800)) {
            s3 = 0;
            break;
        }
    }
    EACH(i, o) func_002113C0(o, 9, 2, 1); END
    EACH(i, o) func_00214A08(o); func_0020E1D0(o); END
    EACH(i, o) func_002113C0(o, 9, 2, 0); END
    EACH(i, o)
        func_002113C0(o, 1, 0x100, 0);
        if (func_00211310(o, 2, 2)) {
            func_00260BF8(CH(o), 1);
        } else {
            func_00260BF8(CH(o), 0);
        }
        func_00211688(o, 1);
        func_00211FC8(o);
        func_002120A8(o);
        func_00212170(o);
        func_00212240(o);
        func_0025F2A0(CH(o));
        func_001F9E90(o);
        func_0020DE38(o);
        func_00260D48(CH(o));
        func_002115D0(o);
        func_00211908(o);
        func_00206F18(o);
        func_001FBEB0(o);
    END
    func_0020DEA0();
    POS_LOOP(1);
    func_001F70D0();
    func_0020E520();
    EACH(i, o)
        func_00216CF0(o);
        func_0020D860(o);
        func_00216990(o);
        func_00211688(o, 0);
        func_00260D48(CH(o));
        func_002115D0(o);
    END
    POS_LOOP(2);
    for (i = 0; i < func_00211270(); i++) {
        s0 = 1;
        if (!func_0020A658(i)) {
            o = func_00211288(i);
            func_002113C0(o, 4, -0x990, 0);
            func_002113C0(o, 6, 1, 0);
            func_002113C0(o, 7, 0x1FC00, 0);
            if (func_00211310(o, 3, 0x1000)) {
                func_00260910(CH(o), o + 0x970);
                s0 = 0;
                func_002113C0(o, 3, 0x1000, 0);
            }
            func_0011D670(CH(o), s0);
            func_0011CA40(CH(o));
            func_002115D0(o);
        }
    }
    POS_LOOP(3);
    EACH(i, o) func_0020D450(o); END
    POS_LOOP(4);
    EACH(i, o)
        func_00211688(o, 0);
        func_00260D48(CH(o));
        func_002115D0(o);
    END
    POS_LOOP(5);
    EACH(i, o)
        func_0026A360(CH(o), BtlChar_GetPos(o) + 0x40);
        BtlMove_UpdateAction(CH(o));
        func_0023DE40(o);
        func_00260D48(CH(o));
        func_001FB830(o);
        func_00206968(o);
    END
    func_002119D0();
    if (s3 != 0) {
        func_0011A9F0();
        func_00201F90();
    } else {
        EACH(i, o) func_00202078(o); END
    }
    return func_0020F9D8();
}
