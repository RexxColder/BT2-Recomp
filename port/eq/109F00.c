#include "common.h"

extern u8 *D_00387A40;

f32 Ramp_Start(s32 arg0, f32 farg0, f32 farg1, f32 farg2);
void func_0020CDC8(s32 arg0);
void func_0025ADD0(s32 arg0, s32 arg1);
s32 func_00101608(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_00267550(s32 arg0, s32 arg1, s32 arg2);

/* 0x00109F00: per-step handler for the record arg0 (mode byte at +8, modes 0..4). Modes 0 and 2
 * each take a channel byte (+9 or +0xA), start a ramp at +0x14, run func_00101608 with two
 * halfwords (+0x10/+0xC or +0x12/+0xE) and func_00267550 at the table base plus channel * 0x18580,
 * then advance the mode byte. Other modes do nothing. Returns 1. */
s32 func_00109F00(u8 *arg0) {
    u32 v = *(u8 *)(arg0 + 0x8);
    s32 ch;

    if (v < 5) {
        switch (v) {
            case 0:
                ch = *(u8 *)(arg0 + 0x9);
                func_0020CDC8(ch);
                Ramp_Start((s32)(arg0 + 0x14), 10.0f, 0.0f, 1.0f);
                func_0025ADD0(ch, 0);
                func_00101608(ch, *(u16 *)(arg0 + 0x10), *(u16 *)(arg0 + 0xC), 0, 0);
                func_00267550(*(s32 *)D_00387A40 + ch * 0x18580, 2, *(u16 *)(arg0 + 0xC));
                *(u8 *)(arg0 + 0x8) = (u8)(*(u8 *)(arg0 + 0x8) + 1);
                break;
            case 2:
                ch = *(u8 *)(arg0 + 0xA);
                func_0020CDC8(ch);
                Ramp_Start((s32)(arg0 + 0x14), 10.0f, 0.0f, 1.0f);
                func_0025ADD0(ch, 0);
                func_00101608(ch, *(u16 *)(arg0 + 0x12), *(u16 *)(arg0 + 0xE), 0, 0);
                func_00267550(*(s32 *)D_00387A40 + ch * 0x18580, 2, *(u16 *)(arg0 + 0xE));
                *(u8 *)(arg0 + 0x8) = (u8)(*(u8 *)(arg0 + 0x8) + 1);
                break;
            default:
                break;
        }
    }
    return 1;
}
