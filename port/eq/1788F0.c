#include "common.h"

void EftTexSet_Keep32(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 *D_00387E94;

void EftSpdLine_UpdateTexture(s32 arg0, s32 arg1) {
    if (*(s32 *)(D_00387E94 + 0x3D40) + *(s32 *)(D_00387E94 + 0x3D44) != 0) {
        EftTexSet_Keep32((s32)(D_00387E94 + 0x3D48), arg0, arg1, (s32)D_00387E94);
        *(s8 *)(D_00387E94 + 0x3F50) = 1;
        return;
    }
    *(s8 *)(D_00387E94 + 0x3F50) = 0;
}
