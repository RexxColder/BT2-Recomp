#include "common.h"

s32 BtlObjXf_Update(s32 arg0);
void func_001FA110(s32 arg0, s32 arg1, s32 arg2);
void func_00206958(s32 arg0, s64 arg1);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(s32 arg0, s32 arg1, f32 farg0);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_00216678(s32 arg0);
extern f32 D_003869D4;
extern f32 D_003869D8;
extern f32 D_003869DC;
extern f32 D_003869E0;

void func_002364B8(s32 arg0) {
    f32 temp_f20;
    s32 v;
    s32 lt;

    v = BtlObjXf_Update(arg0);
    lt = v < 0x160;
    if (v == 0x15F || (lt ? v == 0x13D : v == 0x181)) {
        func_001FA110(arg0, 0, lt);
    }

    temp_f20 = D_003869D4;
    func_00215068(arg0, 5, 0xD, D_003869D8, temp_f20);
    func_00215E88(arg0, 3, temp_f20);
    func_00216208(arg0, D_003869DC, D_003869E0);
    func_00216678(arg0);
    func_002113C0(arg0, 1, 0x800, 1);
    func_002113C0(arg0, 6, 4, 1);
    func_002113C0(arg0, 6, 8, 1);
    func_002113C0(arg0, 1, 0x1000, 1);
    func_002113C0(arg0, 1, 0x02000000, 1);
    func_00206958(arg0, (s64)0x8000 << 29);
}
