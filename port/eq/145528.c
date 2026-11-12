#include "common.h"

void Vu0Screen_StoreMtx(s32 arg0);
void func_00144EE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   s32 arg8, s32 arg9, s32 arg10, s64 arg11);
extern u8 *gEftBound;

void func_00145528(u8 *arg0) {
    s32 sp20[16];
    s32 base;
    u8 *s3;
    u8 *s4;
    s64 *cur;
    s64 v0;
    s64 v1;
    s32 i;

    s4 = gEftBound + 0x10;
    i = 0;
    base = (s32)(arg0 + 0x30);
    s3 = *(u8 **)(gEftBound + 0x218);
    Vu0Screen_StoreMtx((s32)sp20);
    if (*(s16 *)(arg0 + 2) > 0) {
        cur = (s64 *)(arg0 + 0x630);
        v0 = *cur;
        do {
            v1 = cur[1];
            cur += 4;
            i += 1;
            {
                s32 a1 = ((s32)v0 << 6) + base;
                s32 a2 = ((s32)(v0 >> 32) << 6) + base;
                s32 a3 = ((s32)v1 << 6) + base;
                func_00144EE0((s32)sp20, a1, a2, a3, a1 + 0x20, a2 + 0x20, a3 + 0x20, a1 + 0x30,
                              a2 + 0x30, a3 + 0x30, *(s32 *)(s3 + 0x38), *(s64 *)s4);
            }
            {
                s32 a1 = ((s32)v1 << 6) + base;
                s32 a2 = ((s32)(v0 >> 32) << 6) + base;
                s32 a3 = ((s32)(v1 >> 32) << 6) + base;
                func_00144EE0((s32)sp20, a1, a2, a3, a1 + 0x20, a2 + 0x20, a3 + 0x20, a1 + 0x30,
                              a2 + 0x30, a3 + 0x30, *(s32 *)(s3 + 0x38), *(s64 *)s4);
            }
            if (i >= *(s16 *)(arg0 + 2)) {
                break;
            }
            v0 = *cur;
        } while (1);
    }
}
