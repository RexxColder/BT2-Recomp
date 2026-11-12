#include "common.h"

extern u8 D_0036EBA0[];

void func_001296A0(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, s32 arg4);
void func_001B5150(u8 *arg0, s32 arg1, s64 arg2);

/* arg1..arg8 are byte arguments (andi 0xFF; arg8 is the byte in the first stack slot). */
void func_001B4AA0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   s32 arg8, s32 arg9, u8 *arg10) {
    u8 fr[0x240];
    s32 k;
    f32 f3;
    f32 f2;
    f32 f1;
    f32 f0;
    f32 f7;
    f32 f6;
    f32 f5;
    f32 f4;

    f3 = (f32)(u8)arg1;
    f2 = (f32)(u8)arg2;
    f1 = (f32)(u8)arg3;
    f0 = (f32)(u8)arg4;
    f7 = (f32)(u8)arg5;
    f6 = (f32)(u8)arg6;
    f5 = (f32)(u8)arg7;
    f4 = (f32)(u8)arg8;

    for (k = 0; k < 8; k++) {
        *(s64 *)(fr + 0x1B0 + 8 * k) = *(s64 *)(D_0036EBA0 + 8 * k);
    }
    *(f32 *)(fr + 0x1F0) = f3;
    *(f32 *)(fr + 0x1F4) = f2;
    *(f32 *)(fr + 0x1F8) = f1;
    *(f32 *)(fr + 0x1FC) = f0;
    *(f32 *)(fr + 0x200) = f3;
    *(f32 *)(fr + 0x204) = f2;
    *(f32 *)(fr + 0x208) = f1;
    *(f32 *)(fr + 0x20C) = f0;
    *(f32 *)(fr + 0x210) = f7;
    *(f32 *)(fr + 0x214) = f6;
    *(f32 *)(fr + 0x218) = f5;
    *(f32 *)(fr + 0x21C) = f4;
    *(f32 *)(fr + 0x220) = f7;
    *(f32 *)(fr + 0x224) = f6;
    *(f32 *)(fr + 0x228) = f5;
    *(f32 *)(fr + 0x22C) = f4;

    func_001296A0(fr, arg0, fr + 0x1B0, fr + 0x1F0, 3);
    func_001B5150(fr, arg9, *(s64 *)arg10);
    func_001296A0(fr, arg0 + 0x10, fr + 0x1C0, fr + 0x200, 3);
    func_001B5150(fr, arg9, *(s64 *)arg10);
}
