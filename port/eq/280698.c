#include "common.h"

extern u8 *D_003876A0;
extern u8 *D_00387AF8;

void func_00280698(s32 arg0, s32 arg1, f32 farg0) {
    u8 *p;

    if (*(s64 *)(D_003876A0 + 0x4D8) & 3) {
        p = D_00387AF8 + arg0 * 0xBC0;
        *(s32 *)(p + 0x600) = arg1;
        *(f32 *)(p + 0x608) = farg0;
    }
}
