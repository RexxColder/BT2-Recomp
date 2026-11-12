#include "common.h"

extern u8 *gBtlCam;
void func_0025BDD0(u8 *arg0, u8 *arg1, u8 *arg2);
void func_0025B5E8(u8 *arg0, u8 *arg1);

void func_0025BF28(void) {
    u8 *p = *(u8 **)(gBtlCam + 0x600);

    if (*(u8 *)(p + 0x2C0) != 0) {
        func_0025BDD0(p, p + 0x2D0, p + 0x280);
        p = *(u8 **)(gBtlCam + 0x600);
        func_0025B5E8(p, p + 0x2D0);
    } else {
        func_0025BDD0(p, p + 0x270, p + 0x280);
        p = *(u8 **)(gBtlCam + 0x600);
        func_0025B5E8(p, p + 0x270);
    }
}
