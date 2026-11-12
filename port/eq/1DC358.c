#include "common.h"

s32 BtlCharApi_IsInTechnique(s32 arg0);
void BtlTask_SetDead(void *arg0);
void func_001DC5C0(void *arg0);
void func_001DCA90(void *arg0);
void func_001DCCC0(void *arg0);
s32 func_001DCDB8(void *arg0);
void func_001DCE58(void *arg0);
void func_001DCED8(void *arg0, s32 arg1);
s32 func_0020A9C0(s32 arg0);
s32 func_0020AA20(s32 arg0);
s32 func_0020AA78(s32 arg0);
s32 func_0020AC98(s32 arg0);
s32 func_0020AD28(s32 arg0);

void func_001DC358(u8 *arg0) {
    u8 *s0;
    s32 temp_v0;
    u8 v1;
    s32 var_v0;

    s0 = *(u8 **)(arg0 + 0x38);
    if (func_0020AC98(*(s32 *)(s0 + 0x244)) == 0) {
        *(u16 *)(s0 + 0x24C) = (u16)(*(u16 *)(s0 + 0x24C) | 2);
    }
    if (func_0020AD28(*(s32 *)(s0 + 0x244)) != 0) {
        *(u16 *)(s0 + 0x24C) = (u16)(*(u16 *)(s0 + 0x24C) | 2);
    }
    if (BtlCharApi_IsInTechnique(*(s32 *)(s0 + 0x244)) != 0) {
        *(u16 *)(s0 + 0x24C) = (u16)(*(u16 *)(s0 + 0x24C) | 2);
    }
    if (func_0020A9C0(*(s32 *)(s0 + 0x244)) != 0) {
        *(u16 *)(s0 + 0x24C) = (u16)(*(u16 *)(s0 + 0x24C) | 2);
    }
    if (func_0020AA78(*(s32 *)(s0 + 0x244)) != 0) {
        *(u16 *)(s0 + 0x24C) = (u16)(*(u16 *)(s0 + 0x24C) | 2);
    }
    if (func_0020AA20(*(s32 *)(s0 + 0x244)) != 0) {
        *(u16 *)(s0 + 0x24C) = (u16)(*(u16 *)(s0 + 0x24C) | 2);
    }

    v1 = arg0[1];
    var_v0 = 2;
    switch (v1) {
    case 0:
        if (!(*(u16 *)(s0 + 0x24C) & 2)) {
            func_001DCA90(arg0);
        }
        var_v0 = arg0[1] + 1;
        arg0[1] = (u8)var_v0;
        break;
    case 1:
        arg0[1] = (u8)var_v0;
        break;
    case 2:
        temp_v0 = func_001DCDB8(arg0);
        if (temp_v0 == 0) {
            *(u16 *)(s0 + 0x24C) = (u16)(*(u16 *)(s0 + 0x24C) | 2);
        }
        if (*(u16 *)(s0 + 0x24C) & 2) {
            if (temp_v0 != 0) {
                func_001DCE58(arg0);
            }
            var_v0 = arg0[1] + 1;
            arg0[1] = (u8)var_v0;
        }
        break;
    default:
        break;
    }

    func_001DC5C0(arg0);
    func_001DCCC0(arg0);
    func_001DCDB8(arg0);
    if (!(*(u16 *)(s0 + 0x24C) & 4)) {
        return;
    }
    func_001DCED8(arg0, *(s32 *)(s0 + 0x244));
    BtlTask_SetDead(arg0);
}
