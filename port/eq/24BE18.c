#include "common.h"

/* GUESS arity: the asm passes a0..a3 through to the first two calls and the final tail takes no args */
void func_002711A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_0028B090(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void Dma_AddZbuf(s32 arg0, s32 arg1);
void func_00271A00(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s64 arg5);
void func_002711E8(void);
void func_0028B218(void);

void func_0024BE18(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_002711A0(arg0, arg1, arg2, arg3);
    func_0028B090(arg0, arg1, arg2, arg3);
    Dma_AddZbuf(0xE0, 1);
    func_00271A00(0x700, 0x720, 0x200, 0x1C0, 1, (s64)0xFE00 << 46);
    Dma_AddZbuf(0xE0, 0);
    func_002711E8();
    func_0028B218();
}
