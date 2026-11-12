#include "common.h"

extern u8 *D_003877B4;
extern s32 D_00341F78 __attribute__((section(".data")));

extern void *memcpy(void *dst, const void *src, u32 n);
extern void *memset(void *dst, s32 c, u32 n);
s32 BtlTaskList_AddTail(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

/* 0x0018B960: sibling of 0x00187648 (same template): spawns a battle task. Copies three 16-byte
 * blocks (arg3, arg4, arg5) into a frame, clears 0x60 bytes after them and fills a task record:
 * arg0, arg1, arg2, the two floats and arg6 (at +0x80..+0x88), then adds it to the list of the
 * global D_003877B4 (its list head at +0x7AF4). Does nothing when D_003877B4 is NULL. */
void func_0018B960(s32 arg0, u8 *arg1, s32 arg2, u8 *arg3, u8 *arg4, u8 *arg5, s32 arg6,
                   f32 farg0, f32 farg1) {
    u64 buf[0x1C];
    u8 *sp = (u8 *)buf;
    u8 *t0p;

    memcpy(sp, arg3, 16);
    memcpy(sp + 0x10, arg4, 16);
    memcpy(sp + 0x20, arg5, 16);
    memset(sp + 0x30, 0, 0x60);

    t0p = D_003877B4;
    if (t0p == NULL) {
        return;
    }

    *(s32 *)(sp + 0x30) = arg0;
    *(s32 *)(sp + 0x34) = (s32)arg1;
    *(s32 *)(sp + 0x38) = arg2;
    memcpy(sp + 0x40, sp, 16);
    memcpy(sp + 0x50, sp + 0x10, 16);
    memcpy(sp + 0x60, sp + 0x20, 16);
    *(f32 *)(sp + 0x80) = farg0;
    *(f32 *)(sp + 0x84) = farg1;
    *(s32 *)(sp + 0x88) = arg6;

    BtlTaskList_AddTail(*(s32 *)(t0p + 0x7AF4), (s32)&D_00341F78, (s32)(sp + 0x30),
                        (s32)*(s64 *)(sp + 0x28), (s32)t0p);
}
