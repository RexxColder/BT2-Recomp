#include "common.h"

void *EftQuad_Create(void *arg0);
void *memset(void *dst, s32 val, u32 n);
s32 func_00129C28(s32 arg0, s32 arg1);
void func_0018E480(s32 arg0, s32 arg1);
void func_0018E4C8(s32 arg0, s32 arg1);
void func_0018E5E0(s32 arg0, s32 arg1);
void func_0018E1A8(s32 arg0, s32 arg1);
void func_0018E350(s32 arg0, f32 farg0);
void func_0018E2F8(s32 arg0, s32 arg1);
void func_0018E098(s32 arg0);

/* arg4 is a handle word (*arg4 == 0: create the quad), flags in arg5 (bits 0,3,5,6,1 select the draw steps).
 * farg0/farg1 are the float parameters (f12, f13), arg9 the stack argument. */
void func_001503E0(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 *arg4, s32 flags, s32 arg6, s32 arg7,
                   f32 farg0, f32 farg1, s32 arg9) {
    u8 sp[0xA0];
    s32 v0;

    if ((flags & 1) != 0 && *arg4 == 0) {
        *(s32 *)(sp + 0x00) = arg2;
        *(s32 *)(sp + 0x04) = arg3;
        *(s32 *)(sp + 0x08) = (s32)(arg0 + 0x1548);
        memset(sp + 0x10, 0, 0x10);
        memset(sp + 0x20, 0, 0x10);
        *(f32 *)(sp + 0x34) = farg0;
        *(s32 *)(sp + 0x38) = arg6;
        *(f32 *)(sp + 0x30) = farg1;
        func_00129C28((s32)(sp + 0x20), arg9);
        func_00129C28((s32)(sp + 0x10), arg7);
        v0 = (s32)EftQuad_Create(sp);
        *arg4 = v0;
        func_0018E480(v0, arg1[0x15]);
        func_0018E4C8(*arg4, arg1[0x4]);
        func_0018E5E0(*arg4, 1);
    }
    if (*arg4 == 0) {
        return;
    }
    if ((flags & 8) != 0) {
        func_0018E1A8(*arg4, arg7);
    }
    if ((flags & 0x20) != 0) {
        func_0018E350(*arg4, farg1);
    }
    if ((flags & 0x40) != 0) {
        func_0018E2F8(*arg4, arg9);
    }
    if ((flags & 2) != 0) {
        func_0018E098(*arg4);
    }
}
