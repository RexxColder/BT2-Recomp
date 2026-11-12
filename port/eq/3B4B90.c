#include "m2c_macros.h"

s32 func_2B8328(s32);
void func_2B7290(s32, s32);
void func_2B7210(s32);

void func_003B4B90(void *arg0) {
    s32 r;

    r = func_2B8328(M2C_FIELD(arg0, s32 *, 0xC0));
    if (M2C_FIELD(arg0, s32 *, 0xC8) == 1) {
        if (r == 2) {
            M2C_FIELD(arg0, s32 *, 0xCC) -= 1;
        }
        if (M2C_FIELD(arg0, s32 *, 0xCC) <= 0) {
            func_2B7290(M2C_FIELD(arg0, s32 *, 0xC0), 0);
            M2C_FIELD(arg0, s32 *, 0xC8) = 2;
        }
    }
    if (r == 3) {
        func_2B7210(M2C_FIELD(arg0, s32 *, 0xC0));
    }
}
