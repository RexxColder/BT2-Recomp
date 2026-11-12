#include "common.h"

s32 BtlObjVis_GetView_207EA0(s32 arg0);
void func_00260260(u8 *arg0, u8 *arg1);
void func_003126C8(s32 arg0, s32 arg1);
extern s32 D_002C3630[] __attribute__((section(".data")));

/* 0x00209730 (asm wins): frame 0xE0; sp[0x50] = &sp[0x10], sp[0xC8] = view->0xFB8; func_00260260(view, sp);
 * copies *(sp[0x50]) to arg1 and returns *(f32 *)(sp[0x50] + 0x10). With no view: copies D_002C3630, returns 0. */
f32 func_00209730(s32 arg0, s32 arg1) {
    u8 sp[0xE0] __attribute__((aligned(16)));
    u8 *view;

    view = (u8 *)BtlObjVis_GetView_207EA0(arg0);
    if (view == NULL) {
        func_003126C8(arg1, (s32)D_002C3630);
        return 0.0f;
    }
    *(u8 **)(sp + 0x50) = sp + 0x10;
    *(f32 *)(sp + 0xC8) = *(f32 *)(view + 0xFB8);
    func_00260260(view, sp);
    func_003126C8(arg1, (s32)*(u8 **)(sp + 0x50));
    return *(f32 *)(*(u8 **)(sp + 0x50) + 0x10);
}
