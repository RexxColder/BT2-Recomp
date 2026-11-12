#include "common.h"

void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
f32 func_00207F38(s32 arg0);
void func_00121050(f32 farg0, f32 farg1, void *arg0, void *arg1);
s32 func_00126058(void *arg0, s32 arg1, s32 arg2);
void *func_00126040(void *arg0);
void *BtlChar_GetPos(void *arg0);
f32 func_001216C0(void *arg0);
s32 func_00217488(void *arg0);
void func_00122708(void *arg0, s32 arg1);
void func_00122728(void *arg0, s32 arg1);
void func_001226F0(void *arg0, s32 arg1);
extern f32 D_00384110;

void func_001229F0(u8 *arg0) {
    f32 sp[4];
    f32 temp_f20;
    s32 temp_v0;
    u8 *temp_s1;

    temp_s1 = arg0 + 0xFE0;
    func_00208DE8(*(s32 *)arg0, sp, 3);
    temp_f20 = func_00207F38(*(s32 *)arg0);
    func_00121050(10.0f, D_00384110, arg0, arg0 + 0x1050);
    if (func_00126058(arg0, 0, 2) == 0) {
        if ((func_00126058(arg0, 0, 4) == 0)
            && (*(f32 *)((u8 *)BtlChar_GetPos(func_00126040(arg0)) + 0xC4) > 0.0f)
            && (*(f32 *)(temp_s1 + 0x44) < (sp[1] + func_001216C0(arg0)))) {
            func_00122708(arg0, 0x800);
        }
    } else if ((func_00217488(func_00126040(arg0)) == 0x12)
               || (temp_v0 = *(s32 *)(temp_s1 + 0x20) + 1, *(s32 *)(temp_s1 + 0x20) = temp_v0, ((temp_v0 & 1) != 0))) {
        func_00122728(arg0, 0x200);
    }
    if (((*(f32 *)(temp_s1 + 0x44) - func_001216C0(arg0)) - temp_f20) < sp[1]) {
        func_001226F0(arg0, 0);
    }
    if (func_00126058(arg0, 0, 4) != 0) {
        func_001226F0(arg0, 0);
    }
    if ((*(s32 *)(temp_s1 + 0x28) & 4) && (*(f32 *)(temp_s1 + 0x44) < sp[1])) {
        func_00217488(func_00126040(arg0));
    }
}
