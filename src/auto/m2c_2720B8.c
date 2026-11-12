#include "m2c_macros.h"

M2C_UNK func_00272888();                            /* extern */
M2C_UNK func_00277E08();                            /* extern */
extern s32 gBtlStage;

void func_002720B8(void) {
    gBtlStage = 0;
    func_00277E08();
    func_00272888();
}
