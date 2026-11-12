#include "m2c_macros.h"

M2C_UNK func_0026EA88(void *);                      /* extern */
M2C_UNK func_0026EAE0(void *, M2C_UNK);             /* extern */
extern void *D_00387978;

void func_00248640(void) {
    if (M2C_FIELD(D_00387978, s32 *, 0x38) & 4) {
        return;
    }
    M2C_FIELD(D_00387978, s32 *, 0x38) = 4;
    func_0026EAE0(D_00387978 + 4, 0x3C);
    func_0026EA88(D_00387978 + 4);
}
