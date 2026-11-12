#include "m2c_macros.h"

void func_2B7210(s32);
void func_2B73C0(s32, s32, s32);
s32 func_2B8328(s32);
void func_2BB038(s32, s32, s32);

void func_003B4FF8(void *arg0) {
    if (arg0 != 0) {
        if (func_2B8328(M2C_FIELD(arg0, s32 *, 0xC0)) == 2) {
            func_2B7210(M2C_FIELD(arg0, s32 *, 0xC0));
        }
        M2C_FIELD(arg0, s32 *, 0xCC) = 2;
        M2C_FIELD(arg0, s32 *, 0xC8) = 1;
        if (M2C_FIELD(arg0, s32 *, 0x1B8) != 0) {
            func_2BB038(M2C_FIELD(arg0, s32 *, 0xC0), M2C_FIELD(arg0, s32 *, 0xC4), M2C_FIELD(arg0, s32 *, 0x1AC));
            return;
        }
        func_2B73C0(M2C_FIELD(arg0, s32 *, 0xC0), M2C_FIELD(arg0, s32 *, 0xC4), M2C_FIELD(arg0, s32 *, 0x1AC));
    }
}
