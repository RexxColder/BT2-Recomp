#include "common.h"

void func_001BCD58(u8 *arg0);
extern u8 *gEftPtcl4Mgr;

void func_001BCDE8(u8 *arg0) {
    u8 *s0 = *(u8 **)arg0;

    if (s0 != NULL) {
        do {
            if (*(s32 *)(s0 + 0xE8) != 0) {
                func_001BCD58(s0);
            }
            *(s32 *)s0 = 0;
            *(s32 *)(gEftPtcl4Mgr + 8) -= 1;
            s0 = *(u8 **)(s0 + 0xE0);
        } while (s0 != NULL);
    }
    *(s32 *)(arg0 + 4) = 0;
    *(s32 *)arg0 = 0;
}
