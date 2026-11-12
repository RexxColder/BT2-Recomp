#include "m2c_macros.h"

extern M2C_UNK D_00346BF0 __attribute__((section(".data")));

/* Returns the address of 8-byte entry arg0 in the table at D_00346BF0 */
void *func_002BC158(s32 arg0) {
    return &D_00346BF0 + (arg0 * 2);
}
