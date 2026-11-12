#include "m2c_macros.h"

M2C_UNK BtlFacade_PulseCtrl10D(s32);                /* extern */
M2C_UNK EftAura_Command(s32, M2C_UNK);              /* extern */
s32 Gsc_GetInt();                                   /* extern */
M2C_UNK func_001AA220(s32);                         /* extern */
M2C_UNK func_001B56D8(s32, M2C_UNK);                /* extern */
s32 func_002A0010(M2C_UNK);                         /* extern */

s32 func_002A6AA0(s32 arg0) {
    if (arg0 == 0) {
        if (func_002A0010(0x61) != 0) {
            EftAura_Command(Gsc_GetInt(), 7);
        }
        if (func_002A0010(0x6B) != 0) {
            func_001AA220(Gsc_GetInt());
        }
        if (func_002A0010(0x74) != 0) {
            func_001B56D8(Gsc_GetInt(), 1);
        }
        if (func_002A0010(0x54) != 0) {
            BtlFacade_PulseCtrl10D(Gsc_GetInt());
        }
        func_002A0010(0x66);
    }
    return 1;
}
