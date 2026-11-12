#include "m2c_macros.h"

M2C_UNK func_00129C28();            /* extern */

// Walks a linked list from arg1 (next pointer at +0x40), calling func_00129C28 on each node +0x10 block and the header +0x90 block (inferred from call pattern).
void func_001C52A0(s32 unused0, void **arg1) {
    s32 sp[4];
    void *sp10;
    void **var_s0;
    void **var_s2;
    void *temp_v0;
    void *var_s1;

    var_s0 = arg1;
    func_00129C28(sp, (void **) ((s32) var_s0 + 0x90));
    var_s1 = *var_s0;
    var_s2 = &sp10;
    if (var_s1 != NULL) {
        do {
            var_s0 = var_s1 + 0x10;
            func_00129C28(var_s2, var_s0);
            func_00129C28(var_s0, sp);
            func_00129C28(sp, var_s2);
            M2C_FIELD(var_s1, s8 *, 4) = 0;
            temp_v0 = M2C_FIELD(var_s1, void **, 0x40);
            var_s1 = temp_v0;
        } while (temp_v0 != NULL);
    }
}
