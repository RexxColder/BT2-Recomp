#include "common.h"

s32 func_003126C8(s32 arg0, s32 arg1);
extern u8 *gScrWarp;

s32 func_00242828(s32 arg0) {
    u8 *temp = 0;

    if (gScrWarp != 0) {
        if ((*(s32 *)(gScrWarp + 0x40) ^ 1) == 0) {
            temp = gScrWarp + 0x40;
        }
        if (temp != 0) {
            func_003126C8(arg0, (s32)(temp + 0x50));
            return *(s32 *)(temp + 0x10);
        }
    }
    return 0;
}
