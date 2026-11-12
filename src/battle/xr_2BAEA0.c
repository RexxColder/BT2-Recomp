#include "m2c_macros.h"

M2C_UNK Rand_Range(M2C_UNK *, M2C_UNK);             /* extern */
s32 func_002B8280();
void func_002BAD68(void *, M2C_UNK);
void func_002BAF08(void *);
extern M2C_UNK D_00379BE8 __attribute__((section(".data")));

/* Random-gated reset: if func_002B8280() != 1 calls Rand_Range and returns; else func_002BAD68(arg0, 0), func_002BAF08(arg0), then sets +0x2E8 = 4 */
void func_002BAEA0(void *arg0) {
    if (func_002B8280(arg0) != 1) {
        Rand_Range(&D_00379BE8, 0);
        return;
    }
    func_002BAD68(arg0, 0);
    func_002BAF08(arg0);
    M2C_FIELD(arg0, s32 *, 0x2E8) = 4;
}
