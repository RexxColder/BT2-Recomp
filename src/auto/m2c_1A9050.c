#include "m2c_macros.h"

s32 func_00126560();                                /* extern */
u8 func_0020AD28(s32);                              /* extern */
extern s32 D_00387840;

s32  func_001A9050(s32 arg0) {
    void *temp_s1;

    temp_s1 = D_00387840 + 0x1090;
    if (func_00126560() != 0) {
        return (u8)(M2C_FIELD(temp_s1, u8 *, 1));
    }
    return (u8)(func_0020AD28(arg0));
}
