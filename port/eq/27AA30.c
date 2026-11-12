#include "common.h"

void func_0027A9E8(s32 arg0);
s32 func_0028BAA8(s32 arg0);
void *memset(void *s, s32 c, u32 n);
extern s32 D_003876A0;
extern s32 D_00387AE8;

void func_0027AA30(s32 arg0) {
    s32 temp_v0;

    if ((*(s64 *)(D_003876A0 + 0x4D8) & 3) != 0) {
        memset((void *)arg0, 0, 0x70);
        *(s32 *)(arg0 + 0) = func_0028BAA8(0x60090);
        temp_v0 = func_0028BAA8(0x60090);
        *(s32 *)(arg0 + 0xC) = temp_v0;
        *(s32 *)(arg0 + 0x8) = *(s32 *)(arg0 + 0);
        *(s32 *)(arg0 + 0x4) = temp_v0;
        D_00387AE8 = arg0;
        func_0027A9E8(arg0);
    }
}
