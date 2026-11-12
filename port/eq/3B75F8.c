#include "m2c_macros.h"

void func_003B6DE8(s32);

void func_003B75F8(u8 *arg0) {
    s32 count = 0;
    s32 off = 0;

    if (M2C_FIELD(arg0, s32 *, 0x4) > 0) {
        do {
            count += 1;
            func_003B6DE8(M2C_FIELD(arg0, s32 *, 0x0) + off);
            off += 0xBC;
        } while (count < M2C_FIELD(arg0, s32 *, 0x4));
    }
}
