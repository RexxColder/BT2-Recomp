#include "m2c_macros.h"

M2C_UNK EftTexSet_Keep32(void *, s32, M2C_UNK);     /* extern */
extern void *gEftBubble;

void EftBubble_SetTexMode(s32 arg0, M2C_UNK arg1) {
    if (M2C_FIELD(gEftBubble, s32 *, 0x10) != 0) {
        EftTexSet_Keep32(gEftBubble + 0x68, arg0, arg1);
    }
}
