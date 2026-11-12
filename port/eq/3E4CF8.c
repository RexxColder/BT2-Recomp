#include "common.h"

extern u8 *D_004279CC;
extern u8 D_003B0B00[];
extern u8 *D_003876A4;
extern char D_00428900[];
extern char D_00428910[];
extern char D_00428920[];
s32 func_0026EB60();
s32 func_0026EB78();
void func_003E4B10();
s32 func_00297FE0();
void func_0029C7E0();
void func_0029C810();
void func_0029C7C0();
void func_0029C550();
void func_0029C820();
void EftShotFx_Update_2494A0();
void func_00243A80();

#define O (D_004279CC)
#define PADN (*(u32 *)(D_003B0B00 + 0x144))
#define PADH (*(u32 *)(D_003B0B00 + 0x134))
#define F(off) (*(s32 *)(O + (off)))

static void fx(void) {
    func_0029C7E0(1);
    func_0029C810(0);
    func_0029C7C0(1);
    func_0029C550(0);
    func_0029C820(1);
    EftShotFx_Update_2494A0();
}

s32 func_003E4CF8(s32 *arg0) {
    s32 v;

    if (!func_0026EB60(O + 0x3C)) {
        v = F(0x11C);
        if (v != 0) {
            return v;
        }
    }
    if (F(0xD0) & 4) {
        if (PADN & 0x80) {
            F(0xDC) = F(0xDC) - 1;
            if (F(0xDC) < 0) {
                F(0xDC) = 1;
            }
            func_003E4B10(0);
            return func_00297FE0(0, 0, 0x40, 0x40, 1);
        }
        if (PADN & 0x20) {
            F(0xDC) = F(0xDC) + 1;
            if (F(0xDC) >= 2) {
                F(0xDC) = 0;
            }
            func_003E4B10(0);
            return func_00297FE0(0, 0, 0x40, 0x40, 1);
        }
        if (PADH & 0x4000) {
            if (F(0xDC) == 0) {
                F(0x110) = 0x10;
                fx();
            } else if (F(0xDC) == 1) {
                F(0x110) = 0xD;
                fx();
            }
            F(0xD0) = F(0xD0) | 4;
            F(0xE8) = 0xF;
            return func_00297FE0(0, 1, 0x40, 0x40, 1);
        }
        if (PADH & 0x1000) {
            F(0xD0) = F(0xD0) & ~4;
            func_003E4B10(0);
            func_00297FE0(0, 2, 0x40, 0x40, 1);
            return func_0026EB78(O + 0x3C, D_00428900);
        }
        return -5;
    } else {
        if (PADN & 0x10) {
            F(0xD4) = F(0xD4) - 1;
            if (F(0xD4) < 0) {
                F(0xD4) = 4;
            }
            func_003E4B10(0);
            return func_00297FE0(0, 0, 0x40, 0x40, 1);
        }
        if (PADN & 0x40) {
            F(0xD4) = F(0xD4) + 1;
            if (F(0xD4) >= 5) {
                F(0xD4) = 0;
            }
            func_003E4B10(0);
            return func_00297FE0(0, 0, 0x40, 0x40, 1);
        }
        if (PADH & 0x4000) {
            s32 sel = F(0xD4);
            s32 val;
            if (sel == 0) {
                F(0xD0) = F(0xD0) | 4;
                func_003E4B10(0);
                func_00297FE0(0, 1, 0x40, 0x40, 1);
                return func_0026EB78(O + 0x3C, D_00428910);
            }
            if (sel == 1) {
                val = 0x31;
            } else if (sel == 2) {
                val = 0x32;
            } else if (sel == 3) {
                val = 0x33;
            } else {
                if (*(u32 *)(D_003876A4 + 0x18) & 1) {
                    F(0x110) = 0x1C;
                    F(0xD0) = F(0xD0) | 8;
                    F(0xD0) = F(0xD0) | 2;
                    fx();
                } else {
                    func_00243A80(0, 0, 0);
                }
                *arg0 = 0;
                return func_00297FE0(0, 2, 0x40, 0x40, 1);
            }
            *(s32 *)(D_003876A4 + 0x1C) = val;
            F(0xD0) = F(0xD0) | 1;
            F(0xD0) = F(0xD0) | 2;
            F(0xE8) = 0xF;
            func_00297FE0(0, 1, 0x40, 0x40, 1);
            return func_0026EB78(O + 0x3C, D_00428920);
        }
        if (PADH & 0x1000) {
            if (*(u32 *)(D_003876A4 + 0x18) & 1) {
                F(0x110) = 0x1C;
                F(0xD0) = F(0xD0) | 8;
                F(0xD0) = F(0xD0) | 2;
                F(0xD0) = F(0xD0) | 0x10;
                fx();
            } else {
                func_00243A80(0, 0, 0);
            }
            *arg0 = 0;
            return func_00297FE0(0, 2, 0x40, 0x40, 1);
        }
        return 0x380000;
    }
}
