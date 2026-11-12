#include "common.h"

s32 func_0025FBE8(s32 arg0, s64 arg1);

void func_002A8EF0(u8 *arg0) {
    if (func_0025FBE8((s32)arg0, 0x02000000) != 0) {
        *(s32 *)(arg0 + 0xAF0) = *(s32 *)(arg0 + 0xAF0) & ~2;
    }
    if (func_0025FBE8((s32)arg0, 0x04000000) != 0) {
        *(s32 *)(arg0 + 0xAF0) = *(s32 *)(arg0 + 0xAF0) | 2;
    }
    if (func_0025FBE8((s32)arg0, 0x20) != 0) {
        *(s32 *)(arg0 + 0xAF0) = *(s32 *)(arg0 + 0xAF0) | 0x20;
    }
    if (func_0025FBE8((s32)arg0, 0x40) != 0) {
        *(s32 *)(arg0 + 0xAF0) = *(s32 *)(arg0 + 0xAF0) & ~0x20;
    }
    if (func_0025FBE8((s32)arg0, (s64)0x8000 << 28) != 0) {
        *(s32 *)(arg0 + 0xAF0) = *(s32 *)(arg0 + 0xAF0) | 0x40;
    }
    if (func_0025FBE8((s32)arg0, (s64)0x8000 << 29) != 0) {
        *(s32 *)(arg0 + 0xAF0) = *(s32 *)(arg0 + 0xAF0) & ~0x40;
    }
}
