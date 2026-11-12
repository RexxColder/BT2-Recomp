#include "m2c_macros.h"

M2C_UNK func_00129C28(void *, void *);              /* extern */
extern M2C_UNK func_001EB270 __attribute__((section(".data")));

// Same as func_001EB8D0 but passes block+0x20 to func_00129C28.
void func_001EB9C0(void *arg0, s32 arg1) {
    void *temp_a0;

    if (arg0 != NULL) {
        if (*M2C_FIELD(arg0, s32 **, 0x28) == &func_001EB270) {
            temp_a0 = M2C_FIELD(arg0, void **, 0x38);
            if ((temp_a0 != NULL) && (M2C_FIELD(temp_a0, u16 *, 0x60) & 1 & 0xFFFF)) {
                func_00129C28(temp_a0 + 0x20, arg1);
            }
        }
    }
}
