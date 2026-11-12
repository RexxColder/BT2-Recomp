#include "common.h"

void EftSteam_Update(s32 arg0);

void EftSteam_SetPaused(s32 arg0, s32 arg1) {
    u8 *temp_a0;

    if (arg0 != 0 && *(s32 *)(*(u8 **)((u8 *)arg0 + 0x28)) == (s32)0x0013A8B8u && /* PS2 address of EftSteam_Update */
        !(*(u8 *)((u8 *)arg0 + 0) & 1)) {
        temp_a0 = *(u8 **)((u8 *)arg0 + 0x38);
        if ((arg1 & 0xFF) != 0) {
            *(s32 *)(temp_a0 + 0xC70) = *(s32 *)(temp_a0 + 0xC70) | 1;
            return;
        }
        *(s32 *)(temp_a0 + 0xC70) = *(s32 *)(temp_a0 + 0xC70) & ~1;
    }
}
