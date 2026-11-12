#include "common.h"

s32 Dma_BeginDirect(s32 arg0, s32 arg1);
void Dma_EndDirect(s32 arg0);
s32 func_00114728(s32 arg0);
s32 func_00114890(s32 arg0, f32 farg0);
s32 func_00114B10(s32 arg0, s32 arg1, f32 farg0);
s32 func_00114CB0(s32 arg0, s32 arg1, s32 arg2, f32 farg0);
s32 func_00115B10(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 t0, f32 farg0);
s32 func_00115E70(s32 arg0, s32 arg1, s64 arg2, s32 arg3, f32 farg0, f32 farg1);
s32 func_0020A440(s32 arg0);
f32 func_0020C108(s32 arg0);

void func_00116A90(u8 *arg0, s32 arg1) {
    s32 s3;
    s32 s1;
    s32 t;
    f32 f;

    s3 = (arg1 == 0);
    t = Dma_BeginDirect((s32)arg0, arg1);
    t = func_00114728(t);
    t = func_00114890(t, *(f32 *)(arg0 + 0xF0));
    s1 = func_00114CB0(t, (s32)arg0, (s32)(arg0 + 0x100), *(f32 *)(arg0 + 0xF0));
    f = func_0020C108(arg1);
    s1 = func_00114B10(s1, arg1, f);
    if (*(s32 *)(arg0 + 0x50) != 0) {
        s1 = func_00115E70(s1, (s32)(arg0 + 0x54), *(s32 *)(arg0 + 0x5C), 0x30,
                           *(f32 *)(arg0 + 0x48), *(f32 *)(arg0 + 0x4C));
    }
    if (func_0020A440(arg1) != 0) {
        s1 = func_00115B10(s1, (s32)arg0, s3, arg1, 1, *(f32 *)(arg0 + 0xF0));
    } else if (*(s32 *)(arg0 + 0x20) != 0) {
        s1 = func_00115E70(s1, (s32)(arg0 + 0x24), *(s32 *)(arg0 + 0x2C), 0x70,
                           *(f32 *)(arg0 + 0x18), *(f32 *)(arg0 + 0x1C));
    }
    s1 = func_00115B10(s1, (s32)arg0, arg1, -1, 0, *(f32 *)(arg0 + 0xF0));
    if (*(s32 *)(arg0 + 0x38) != 0) {
        s1 = func_00115E70(s1, (s32)(arg0 + 0x3C), *(s32 *)(arg0 + 0x44), 0x80,
                           *(f32 *)(arg0 + 0x30), *(f32 *)(arg0 + 0x34));
    }
    Dma_EndDirect(s1);
}
