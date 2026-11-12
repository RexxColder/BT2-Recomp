#include "m2c_macros.h"

M2C_UNK func_00272680();                            /* extern */
M2C_UNK func_002740B8(M2C_UNK);                     /* extern */
M2C_UNK func_00276430(void *);                      /* extern */
M2C_UNK func_00277B80();                            /* extern */
extern void *gBtlStage;

void func_00271FD8(void) {
    M2C_FIELD(gBtlStage, s32 *, 8) = 0;
    func_00276430(gBtlStage);
    func_002740B8(0);
    func_00272680();
    func_00277B80();
}
