#include "m2c_macros.h"

s32 EftStage_IsDrawOn();                            /* extern */
M2C_UNK func_00128EF0();                            /* extern */
M2C_UNK func_00128F08();                            /* extern */
M2C_UNK func_00128F90(s32);                         /* extern */
M2C_UNK func_00131A18(s32);                         /* extern */
extern s32 gBtlCamView;

void func_00131900(s32 arg0) {
    if (EftStage_IsDrawOn() == 0) {
        return;
    }
    func_00128EF0();
    func_00128F90(gBtlCamView + 0x100);
    func_00131A18(arg0);
    func_00128F08();
}
