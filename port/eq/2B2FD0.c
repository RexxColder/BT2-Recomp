#include "common.h"

void func_002B2D10(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_002B2E48(s32 arg0, s32 arg1, s32 arg2);
s32 func_002B2F98(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002B2FC8(void);

s32 func_002B2FD0(s32 arg0) {
    s32 sp[11];
    s32 temp_s0;
    s32 temp_v0;

    func_002B2D10(arg0, (s32)&sp[0], (s32)&sp[1], (s32)&sp[2], (s32)&sp[3], (s32)&sp[4], (s32)&sp[5]);
    func_002B2E48(arg0, (s32)&sp[6], (s32)&sp[7]);
    temp_s0 = func_002B2F98(arg0, (s32)&sp[8], (s32)&sp[9], (s32)&sp[10]);
    temp_v0 = func_002B2FC8();
    return sp[1] + sp[2] + sp[3] + 0x40 + temp_s0 + (sp[0] + sp[4]) + (sp[6] + 0x40 + (sp[7] + sp[5])) + temp_v0 + 0x800;
}
