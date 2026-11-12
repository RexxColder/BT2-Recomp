#include "common.h"

void func_00101438(s32 arg0);
void func_001029C8(void);
s32 func_00102AA0(void);
s32 func_00102C40(void);
s32 func_00102D20(void);
void func_001057F8(void);
void func_002711A0(void);
void func_002711E8(void);
void func_0028B090(void);
void func_0028BDA0(void);
void func_00297978(void);
void func_002A8678(void);
extern u8 *D_003876A0;

void func_00102F30(void) {
    s32 s0;

    s0 = 0;
    func_00101438(*(s32 *)(D_003876A0 + 0xBC) + 0x3E1F);
    do {
        if (*(s64 *)(D_003876A0 + 0x4D8) & 0x8000) {
            func_001029C8();
        }
        func_002711A0();
        func_002A8678();
        func_0028B090();
        func_0028BDA0();
        func_00297978();
        func_001057F8();
        if (func_00102AA0() != 0) {
            if (func_00102C40() != 0) {
                s0 = 1;
            }
        } else {
            s0 = (func_00102D20() != 0) ? 1 : s0;
        }
        func_002711E8();
    } while (s0 == 0);
}
