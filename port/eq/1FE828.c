#include "common.h"

s32 BattleResult_GetFlags(s32 arg0);
u8 *BtlChar_GetPos(void *arg0);
s32 BtlPad_Test48(void *arg0, s32 arg1);
void func_001FCF88(void *arg0, s32 arg1);
void func_00206958(void *arg0, s64 arg1);
void func_0020E4B0(f32 farg0, void *arg1, f32 farg2);
s32 func_002113C0(void *arg0, s32 arg1, s32 arg2, s32 arg3);
f32 func_0023F010(void *arg0);
s32 func_0023E520(void *arg0);

void func_001FE828(void *arg0, void *arg1) {
    u8 *temp_s0;
    f32 f0;

    func_00206958(arg0, (s64)0x400000);
    if (BattleResult_GetFlags((s32)arg0) & 0x10000) {
        func_00206958(arg0, (s64)0x20000000);
    }
    if (BattleResult_GetFlags((s32)arg0) & 0x20000) {
        func_00206958(arg0, (s64)0x40000000);
    }
    if (BattleResult_GetFlags((s32)arg0) & 0x40000) {
        func_00206958(arg0, (s64)0x8000 << 16);
    }
    func_002113C0(arg0, 5, 8, 0);
    func_002113C0(arg0, 4, 4, 1);
    *(s32 *)((u8 *)arg0 + 0x1440) = *(s32 *)((u8 *)arg0 + 0x1440) + 1;
    temp_s0 = BtlChar_GetPos(arg0);
    f0 = func_0023F010(arg0);
    func_0020E4B0(*(f32 *)(temp_s0 + 0xB4), arg1, f0);
    if (BtlPad_Test48(arg1, 0xC) != 0) {
        func_002113C0(arg1, 4, 0x4000, 1);
    }
    if (BtlPad_Test48(arg1, 0xD) != 0) {
        func_002113C0(arg1, 4, 0x8000, 1);
    }
    if (BtlPad_Test48(arg1, 0xE) != 0) {
        func_002113C0(arg1, 4, 0x10000, 1);
    }
    if (BtlPad_Test48(arg1, 0xF) != 0) {
        func_002113C0(arg1, 4, 0x20000, 1);
    }
    if (BtlPad_Test48(arg1, 8) == 0) {
        func_002113C0(arg1, 4, 0x40000, 1);
    }
    func_001FCF88(arg1, func_0023E520(arg0));
}
