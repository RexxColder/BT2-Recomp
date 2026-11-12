#include "common.h"

extern u8 *func_001F3758(u8 *arg0);
extern s32 BtlScene_IsCharStopped(s32 arg0);
extern void func_00129C38(u8 *arg0, u8 *arg1);
extern void func_00165F60(s32 arg0, u8 *arg1, u8 *arg2, s32 arg3);

void func_00166D18(u8 *arg0) {
    u8 *other = func_001F3758(arg0);
    u8 *self = *(u8 **)(arg0 + 0x38);
    u8 *peer = *(u8 **)(other + 0x38);
    s32 *ctx = *(s32 **)(self + 0xB0);

    if (BtlScene_IsCharStopped(*ctx) != 0) {
        return;
    }
    if (*(u16 *)(arg0 + 8) & 1) {
        func_00129C38(self + 0x80, arg0 + 0x10);
        func_00165F60(*ctx, arg0, peer, 1);
        if ((*(u32 *)self & 0x20) == 0) {
            *(u32 *)self |= 0x20;
        }
    }
    if (*(u16 *)(arg0 + 8) & 4) {
        *(u32 *)self |= 1;
    }
}
