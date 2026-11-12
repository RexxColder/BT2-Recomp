#include "common.h"

extern s32 func_001F3758(s32 arg0);
extern void func_00126ED0();
extern void func_0014EEF8(s32 arg0, s32 arg1);
extern void func_00168F70(s32 arg0);
extern void func_00147FB8(s32 arg0);

void func_00169CE0(u8 *self) {
    u8 *other = (u8 *)func_001F3758((s32)self);
    s32 otherField = *(s32 *)(other + 0x38);
    u8 *sub = *(u8 **)(self + 0x38);
    s32 *handle = *(s32 **)(sub + 0xB0);

    func_00126ED0();
    func_0014EEF8(otherField, (s32)(sub + 0xB4));
    func_00168F70((s32)self);
    func_00147FB8(*handle);
}
