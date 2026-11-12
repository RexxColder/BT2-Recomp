#include "common.h"

s32 EftWaterDrop_Update(void *arg0);
extern u8 *D_003876A0;
extern u8 *gEftDust;

void EftWaterDrop_UpdateList(u8 **arg0, u8 **arg1) {
    u8 *cur;
    u8 *s1;
    u8 *prev;
    u8 *next;
    s32 ret;

    if (!(*(s64 *)(D_003876A0 + 0x4D8) & 0x100)) {
        s1 = *arg0;
        if (s1 != NULL) {
            do {
                cur = s1;
                ret = EftWaterDrop_Update(cur);
                s1 = *(u8 **)(cur + 0x6C);
                if (ret != 0) {
                    prev = *(u8 **)(cur + 0x68);
                    *(s32 *)(cur + 0x64) = 0;
                    if (prev == NULL) {
                        *arg0 = s1;
                    } else {
                        *(u8 **)(prev + 0x6C) = *(u8 **)(cur + 0x6C);
                    }
                    next = *(u8 **)(cur + 0x6C);
                    prev = *(u8 **)(cur + 0x68);
                    if (next == NULL) {
                        *arg1 = prev;
                    } else {
                        *(u8 **)(next + 0x68) = prev;
                    }
                    *(u8 **)(cur + 0x6C) = NULL;
                    *(u8 **)(cur + 0x68) = NULL;
                    *(s32 *)(gEftDust + 0x2C) = *(s32 *)(gEftDust + 0x2C) - 1;
                }
            } while (s1 != NULL);
        }
    }
}
