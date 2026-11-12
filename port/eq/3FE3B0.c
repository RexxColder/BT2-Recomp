#include "m2c_macros.h"

M2C_UNK func_26EA58();                        /* extern */
M2C_UNK func_26EBC0();     /* extern */
M2C_UNK func_26EFC8();       /* extern */
M2C_UNK func_277E70();         /* extern */
extern void *D_0042A58C __attribute__((section(".data")));
extern M2C_UNK D_0042B898 __attribute__((section(".data")));

void func_003FE3B0(void) {
    s32 sp[4];
    void *temp_s0;

    func_277E70(M2C_FIELD(D_0042A58C, s32 *, 0x34), 0, 0x80);
    temp_s0 = D_0042A58C + 0xC;
    func_26EBC0(temp_s0, &D_0042B898, sp);
    func_26EFC8(temp_s0, sp, 0x80);
    func_26EA58(D_0042A58C + 0xC);
}
