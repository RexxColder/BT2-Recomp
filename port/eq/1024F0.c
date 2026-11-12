#include "common.h"

extern u8 *D_003876A0;
void func_0028BB60(s32 arg0);
void func_00261D10(void);
void func_001020F0(void);

void func_001024F0(void) {
    u8 *p = D_003876A0;
    s32 v;

    func_0028BB60(*(s32 *)(p + 0x0));
    func_0028BB60(*(s32 *)(p + 0x4));
    *(s32 *)(p + 0x4) = 0;
    func_0028BB60(*(s32 *)(p + 0x24));
    func_0028BB60(*(s32 *)(p + 0xC));
    v = *(s32 *)(p + 0x30);
    if (v != 0) {
        func_0028BB60(v);
    }
    v = *(s32 *)(p + 0x2C);
    if (v != 0) {
        func_0028BB60(v);
        *(s32 *)(p + 0x2C) = 0;
    }
    func_00261D10();
    func_001020F0();
}
