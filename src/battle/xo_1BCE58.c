#include "m2c_macros.h"

void func_00129C28(void *, void *);              /* extern */

/* Walks the linked list at +0xE8 (next at +0xF0) and calls func_00129C28 on each node. */
void func_001BCE58(void *arg0) {
    void *temp_v0;
    void *var_s0;

    var_s0 = M2C_FIELD(arg0, void **, 0xE8);
    if (var_s0 != NULL) {
        do {
            M2C_FIELD(var_s0, s32 *, 0) = (s32) (M2C_FIELD(var_s0, s32 *, 0) | 1);
            M2C_FIELD(var_s0, u8 *, 5) = (u8) M2C_FIELD(arg0, u8 *, 5);
            func_00129C28(var_s0 + 0x40, arg0 + 0x40);
            func_00129C28(var_s0 + 0x60, arg0 + 0x60);
            temp_v0 = M2C_FIELD(var_s0, void **, 0xF0);
            var_s0 = temp_v0;
        } while (temp_v0 != NULL);
    }
}
