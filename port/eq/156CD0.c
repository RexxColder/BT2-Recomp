#include "common.h"

/* a1 is a 64-bit register here (ld), a2 carries the packed (A, B) float pair */
void func_001DBF28(s32 arg0, s64 arg1, s64 arg2, s32 arg3);
void func_0019F8D0(s32 arg0);

void func_00156CD0(s32 arg0, s32 arg1, f32 farg0, f32 farg1, f32 farg2) {
    u8 fr[0x90];
    u8 *P;
    s32 Q;
    s64 a2v;
    s64 v1v;
    s64 a1v;
    s64 v0v;

    P = (u8 *)*(s32 *)((u8 *)arg0 + 0x38);
    Q = *(s32 *)(P + 0xB0);
    *(f32 *)(fr + 0xC) = 255.0f;
    *(f32 *)(fr + 0x10) = farg0;
    *(f32 *)(fr + 0x14) = farg1;
    *(f32 *)(fr + 0x18) = farg2;
    *(f32 *)(fr + 0x0) = 255.0f;
    *(f32 *)(fr + 0x4) = 255.0f;
    *(f32 *)(fr + 0x8) = 255.0f;
    if ((arg1 & 0xFF) != 0) {
        *(f32 *)(fr + 0x50) = *(f32 *)(P + 0x80);
        *(f32 *)(fr + 0x54) = *(f32 *)(P + 0x84);
        *(f32 *)(fr + 0x5C) = 1.0f;
        *(f32 *)(fr + 0x58) = *(f32 *)(P + 0x88);
        *(s32 *)(fr + 0x64) = 0;
        *(s32 *)(fr + 0x60) = *(s32 *)(u8 *)Q;
        *(s32 *)(fr + 0x6C) = 1;
        *(s32 *)(fr + 0x68) = 1;
        *(s32 *)(fr + 0x70) = 0;
        a2v = *(s64 *)(fr + 0x50);
        v1v = *(s64 *)(fr + 0x58);
        a1v = *(s64 *)(fr + 0x60);
        *(s64 *)(fr + 0x30) = a1v;
        *(s64 *)(fr + 0x28) = v1v;
        v0v = *(s64 *)(fr + 0x68);
        v1v = *(s64 *)(fr + 0x70);
        a1v = *(s64 *)(fr + 0x78);
        *(s64 *)(fr + 0x20) = a2v;
        *(s64 *)(fr + 0x38) = v0v;
        *(s64 *)(fr + 0x40) = v1v;
        *(s64 *)(fr + 0x48) = a1v;
        *(s32 *)(fr + 0x34) = 0x47;
        func_001DBF28((s32)(fr + 0x20), a1v, a2v, 1);
    }
    func_0019F8D0((s32)fr);
}
