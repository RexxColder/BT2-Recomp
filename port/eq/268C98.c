#include "common.h"

void func_003126C8(s32 arg0, void *arg1);
extern f32 D_00386EC4;
extern f32 D_00386EC8;
extern f32 D_00386ECC;
extern f32 D_00386ED0;
extern f32 D_00386ED4;
extern s32 D_00387A44;

void func_00268C98(u8 *arg0, u8 *arg1) {
    f32 temp_f1;
    f32 var_f0;

    temp_f1 = *(f32 *)(arg0 + 0xFAC);
    if (temp_f1 <= 23.0f) {
        *(f32 *)(arg1 + 8) = 18.0f;
        var_f0 = D_00386EC4;
    } else if (temp_f1 <= 50.0f) {
        *(f32 *)(arg1 + 8) = D_00386EC8;
        var_f0 = D_00386ECC;
    } else if (temp_f1 <= 70.0f) {
        *(f32 *)(arg1 + 8) = 50.0f;
        var_f0 = D_00386ED0;
    } else {
        *(f32 *)(arg1 + 8) = 85.0f;
        var_f0 = D_00386ED4;
    }
    *(f32 *)(arg1 + 0x30) = var_f0;
    func_003126C8(D_00387A44 + 0xE540, arg0 + 0x9C0);
}
