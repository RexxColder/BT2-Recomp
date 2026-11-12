#include "common.h"

s32 func_001EBCC0(s32 arg0, s32 arg1);

void func_001EBD08(s32 arg0, s32 arg1) {
    s32 base;
    s32 i;

    i = func_001EBCC0(arg0, arg1);
    while (i < (s32)(*(s16 *)(arg0 + 6)) - 1) {
        base = *(s32 *)arg0;
        *(s32 *)(base + i * 4) = *(s32 *)(base + i * 4 + 4);
        i++;
    }
    base = *(s32 *)arg0;
    *(s32 *)(base + i * 4) = arg1;
    *(s16 *)(arg0 + 6) = (s16)(*(u16 *)(arg0 + 6) - 1);
}
