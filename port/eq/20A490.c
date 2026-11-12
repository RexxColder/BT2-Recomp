#include "common.h"

s32 func_00211288(s32 arg0);
extern f32 D_003859AC;
extern s32 D_00387930;
extern s32 gBtlCam;

s32 BtlCharApi_ObjTestFlagBit21(s32 arg0) {
    s32 view;
    s32 cam;

    if (D_00387930 == 0) {
        return 0;
    }
    if ((u32)arg0 >= 2) {
        return 0;
    }
    view = func_00211288(arg0);
    cam = gBtlCam + *(s32 *)(view + 0x1538) * 0x300;
    if (!(*(f32 *)(cam + 0x2C4) < D_003859AC)) {
        return 0;
    }
    if (*(s32 *)(cam + 0x254) != arg0) {
        return 0;
    }
    return 1;
}
