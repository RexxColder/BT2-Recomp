#include "common.h"

extern u8 *gEftBurst;

/* 0x00134720 EftBurst_IsBusy: 1 while the burst exists and its frame counter (+4) is below 150. */
s32 EftBurst_IsBusy(void) {
    if (gEftBurst != NULL && *(s32 *)(gEftBurst + 4) < 0x96) {
        return 1;
    }
    return 0;
}
