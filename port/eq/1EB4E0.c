#include "common.h"

void *func_001EB6F0(void);
s32 func_001EAD08(void *arg0, s64 arg1, s64 arg2, s64 arg3, s64 arg4, s64 arg5, s64 arg6, s64 arg7,
                  s64 arg8, s64 arg9, s64 arg10, s64 arg11, s64 arg12, s64 arg13, s64 arg14, s64 arg15);
void func_001EB758(void *arg0, void *arg1, void *arg2);

void func_001EB4E0(void *arg0) {
    u8 fr[0x80];
    u8 *a0;
    u8 *temp_v0;
    s64 v0v;
    s64 v1v;
    s64 a1v;
    s64 a2v;
    s64 a3v;
    s64 t0v;
    s64 t1v;
    s64 t2v;

    temp_v0 = (u8 *)func_001EB6F0();
    if (temp_v0 != NULL) {
        a0 = (u8 *)arg0;
        *(s32 *)(fr + 0x40) = *(s32 *)(a0 + 4);
        *(s32 *)(fr + 0x44) = *(s32 *)(a0 + 8);
        *(s32 *)(fr + 0x48) = *(s32 *)(a0 + 0);
        *(f32 *)(fr + 0x70) = *(f32 *)(a0 + 0x34);
        *(s32 *)(fr + 0x74) = *(s32 *)(a0 + 0x38);
        *(s32 *)(fr + 0x78) = *(s32 *)(a0 + 0x3C);
        *(u8 *)(fr + 0x7C) = *(u8 *)(a0 + 0x40);
        v1v = *(s64 *)(fr + 0x48);
        a1v = *(s64 *)(fr + 0x70);
        v0v = *(s64 *)(fr + 0x40);
        t2v = *(s64 *)(fr + 0x78);
        a2v = *(s64 *)(a0 + 0x20);
        a3v = *(s64 *)(a0 + 0x28);
        t0v = *(s64 *)(a0 + 0x10);
        t1v = *(s64 *)(a0 + 0x18);
        *(s64 *)(fr + 0x0) = v0v;
        *(s64 *)(fr + 0x8) = v1v;
        *(s64 *)(fr + 0x10) = a2v;
        *(s64 *)(fr + 0x18) = a3v;
        *(s64 *)(fr + 0x20) = t0v;
        *(s64 *)(fr + 0x28) = t1v;
        *(s64 *)(fr + 0x30) = a1v;
        *(s64 *)(fr + 0x38) = t2v;
        *(s64 *)(fr + 0x50) = a2v;
        *(s64 *)(fr + 0x58) = a3v;
        *(s64 *)(fr + 0x60) = t0v;
        *(s64 *)(fr + 0x68) = t1v;
        *(s32 *)temp_v0 = func_001EAD08(fr, a1v, a2v, a3v, t0v, t1v, t2v, 0,
                                        v0v, v1v, a2v, a3v, t0v, t1v, a1v, t2v);
        *(s32 *)(temp_v0 + 4) = 1;
        *(s32 *)(temp_v0 + 8) = 0;
        *(s32 *)(temp_v0 + 0xC) = 0;
        func_001EB758(a0 + 0x64, a0 + 0x68, temp_v0);
    }
}
