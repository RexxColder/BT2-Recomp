#include "common.h"

void func_001F9FB0(s32 arg0, s32 arg1);
void func_00215068(f32 farg0, f32 farg1, s32 arg0, s32 arg1, s32 arg2);
void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
void func_00216208(f32 farg0, f32 farg1, s32 arg0);
void func_00216678(s32 arg0);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00206958(s32 arg0, s64 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_00211328(s32 arg0, s32 arg1, s32 arg2);
void func_00237088(s32 arg0);
s32 BtlChar_GetPos(s32 arg0);
extern f32 D_00386A70;
extern f32 D_00386A74;
extern f32 D_00386A78;
extern f32 D_00386A7C;

void func_00237B90(s32 arg0) {
    u8 *p;
    s32 temp_s0;

    p = (u8 *)arg0;
    func_001F9FB0(arg0, 1);
    func_00215068(D_00386A70, 0.5f, arg0, 8, 0xD);
    func_00215E88(D_00386A74, arg0, 3);
    func_00216208(D_00386A78, D_00386A7C, arg0);
    func_00216678(arg0);
    func_002113C0(arg0, 6, 2, 1);
    func_002113C0(arg0, 6, 4, 1);
    func_002113C0(arg0, 0xD, 1, 1);
    func_002113C0(arg0, 1, 0x1000, 1);
    func_002113C0(arg0, 1, 0x40, 1);
    func_002113C0(arg0, 3, 0x800, 1);
    func_002113C0(arg0, 3, 0xE, 1);
    func_002113C0(arg0, 6, 8, 1);
    func_00206958(arg0, (s64)0x8000 << 29);
    func_002113C0(arg0, 1, 0x800, 1);
    if (func_00211310(arg0, 1, 0x200) == 0 && func_00211328(arg0, 1, 0x200) != 0) {
        func_00237088(arg0);
        *(s32 *)(p + 0x8DC) = *(s32 *)(p + 0x8DC) | 1;
    }
    if (*(s32 *)(p + 0x8DC) & 1) {
        temp_s0 = BtlChar_GetPos(arg0);
        *(f32 *)((u8 *)temp_s0 + 0xD4) = -*(f32 *)((u8 *)BtlChar_GetPos(arg0) + 0xB0);
    }
}
