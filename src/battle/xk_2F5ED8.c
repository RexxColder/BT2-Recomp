#include "m2c_macros.h"

M2C_UNK func_002EA050(M2C_UNK *);                   /* extern */
extern M2C_UNK D_0037CC58 __attribute__((section(".data")));

void func_002F5ED8(void *arg0) {
    if (arg0 == NULL) {
        func_002EA050(&D_0037CC58);
        return;
    }
    M2C_FIELD(arg0, s16 *, 0x60) = 0;
    M2C_FIELD(arg0, s32 *, 0x64) = 0;
    M2C_FIELD(arg0, s16 *, 0x68) = 0;
    M2C_FIELD(arg0, s16 *, 0x6A) = 0;
}
