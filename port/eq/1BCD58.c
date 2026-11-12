#include "m2c_macros.h"

extern u8 *gEftPtcl4Mgr;

void func_001BCD58(void *arg0) {
    u8 *a = (u8 *)arg0;
    u8 *p = *(u8 **)(a + 0xE8);
    u8 *next;

    if (p != NULL) {
        do {
            *(s32 *)p = 0;
            *(s32 *)(gEftPtcl4Mgr + 8) = *(s32 *)(gEftPtcl4Mgr + 8) - 1;
            next = *(u8 **)(p + 0xF0);
            p = next;
        } while (p != NULL);
    }
    *(s32 *)(a + 0xF4) = 0;
    *(u8 **)(a + 0xE8) = NULL;
    *(s32 *)(a + 0xEC) = 0;
    *(s32 *)(a + 0xF0) = 0;
}
