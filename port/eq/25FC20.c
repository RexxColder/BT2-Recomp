#include "m2c_macros.h"

s32 BtlObjAnim_GetEventArg(void *arg0, u64 arg1) {
    s32 n = *(s8 *)((u8 *)arg0 + 0xD7E);
    s32 res = 0;
    u8 *pf = (u8 *)arg0 + 0xD88;
    u8 *pv = (u8 *)arg0 + 0xDC8;
    s32 v1;

    if (n > 0) {
        v1 = n;
        do {
            if (*(s64 *)pf & (s64)arg1) {
                res |= *(s32 *)pv;
            }
            pf += 8;
            pv += 4;
            v1 -= 1;
        } while (v1 != 0);
    }
    return res;
}
