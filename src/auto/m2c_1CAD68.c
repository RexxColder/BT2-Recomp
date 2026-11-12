#include "m2c_macros.h"

M2C_UNK func_00128EF0();                            /* extern */
M2C_UNK func_00128F08();                            /* extern */
M2C_UNK func_00128F90(s32);                         /* extern */
M2C_UNK func_001CA860(s32, M2C_UNK);                /* extern */
extern s32 gBtlCamView;

void func_001CAD68(s32 arg0, M2C_UNK arg1) {
    func_00128EF0();
    func_00128F90(gBtlCamView + 0x100);
    func_001CA860(arg0, arg1);
    func_00128F08();
}
