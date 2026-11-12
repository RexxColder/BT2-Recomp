#include "common.h"

s32 BtlCharApi_ObjTestAttr(s32 arg0, s32 arg1);
s32 func_001E74A0(s32 arg0);
s32 func_0020A960(s32 arg0);
s32 func_0020B3D0(s32 arg0);
void func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
void func_0019F370(s32 arg0, s32 arg1, s32 arg2);
extern u8 *D_003876A0;
extern u8 *D_003878F0;

void func_001E7390(void) {
    s32 sp[4];
    s32 i;
    s32 off;
    s32 s0;
    s32 a;
    s32 b;
    s32 *p;

    i = 0;
    off = 0;
    if (*(s64 *)(D_003876A0 + 0x4D8) & 3) {
        do {
            if (func_001E74A0(i) != 0) {
                if (func_0020A960(i) != 0) {
                    a = BtlCharApi_ObjTestAttr(i, 0x80);
                    s0 = (a != 0);
                    b = BtlCharApi_ObjTestAttr(i, 0x100);
                    if (b != 0) {
                        s0 = 1;
                    }
                    if (s0 != 0) {
                        func_00208DE8(func_0020B3D0(i), (s32)sp, 0x30);
                        p = (s32 *)(D_003878F0 + off);
                        if (!(*p & 3)) {
                            func_0019F370((s32)sp, 0, (s32)D_003878F0);
                            p = (s32 *)(D_003878F0 + off);
                        }
                        *p += 1;
                    }
                } else {
                    *(s32 *)(D_003878F0 + off) = 0;
                }
            }
            i += 1;
            off += 4;
        } while (i < 2);
    }
}
