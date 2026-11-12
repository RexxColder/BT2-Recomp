#include "common.h"

extern s32 func_001F3758(s32 arg0);
extern s32 func_001A1210(s32 arg0);
extern void func_00147FB8(s32 arg0);
extern void func_0014EEF8(s32 arg0, s32 arg1);

void func_0015A828(u8 *self) {
    u8 *other = (u8 *)func_001F3758((s32)self);
    u8 *selfSub = *(u8 **)(self + 0x38);
    s32 otherField = *(s32 *)(other + 0x38);
    s32 *handle = *(s32 **)(selfSub + 0x80);

    if (**(s32 **)((u8 *)handle + 0x20) != 0xD2) {
        func_001A1210(*handle);
        func_00147FB8(*handle);
    }
    func_0014EEF8(otherField, (s32)(selfSub + 0x84));
}
