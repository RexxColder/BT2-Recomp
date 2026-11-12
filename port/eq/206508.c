#include "common.h"

s32 func_0025FBE8(void *a0, s64 a1);

void func_00206508(void *arg0) {
    if (func_0025FBE8(*(void **)((u8 *)arg0 + 0x1530), 0x20) != 0) {
        *(s32 *)((u8 *)*(void **)((u8 *)arg0 + 0x1530) + 0xAF0) |= 0x20;
    }
    if (func_0025FBE8(*(void **)((u8 *)arg0 + 0x1530), 0x40) != 0) {
        *(s32 *)((u8 *)*(void **)((u8 *)arg0 + 0x1530) + 0xAF0) &= ~0x20;
    }
    if (func_0025FBE8(*(void **)((u8 *)arg0 + 0x1530), (s64)0x8000 << 28) != 0) {
        *(s32 *)((u8 *)*(void **)((u8 *)arg0 + 0x1530) + 0xAF0) |= 0x40;
    }
    if (func_0025FBE8(*(void **)((u8 *)arg0 + 0x1530), (s64)0x8000 << 29) != 0) {
        *(s32 *)((u8 *)*(void **)((u8 *)arg0 + 0x1530) + 0xAF0) &= ~0x40;
    }
}
