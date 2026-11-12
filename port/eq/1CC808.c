#include "m2c_macros.h"

extern s32 func_00126598(s32 arg0);
extern s32 func_001267E8(s32 arg0, s32 arg1);
extern void func_00128EF0(void);
extern void func_00128F08(void);
extern void func_00128F90(s32 arg0);
extern void func_001CBA98(s32 arg0, s32 arg1, s64 arg2, f32 farg0, f32 farg1);
extern void func_001CC0A0(s32 arg0, s32 arg1);
extern s32 gBtlCamView;

void func_001CC808(u8 *arg0) {
    u8 *s0;
    u8 *s2;
    u8 v;

    s0 = *(u8 **)(arg0 + 0x38);
    s2 = *(u8 **)(s0 + 0x34);
    if (func_001267E8(*(s32 *)s0, *(u8 *)(s0 + 0x44)) != 0) {
        return;
    }
    if (*(s32 *)(s0 + 0x40) & 0x10) {
        if (func_00126598(*(s32 *)s0) == 0) {
            return;
        }
    }
    func_00128EF0();
    func_00128F90(gBtlCamView + 0x100);
    v = s2[1];
    switch (v) {
    case 0:
        func_001CBA98((s32)arg0, (s32)(s0 + 0x80), *(s64 *)(s0 + 0xC0),
                      *(f32 *)(s0 + 0x64), *(f32 *)(s0 + 0x68));
        break;
    case 1:
        func_001CC0A0((s32)arg0, (s32)(s0 + 0x80));
        break;
    }
    func_00128F08();
}
