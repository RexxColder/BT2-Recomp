#include "common.h"

void func_0024BEA8(void);
void func_00259288(void);
void func_00298158(s32 arg0);
void func_002AB878(void);
void func_002ABA48(void);
s32 func_002ABB98(void);
void func_002ABE80(void);
void func_002ABF30(void);
s32 func_002AC1F8(void);
s32 func_002AC9A8(void);
s32 func_002ACB20(void);
void func_002ACBD8(void);
extern u8 *D_003876A0;
extern s32 D_00344F30[] __attribute__((section(".data")));
extern s32 D_003B2600[] __attribute__((section(".data")));

s32 func_002AC308(void) {
    s32 s2;
    s32 s0;

    s2 = 0;
    func_002AB878();

    for (;;) {
        *(s64 *)(D_003876A0 + 0x4D8) = *(s64 *)(D_003876A0 + 0x4D8) | 8;
        do {
        } while (func_002ABB98() != 0);
        func_002ABF30();
        func_00298158(1);
        func_002ABE80();
        *(s64 *)(D_003876A0 + 0x4D8) = *(s64 *)(D_003876A0 + 0x4D8) & ~8LL;

        if (func_002AC9A8() == 0) {
            s0 = (func_002ACB20() != 0) ? 1 : 0;
            s2 = (func_002AC1F8() == 0) ? 1 : s2;
            if (s0 != 0) {
                func_002ACBD8();
                if (D_003B2600[0] == 0x14 && D_003B2600[1] == *(s32 *)((u8 *)D_00344F30 + 0x144)) {
                    func_0024BEA8();
                }
                func_00298158(0);
                func_00259288();
                func_00298158(1);
            }
            if (s2 != 1) {
                continue;
            }
        }
        break;
    }

    func_002ABA48();
    return 1;
}
