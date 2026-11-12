#include "m2c_macros.h"

s32 BtlTask_CreateChildList(s32, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_001E6640();                            /* extern */
extern s32 D_003878EC;

void func_001E7018(s32 arg0) {
    func_001E6640();
    D_003878EC = BtlTask_CreateChildList(arg0, 0x20, 0x2240);
}
