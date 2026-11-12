#include "common.h"

void func_00129FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void Vec4_Set(s32 arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void func_00129C28(s32 arg0, s32 arg1);
s32 func_00181040(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

/* Builds two sets of eight transformed points (the rows at arg0 and arg1 plus the two 16-byte rows
 * offset by +16/+32 and +48) from projected corner data, then submits both sets through func_00181040
 * and returns its result. */
s32 func_00180D98(s32 a1, s32 a2, u8 a3, u8 a4, u8 a5, u8 a6, u8 a7, u8 a8,
                  u8 a9, u8 a10, s32 a11, s32 a12, s32 a13) {
    u8 sp[0x270];
    s32 v40 = a1;
    s32 v41 = a2;
    s32 v43 = a1 + 16;
    s32 v20 = a1 + 32;
    s32 v21 = a2 + 16;
    s32 v22 = a2 + 32;
    s32 v19;
    s32 s33 = (s32)(sp + 0x1B0);
    s32 s34 = (s32)(sp + 0x1C0);

    func_00129FE0((s32)(sp + 0x1D0), a11, a1, 4);
    v19 = (*(s32 *)(sp + 0x1D8) + *(s32 *)(sp + 0x208)
           + (*(s32 *)(sp + 0x1F8) + *(s32 *)(sp + 0x1E8))) >> 10;

    Vec4_Set(s33, (f32)a3, (f32)a4, (f32)a5, (f32)a6);
    Vec4_Set(s34, (f32)a7, (f32)a8, (f32)a9, (f32)a10);

    func_00129C28((s32)sp, a1);
    func_00129C28((s32)(sp + 0x10), v43);
    func_00129C28((s32)(sp + 0x20), v20);
    func_00129C28((s32)(sp + 0x90), a2);
    func_00129C28((s32)(sp + 0xA0), v21);
    func_00129C28((s32)(sp + 0xB0), v22);
    func_00129C28((s32)(sp + 0x120), s33);
    func_00129C28((s32)(sp + 0x130), s33);
    func_00129C28((s32)(sp + 0x140), s34);
    func_00181040((s32)sp, a11, a13, a12, v19, 0);

    func_00129C28((s32)sp, v43);
    func_00129C28((s32)(sp + 0x10), v20);
    func_00129C28((s32)(sp + 0x20), a1 + 48);
    func_00129C28((s32)(sp + 0x90), v21);
    func_00129C28((s32)(sp + 0xA0), v22);
    func_00129C28((s32)(sp + 0xB0), a2 + 48);
    func_00129C28((s32)(sp + 0x120), s33);
    func_00129C28((s32)(sp + 0x130), s34);
    func_00129C28((s32)(sp + 0x140), s34);
    return func_00181040((s32)sp, a11, a13, a12, v19, 0);
}
