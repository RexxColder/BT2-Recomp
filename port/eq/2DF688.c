#include "common.h"

s32 func_003061A8(u8 *a0, s32 a1, u8 *a2, u8 *a3);
void func_002DFBC8(u8 *obj);

/* 0x002DF688: (self, stream) serializes the field at self+0x38C through the stream's vtable. */
s32 func_002DF688(u8 *self, u8 *stream) {
    u8 sp[16];
    u8 *field = self + 0x38C;
    s32 v;
    s32 base;

    ((void (*)(u8 *, s32, s32, u8 *))(*(u8 **)(*(u8 **)stream + 0x18)))(stream, 1, 0x7FFFFFFF, field);
    v = *(s32 *)field;
    base = v & -4;
    func_003061A8(field, (base + (((v - base) << 3) >> 3) + 4) - v, field, sp);
    ((void (*)(u8 *, s32, u8 *))(*(u8 **)(*(u8 **)stream + 0x20)))(stream, 0, field);
    ((void (*)(u8 *, s32, u8 *))(*(u8 **)(*(u8 **)stream + 0x1C)))(stream, 1, sp);
    func_002DFBC8(stream);
    return 0;
}
