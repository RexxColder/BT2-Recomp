#include "common.h"

extern void *memset(void *dst, s32 c, u32 n);
void sceVu0Normalize(s32 arg0, s32 arg1);
s32 BtlTaskList_AddTail(s32 arg0, s32 arg1, s32 arg2);
s32 func_00312650(s32 arg0, s32 arg1, s32 arg2);
extern u8 *D_00387830;
extern u8 D_00342560[];

/* 0x001A6028: builds a 0x30-byte record on the stack: vec4 copied from arg0 (sp+0..0xC), arg1 at +0x20, arg2 at +0x24,
 * 14 at +0x28, 1 at +0x2C. func_00312650(sp+0x10, arg3, arg4) makes a vec4 there, which is normalized in place,
 * then the record is added to the task list at D_00387830+0x74C. Returns 1, or 0 when D_00387830 is null. */
s32 func_001A6028(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 sp[0x30];
    f32 *src;
    f32 *dst;

    memset(sp, 0, 0x30);
    if (D_00387830 == 0) {
        return 0;
    }
    src = (f32 *)arg0;
    dst = (f32 *)sp;
    dst[3] = src[3];
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    *(s32 *)(sp + 0x20) = arg1;
    *(s32 *)(sp + 0x24) = arg2;
    *(s32 *)(sp + 0x28) = 0xE;
    *(s32 *)(sp + 0x2C) = 1;
    func_00312650((s32)(sp + 0x10), arg3, arg4);
    sceVu0Normalize((s32)(sp + 0x10), (s32)(sp + 0x10));
    BtlTaskList_AddTail(*(s32 *)(D_00387830 + 0x74C), (s32)D_00342560, (s32)sp);
    return 1;
}
