#include "common.h"

s32 func_00242188(s32 arg0);
extern u8 *gScrWarp __attribute__((section(".data")));

void func_002422C8(void) {
    if (gScrWarp != NULL) {
        if (*(s32 *)(gScrWarp + 0x40) == 1) {
            func_00242188((s32)(gScrWarp + 0x40));
        }
    }
}
