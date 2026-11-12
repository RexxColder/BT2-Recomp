#include "common.h"

extern s32 D_00367400 __attribute__((section(".data")));
extern u8 D_003672E0 __attribute__((section(".data")));
extern u16 D_003673E0 __attribute__((section(".data")));

s32 adxf_SetCmdHstry(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 cnt;
    s32 t;
    s32 rem;
    u8 *rec;
    u16 *arr;
    s32 v;

    cnt = D_00367400;
    t = (cnt < 0) ? cnt + 15 : cnt;
    rem = cnt - (t & -16);
    rec = &D_003672E0 + 16 * rem;
    arr = &D_003673E0;

    if (arg1 == 0) {
        arr[arg0] = (u16)(arr[arg0] + 1);
    }
    rec[0] = (u8)arg0;
    rec[1] = (u8)arg1;
    *(s32 *)(rec + 0xC) = arg4;
    *(s32 *)(rec + 4) = arg2;
    *(s32 *)(rec + 8) = arg3;
    D_00367400 = rem + 1;
    v = arr[arg0];
    *(u16 *)(rec + 2) = (u16)v;
    return v;
}
