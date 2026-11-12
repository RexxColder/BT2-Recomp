#include "m2c_macros.h"

M2C_UNK EftTexSet_Keep32(void *, M2C_UNK, M2C_UNK); /* extern */
extern void *D_003878DC;

void func_001DE2B8(void *arg0) {
    if ((M2C_FIELD(M2C_FIELD(arg0, void **, 0x24), s32 *, 4) != 0) && (M2C_FIELD(D_003878DC, s32 *, 0x21C) != 0)) {
        EftTexSet_Keep32(D_003878DC + 8, 1, 0);
    }
}
