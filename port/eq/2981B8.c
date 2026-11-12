#include "common.h"

u8 *SndHd_GetVagInfo(u8 *arg0);

void func_002981B8(u8 *arg0, u8 *arg1) {
    u8 *vag;
    u8 *p;
    s32 count;
    s32 i;
    s32 k;

    vag = SndHd_GetVagInfo(arg0 + (*(u32 *)(arg0 + 8) & ~3));
    count = *(s32 *)(vag + 0xC);
    p = vag + 0x14 + count * 4;
    if (count >= 0) {
        k = 0;
        for (i = count + 1; i != 0; i--) {
            p += 6;
            if (arg1 != NULL) {
                if (p[0] & 1) {
                    arg1[k] = 1;
                } else {
                    arg1[k] = 0;
                }
            }
            p += 2;
            k++;
        }
    }
}
