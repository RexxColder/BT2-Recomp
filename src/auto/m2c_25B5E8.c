#include "m2c_macros.h"

M2C_UNK Vu0Clip_StoreMtx(s32);                      /* extern */
M2C_UNK Vu0Screen_StoreMtx(s32);                    /* extern */
M2C_UNK func_0025B2D0(s32, M2C_UNK);                /* extern */
M2C_UNK func_0029D8B8(s32, s32);                    /* extern */
M2C_UNK func_0029D938(s32, s32);                    /* extern */
extern s32 gBtlCamView;

void func_0025B5E8(s32 arg0, M2C_UNK arg1) {
    func_0029D8B8(arg0 + 0x40, arg0);
    Vu0Screen_StoreMtx(arg0 + 0x100);
    func_0029D938(arg0 + 0x80, arg0);
    Vu0Clip_StoreMtx(arg0 + 0x140);
    func_0025B2D0(arg0, arg1);
    gBtlCamView = arg0;
}
