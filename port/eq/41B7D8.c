#include "common.h"

extern u8 *D_0042BB84;
extern u8 *D_003876A4;
extern u8 D_003B0B00[];
extern char D_0042FD38[], D_0042FD48[], D_0042FD60[];
s32 func_0026EB60();
s32 func_0026EB78();
void func_0041B648();
s32 func_00297FE0();
s32 func_0028C4B8();
void func_00243A80();
void func_002493C0();

#define O D_0042BB84
#define OW(off) (*(s32 *)(O + (off)))
#define PADN (*(u32 *)(D_003B0B00 + 0x144))
#define PADH (*(u32 *)(D_003B0B00 + 0x134))
#define PW(off) (*(s32 *)(D_003876A4 + (off)))

s32 func_0041B7D8(s32 *arg0) {
    if (!func_0026EB60(O + 0x38)) {
        return 0;
    }
    if (OW(0xF0) & 4) {
        if (PADN & 0x80) {
            OW(0x114) = 0;
            OW(0xFC) = OW(0xFC) - 1;
            if (OW(0xFC) < 0) {
                OW(0xFC) = 2;
            }
            return func_00297FE0(0, 0, 0x40, 0x40, 1);
        }
        if (PADN & 0x20) {
            OW(0x114) = 0;
            OW(0xFC) = OW(0xFC) + 1;
            if (OW(0xFC) >= 3) {
                OW(0xFC) = 0;
            }
            return func_00297FE0(0, 0, 0x40, 0x40, 1);
        }
        if (PADH & 0x4000) {
            s32 v;
            OW(0x114) = 0;
            if (OW(0xF4) == 1) {
                if (*(s32 *)(D_003B0B00 + 0x284) != 1 || func_0028C4B8(1)) {
                    return func_00297FE0(0, 7, 0x40, 0x40, 1);
                }
                PW(0x18) = PW(0x18) | 0x1000;
                PW(0x18) = PW(0x18) & ~0x2000;
            }
            if (OW(0xFC) == 0) {
                v = 0x1F;
            } else if (OW(0xFC) == 1) {
                v = 0x20;
            } else {
                v = 0x21;
            }
            PW(0x1C) = v;
            OW(0xF0) = OW(0xF0) | 1;
            OW(0xF0) = OW(0xF0) | 2;
            OW(0x100) = 0xF;
            return func_00297FE0(0, 1, 0x40, 0x40, 1);
        }
        if (PADH & 0x1000) {
            OW(0x114) = 0;
            OW(0xF0) = OW(0xF0) & ~4;
            func_0041B648(-5);
            func_00297FE0(0, 2, 0x40, 0x40, 1);
            return func_0026EB78(O + 0x38, D_0042FD38);
        }
        return 0;
    }
    if (PADN & 0x10) {
        OW(0x114) = 0;
        OW(0xF4) = OW(0xF4) - 1;
        if (OW(0xF4) == 1) {
            if (OW(0xF0) & 8) {
                OW(0xF4) = 0;
            }
        }
        OW(0x114) = 0;
        if (OW(0xF4) < 0) {
            OW(0xF4) = 3;
        }
        func_0041B648(0);
        return func_00297FE0(0, 0, 0x40, 0x40, 1);
    }
    if (PADN & 0x40) {
        OW(0x114) = 0;
        OW(0xF4) = OW(0xF4) + 1;
        if (OW(0xF4) == 1) {
            if (OW(0xF0) & 8) {
                OW(0xF4) = 2;
            }
        }
        if (OW(0xF4) >= 4) {
            OW(0xF4) = 0;
        }
        func_0041B648(0);
        return func_00297FE0(0, 0, 0x40, 0x40, 1);
    }
    if (PADH & 0x4000) {
        OW(0x114) = 0;
        if (OW(0xF4) == 3) {
            PW(0x1C) = 0x23;
            OW(0xF0) = OW(0xF0) | 1;
            OW(0xF0) = OW(0xF0) | 2;
            OW(0x100) = 0xF;
            func_00297FE0(0, 1, 0x40, 0x40, 1);
            return func_0026EB78(O + 0x38, D_0042FD48);
        }
        if (OW(0xF4) == 1) {
            if (*(s32 *)(D_003B0B00 + 0x284) != 1 || func_0028C4B8(1)) {
                return func_00297FE0(0, 7, 0x40, 0x40, 1);
            }
        }
        OW(0xF0) = OW(0xF0) | 4;
        func_00297FE0(0, 1, 0x40, 0x40, 1);
        return func_0026EB78(O + 0x38, D_0042FD60);
    }
    if (PADH & 0x1000) {
        OW(0x114) = 0;
        func_00243A80(0, 0, 0);
        *arg0 = 0;
        return func_00297FE0(0, 2, 0x40, 0x40, 1);
    }
    OW(0x114) = OW(0x114) + 1;
    if (OW(0x114) == 0xE10) {
        OW(0xF8) = 7;
        func_002493C0(*(u8 **)(O + 8), 0x36A3, 0x3ABC, 0, OW(0xF8));
        OW(0x114) = 0;
        return (s32)O;
    }
    return OW(0x114);
}
