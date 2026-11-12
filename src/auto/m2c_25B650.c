#include "m2c_macros.h"

M2C_UNK func_0029C848(s32);                         /* extern */
M2C_UNK func_0029C860(s32);                         /* extern */
extern s32 gBtlCamView;

void func_0025B650(s32 arg0) {
    func_0029C848(arg0 + 0x100);
    func_0029C860(arg0 + 0x140);
    gBtlCamView = arg0;
}
