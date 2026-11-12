#include "common.h"

#define LD32(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define LDF(p, off) (*(f32 *)((u8 *)(p) + (off)))
#define PTR(v) ((u8 *)(s32)(v))

void *memcpy(void *dst, const void *src, u32 n);
void *memset(void *dst, s32 c, u32 n);
s32 BtlTaskList_AddTail(s32 arg0, void *arg1, void *arg2);

extern u8 *D_00387894;
extern u8 D_00342950[] __attribute__((section(".data")));

/* 0x001C1048: queues a task entry on the list at *D_00387894. The entry is built in a 0xC0-byte frame: the
 * 64-byte record at arg2, the 16 bytes at arg3, arg0 and arg1 (the list-entry words), zeros, and the float
 * farg0 and arg4 at +0xB0/+0xB4. Returns the list call's result, or 0 when the list pointer is unset or
 * arg0/arg1 is zero. */
s32 func_001C1048(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 farg0) {
    u8 fr[0xC0];
    s32 ret;

    memcpy(fr, PTR(arg2), 0x40);
    memcpy(fr + 0x40, PTR(arg3), 0x10);
    memset(fr + 0x50, 0, 0x70);

    ret = 0;
    if (D_00387894 != NULL) {
        if (arg0 != 0 && arg1 != 0) {
            LD32(fr, 0x50) = arg0;
            LD32(fr, 0x54) = arg1;
            memcpy(fr + 0x60, fr, 0x40);
            memcpy(fr + 0xA0, fr + 0x40, 0x10);
            LDF(fr, 0xB0) = farg0;
            LD32(fr, 0xB4) = arg4;
            ret = BtlTaskList_AddTail(LD32(D_00387894, 0), D_00342950, fr + 0x50);
        }
    }
    return ret;
}
