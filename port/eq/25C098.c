#include "common.h"

s32 func_002097A8(s32 arg0, void *arg1, void *arg2, void *arg3, void *arg4);
s32 func_00209848(s32 arg0);
f32 func_00209AC0(s32 arg0, void *arg1);
s32 func_00209B08(s32 arg0);
void func_0025B5E8(void *arg0, void *arg1);
void func_0025BB38(void *arg0, s32 arg1);
void func_0025BDD0(void *arg0, void *arg1, void *arg2);
extern u8 *D_003876A0;
extern u8 *gBtlCam;

/* 0x0025C098: camera update for the battle camera (gBtlCam, camera block at +0x600). A flag bit
 * in D_003876A0 (64-bit word at +0x4D8) first resets the block's +0x258 and runs func_0025BB38.
 * Then the block's +0x254 gets arg0, the camera vectors and scalars are refreshed, and the
 * +0x2C0 flag picks which pair of vectors func_0025BDD0 and func_0025B5E8 work on. */
void func_0025C098(s32 arg0) {
    u8 *c;

    if ((*(s64 *)(D_003876A0 + 0x4D8) & 2) != 0) {
        c = *(u8 **)(gBtlCam + 0x600);
        *(s32 *)(c + 0x258) = 1;
        c = *(u8 **)(gBtlCam + 0x600);
        func_0025BB38(c, *(s32 *)(c + 0x250) == 0);
    }

    *(s32 *)(*(u8 **)(gBtlCam + 0x600) + 0x254) = arg0;
    c = *(u8 **)(gBtlCam + 0x600);
    func_002097A8(arg0, c + 0x270, c + 0x2D0, c + 0x280, c + 0x290);

    *(u8 *)(*(u8 **)(gBtlCam + 0x600) + 0x2C0) = func_00209848(arg0);
    *(f32 *)(*(u8 **)(gBtlCam + 0x600) + 0x2C4) = func_00209AC0(arg0, gBtlCam);
    *(s32 *)(*(u8 **)(gBtlCam + 0x600) + 0x260) = func_00209B08(arg0);

    c = *(u8 **)(gBtlCam + 0x600);
    if (*(u8 *)(c + 0x2C0) != 0) {
        func_0025BDD0(c, c + 0x2D0, c + 0x280);
        c = *(u8 **)(gBtlCam + 0x600);
        func_0025B5E8(c, c + 0x2D0);
        return;
    }
    func_0025BDD0(c, c + 0x270, c + 0x280);
    c = *(u8 **)(gBtlCam + 0x600);
    func_0025B5E8(c, c + 0x270);
}
