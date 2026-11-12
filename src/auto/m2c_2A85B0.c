#include "m2c_macros.h"

M2C_UNK Queue_Clear(s32);                           /* extern */
extern s32 D_00387E04;

void func_002A85B0(void) {
    Queue_Clear(D_00387E04 + 0xA0);
}
