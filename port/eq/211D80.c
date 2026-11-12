#include "common.h"

f32 BtlCharApi_GetHeight(s32 arg0);
u8 *BtlChar_GetPos(s32 arg0);
void func_002608E8(s32 arg0);
s32 func_002765A8(s32 a0, s32 a1, s32 a2, s32 a3);
s32 func_00276700(s32 a0, s32 a1);
void func_003126C8(s32 a0, s32 a1);

void func_00211D80(s32 arg0, s32 arg1) {
    u8 *p = (u8 *)arg0;
    s32 buf[8];
    u8 *sp = (u8 *)buf;          /* sp+0 = buf[0], sp10 = buf+4 (sp+0x10), sp+0x14 = buf[5] */
    u8 *sp10 = (u8 *)(buf + 4);
    s32 var_s1 = 0;
    s32 var_v0;
    u8 *x3;
    u8 *x4;
    u8 *x5;
    u8 *x6;
    f32 f1;
    f32 hgt;

    if (arg1 == 0) {
        var_v0 = func_002765A8(*(s32 *)(p + 0x1534), (s32)sp, (s32)sp10, 0);
        var_s1 = var_v0;
    } else if (arg1 == 1) {
        var_v0 = func_00276700((s32)sp, (s32)sp10);
        var_s1 = var_v0;
    } else if (arg1 == 2) {
        var_v0 = func_002765A8(*(s32 *)(p + 0x1534), (s32)sp, (s32)sp10, 1);
        var_s1 = var_v0;
    }
    func_003126C8((s32)BtlChar_GetPos(arg0), (s32)sp);
    func_003126C8((s32)(BtlChar_GetPos(arg0) + 0x10), (s32)sp10);
    func_003126C8((s32)(*(u8 **)(p + 0x1530) + 0x9A0), (s32)sp);
    func_003126C8((s32)(*(u8 **)(p + 0x1530) + 0x9C0), (s32)sp);
    func_003126C8((s32)(*(u8 **)(p + 0x1530) + 0x9B0), (s32)sp10);
    *(s32 *)(*(u8 **)(p + 0x1530) + 0x9F0) = var_s1;
    x3 = BtlChar_GetPos(arg0);
    *(f32 *)(x3 + 0xB4) = *(f32 *)(sp + 0x14);
    x4 = BtlChar_GetPos(arg0);
    *(s32 *)(x4 + 0xB0) = 0;
    x5 = BtlChar_GetPos(arg0);
    *(s32 *)(x5 + 0xC0) = 0;
    x6 = BtlChar_GetPos(arg0);
    *(s32 *)(x6 + 0xC4) = 0;
    *(f32 *)(p + 0x180) = *(f32 *)(sp + 0x0);
    hgt = BtlCharApi_GetHeight(*(s32 *)(p + 0x1534));
    f1 = *(f32 *)(sp + 0x4) - hgt;
    *(f32 *)(p + 0x188) = *(f32 *)(sp + 0x8);
    *(f32 *)(p + 0x150) = *(f32 *)(sp + 0x14);
    *(f32 *)(p + 0x184) = f1;
    func_002608E8(*(s32 *)(p + 0x1530));
}
