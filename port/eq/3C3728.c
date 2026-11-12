#include "m2c_macros.h"

void func_29BD28(s32);
void func_26E908(void *);
void func_28BB60(void *);
extern void *D_00421CF4 __attribute__((section(".data")));

void func_003C3728(s32 arg0) {
    s32 i;
    s32 off;

    func_29BD28(arg0);
    i = 2;
    off = 0;
    do {
        i -= 1;
        func_26E908((u8 *)D_00421CF4 + off + 0x38);
        off += 0x28;
    } while (i >= 0);
    func_28BB60(M2C_FIELD(D_00421CF4, void **, 0x30));
    func_28BB60(M2C_FIELD(D_00421CF4, void **, 0x34));
    func_28BB60(M2C_FIELD(D_00421CF4, void **, 4));
    func_28BB60(D_00421CF4);
}
