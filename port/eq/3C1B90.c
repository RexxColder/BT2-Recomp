#include "common.h"

extern u8 *D_00421C98;
extern u8 *D_003876A4;
extern u8 *D_00387F2C;
extern u8 D_003B0B00[];
extern char D_00422978[];
extern char D_00422988[];
extern char D_00422998[];
extern char D_004229A8[];
s32 func_0026EB60();
s32 func_0026EB78();
void func_003C1A48();
s32 func_00297FE0();
void func_0029C550();
void func_0029C820();
void func_0029C810();
void func_0029C7E0();
void EftShotFx_Update_2494A0();
void func_0024C0F0();
void func_0024C120();
s32 func_001018B8();
void func_002493C0();

#define O D_00421C98
#define OW(off) (*(s32 *)(O + (off)))
#define PADN (*(u32 *)(D_003B0B00 + 0x144))
#define PADH (*(u32 *)(D_003B0B00 + 0x134))

s32 func_003C1B90(s32 *arg0) {
    s32 v;

    if (!func_0026EB60(O + 0x68)) {
        return 0;
    }
    if (OW(0x9A4) > 0) {
        OW(0x9B4) = 0;
        goto tick;
    }
    if (OW(0x124) & 4) {
        if (!(PADH & 0x4000)) {
            goto tick;
        }
        OW(0x9B4) = 0;
        OW(0x124) = OW(0x124) & ~4;
        EftShotFx_Update_2494A0();
        func_003C1A48(O);
        func_0026EB78(O + 0x68, D_00422978);
        func_0024C0F0(0);
        func_00297FE0(0, 1, 0x40, 0x40, 1);
        goto tick;
    }
    if (OW(0x124) & 8) {
        if (func_001018B8() != 5) {
            if (!(PADH & 0x4000)) {
                goto tick;
            }
        }
        OW(0x9B4) = 0;
        if (OW(0x12C) == 13) {
            OW(0x12C) = 14;
            func_002493C0(*(u8 **)(O + 8), 0x33E9, 0x3802, 0, OW(0x12C));
        } else if (OW(0x12C) == 14) {
            OW(0x124) = OW(0x124) & ~8;
            OW(0x9A4) = 2;
            OW(0x9AC) = 0x3C;
            func_0029C550(0);
            func_0029C820(1);
            func_0029C810(0);
            func_0029C7E0(0);
            EftShotFx_Update_2494A0();
        }
        if (!(PADH & 0x4000)) {
            goto tick;
        }
        func_00297FE0(0, 1, 0x40, 0x40, 1);
        goto tick;
    }
    if (PADN & 0x10) {
        OW(0x9B4) = 0;
        OW(0x128) = OW(0x128) - 1;
        if (OW(0x128) < 0) {
            v = 1;
            if (!(*(u32 *)(D_00387F2C + 0xE08) & 1)) {
                v = 2;
            }
            OW(0x128) = v;
        }
        func_003C1A48(0);
        func_00297FE0(0, 0, 0x40, 0x40, 1);
        goto tick;
    }
    if (PADN & 0x40) {
        OW(0x9B4) = 0;
        OW(0x128) = OW(0x128) + 1;
        if (*(u32 *)(D_00387F2C + 0xE08) & 1) {
            v = OW(0x128) < 2;
        } else {
            v = OW(0x128) < 3;
        }
        if (!v) {
            OW(0x128) = 0;
        }
        func_003C1A48(0);
        func_00297FE0(0, 0, 0x40, 0x40, 1);
        goto tick;
    }
    if (PADH & 0x4000) {
        OW(0x9B4) = 0;
        if (OW(0x128) == 2) {
            *(s32 *)(D_003876A4 + 0x4B8) = 2;
            if (*(u32 *)(D_00387F2C + 0xE08) & 1) {
                func_00297FE0(0, 7, 0x40, 0x40, 1);
            } else {
                func_0026EB78(O + 0x68, D_00422988);
                func_0024C120(O + 0x68, 1);
                func_00297FE0(0, 1, 0x40, 0x40, 1);
                OW(0x9A4) = 1;
                func_0029C550(0);
                func_0029C820(1);
                func_0029C810(0);
                func_0029C7E0(0);
                EftShotFx_Update_2494A0();
            }
            goto tick;
        }
        if (OW(0x128) == 0) {
            *(s32 *)(D_003876A4 + 0x1C) = 0x27;
        } else if (OW(0x128) == 1) {
            *(s32 *)(D_003876A4 + 0x1C) = 0x28;
        }
        OW(0x124) = OW(0x124) | 1;
        OW(0x124) = OW(0x124) | 2;
        OW(0x138) = 0xF;
        func_00297FE0(0, 1, 0x40, 0x40, 1);
        goto tick;
    }
    if (PADH & 0x1000) {
        OW(0x9B4) = 0;
        OW(0x124) = OW(0x124) | 2;
        *arg0 = 0;
        func_00297FE0(0, 2, 0x40, 0x40, 1);
        goto tick;
    }
    if (PADH & 0x2000) {
        OW(0x9B4) = 0;
        if (*(s16 *)(D_00387F2C + 0x2802) > 0) {
            if (OW(0x134) == 1) {
                OW(0x134) = 0;
                func_0026EB78(O + 0x68, D_00422998);
            } else {
                OW(0x134) = 1;
                func_0026EB78(O + 0x68, D_004229A8);
            }
            func_00297FE0(0, 1, 0x40, 0x40, 1);
        }
    }
tick:
    OW(0x9B4) = OW(0x9B4) + 1;
    if (OW(0x9B4) >= 0xE10) {
        OW(0x12C) = 4;
        func_002493C0(*(u8 **)(O + 8), 0x33E9, 0x3802, 0, OW(0x12C));
        OW(0x9B4) = 0;
    }
    return (s32)O;
}
