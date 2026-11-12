#include "common.h"

void func_0012F040(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_0012F178(s64 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_0012EF78(void);
extern u8 *D_00387AD8;
extern u8 *D_00387AE4;

void func_0012EB68(void) {
    u8 *p;
    s64 mask = (s64)0xFF000000FFFFFFFFULL;

    func_0012F040(0x158, 0x80, 0x70, 0x31, 0);
    p = D_00387AD8;
    D_00387AD8 += 0x60;
    *(s16 *)(p + 0x40) = 0x7C00;
    *(s16 *)(p + 0x42) = 0x7C80;
    *(s16 *)(p + 0x52) = -0x7C80;
    *(s16 *)(p + 0x50) = -0x7C00;
    *(s64 *)(p + 0x40) = *(s64 *)(p + 0x40) & mask;
    *(s64 *)(p + 0x50) = *(s64 *)(p + 0x50) & mask;
    *(s64 *)(p + 0x20) = 0x116;
    *(s64 *)(p + 0x00) = (s64)0xA0000005ULL;
    *(s64 *)(p + 0x10) = (s64)0x8400000000008001ULL;
    *(s64 *)(p + 0x18) = (s64)0xF4343160ULL;
    *(s64 *)(p + 0x28) = (s64)0x667121C00ULL;
    *(s8 *)(p + 0x33) = -0x80;
    *(f32 *)(p + 0x34) = 1.0f;
    *(s16 *)(p + 0x48) = 0x2000;
    *(s16 *)(p + 0x4A) = 0x1C00;
    *(s8 *)(p + 0x57) = -1;
    *(s8 *)(p + 0x30) = -0x80;
    *(s8 *)(p + 0x31) = -0x80;
    *(s8 *)(p + 0x32) = -0x80;
    *(s16 *)(p + 0x38) = 0;
    *(s16 *)(p + 0x3A) = 0;
    *(s8 *)(p + 0x47) = -1;
    *(u8 **)(*(u8 **)(D_00387AE4 + 4) + 4) = p;
    *(u8 **)(D_00387AE4 + 4) = p;
    func_0012F178(0x150, 0x80, 0, 0);
    func_0012EF78();
}
