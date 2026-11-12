#include "m2c_macros.h"

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */

void func_001DBFE0(void *arg0, void *arg1) {
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 0x38);
    memset(temp_s0, 0, 0x40);
    M2C_FIELD(temp_s0, s64 *, 0) = (s64) M2C_FIELD(arg1, s64 *, 0);
    M2C_FIELD(temp_s0, s64 *, 8) = (s64) M2C_FIELD(arg1, s64 *, 8);
    M2C_FIELD(temp_s0, s64 *, 0x10) = (s64) M2C_FIELD(arg1, s64 *, 0x10);
    M2C_FIELD(temp_s0, s64 *, 0x18) = (s64) M2C_FIELD(arg1, s64 *, 0x18);
    M2C_FIELD(temp_s0, s64 *, 0x20) = (s64) M2C_FIELD(arg1, s64 *, 0x20);
    M2C_FIELD(temp_s0, s64 *, 0x28) = (s64) M2C_FIELD(arg1, s64 *, 0x28);
}
