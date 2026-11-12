#include "m2c_macros.h"

M2C_UNK *BtlPool_Alloc(s32, M2C_UNK);               /* extern */
s32 BtlPool_GetCurrent();                           /* extern */
M2C_UNK EftTexSet_Load32(M2C_UNK *, s32);           /* extern */
s32 func_00126460(M2C_UNK);                         /* extern */
M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);        /* extern */
extern M2C_UNK *gEftBubble;

void func_0012F2C8(void) {
    M2C_UNK *var_s0;

    var_s0 = gEftBubble;
    if (var_s0 == NULL) {
        var_s0 = BtlPool_Alloc(BtlPool_GetCurrent(), 0x270);
        gEftBubble = var_s0;
        memset(var_s0, 0, 0x270);
        var_s0 = gEftBubble;
    }
    if (*var_s0 == NULL) {
        M2C_FIELD(gEftBubble, M2C_UNK **, 0) = BtlPool_Alloc(BtlPool_GetCurrent(), 0x20);
        memset(M2C_FIELD(gEftBubble, M2C_UNK **, 0), 0, 0x20);
        var_s0 = gEftBubble;
    }
    if (M2C_FIELD(var_s0, s32 *, 4) == 0) {
        M2C_FIELD(gEftBubble, M2C_UNK **, 4) = BtlPool_Alloc(BtlPool_GetCurrent(), 0x2580);
        memset(M2C_FIELD(gEftBubble, M2C_UNK **, 4), 0, 0x2580);
        var_s0 = gEftBubble;
    }
    var_s0 += 26;
    EftTexSet_Load32(var_s0, func_00126460(0xED));
}
