#include "common.h"

s32 func_002AF5E8(u8 *arg0); /* GUESS arity: a0 = arg0 passes through */
s32 func_002ADFD8(u8 *arg0);
void func_002AFC18(u8 *arg0, s32 arg1);
void func_002B0F78(u8 *arg0, s32 arg1, f32 farg0);
void func_002B11F0(u8 *arg0, f32 farg0, f32 farg1);
void func_002B1298(u8 *arg0, f32 farg0, f32 farg1);
extern f32 D_00387468;
extern f32 D_0038746C;
extern f32 D_00387470;
extern f32 D_00387474;
extern f32 D_00387478;
extern u8 *D_00387E18;

void func_002AF3D0(u8 *arg0) {
    if (func_002AF5E8(arg0) != 0) {
        *(u8 *)(D_00387E18 + 8) = 1;
    }
    func_002B0F78(arg0, 0, D_00387468);
    func_002B11F0(arg0, 0.0f, D_0038746C);
    if (func_002ADFD8(arg0) != 0) {
        func_002B1298(arg0, D_00387470, D_00387474);
    } else {
        func_002B1298(arg0, 0.0f, D_00387478);
    }
    func_002AFC18(arg0, 4);
    *(u8 *)(arg0 + 0x7D) = 1;
}
