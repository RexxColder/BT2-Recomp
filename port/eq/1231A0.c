#include "common.h"

f32 func_00123178(s32 arg0, s32 arg1);
s32 func_002745F8(s32 arg0);
extern f32 D_00384118;
extern u8 *D_003876FC;

void func_001231A0(u8 *arg0, s32 arg1) {
    f32 sp[16];
    s32 *ids;
    u8 *s1;
    s32 s0;
    s32 a3;
    s32 a2;
    s32 k;
    s32 a0;
    f32 f1;

    ids = (s32 *)(arg0 + 0xB9C);
    for (a3 = 0; a3 < 16; a3++) {
        sp[a3] = D_00384118;
        ids[a3] = -1;
    }
    s1 = *(u8 **)(D_003876FC + 0x10);

    s0 = 0;
    if (*(s32 *)(s1 + 8) > 0) {
        do {
            a0 = *(s8 *)(*(u8 **)(s1 + 0x50) + s0);
            if ((a0 < 0) || (func_002745F8(a0) != 0)) {
                f1 = func_00123178(arg1, (s32)(*(u8 **)(s1 + 0x48) + (s0 * 0x10)));
                a3 = 0;
                while (a3 < 16) {
                    if (f1 < sp[a3]) {
                        break;
                    }
                    a3 += 1;
                }
                if (a3 < 16) {
                    a2 = 0xF;
                    if (a3 < 0xF) {
                        for (k = 15; k > a3; k--) {
                            sp[k] = sp[k - 1];
                            ids[k] = ids[k - 1];
                        }
                    }
                    sp[a3] = f1;
                    ids[a3] = s0;
                }
            }
            s0 += 1;
        } while (s0 < *(s32 *)(s1 + 8));
    }
}
