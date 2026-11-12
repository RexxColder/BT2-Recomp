#include "m2c_macros.h"

M2C_UNK func_00191B80(void *);                      /* extern */

void func_00194928(void *arg0) {
    void *temp_a0;

    temp_a0 = M2C_FIELD(arg0, void **, 0x38);
    M2C_FIELD(temp_a0, s32 *, 0x60) = 0;
    func_00191B80(temp_a0);
}
