#include "m2c_macros.h"

M2C_UNK func_001E0A00(s32);                         /* extern */
M2C_UNK func_001E19F0(s32);                         /* extern */

void func_001E6808(void *arg0) {
    s32 temp_v1;
    void *temp_a0;

    if ((arg0 != NULL) && (temp_a0 = M2C_FIELD(arg0, void **, 0x38), ((M2C_FIELD(temp_a0, s64 *, 0) & 5) == 1))) {
        temp_v1 = M2C_FIELD(temp_a0, s32 *, 8);
        switch (temp_v1) {                          /* irregular */
        case 0:
            func_001E19F0(M2C_FIELD(temp_a0, s32 *, 0x40));
            return;
        case 1:
            func_001E0A00(M2C_FIELD(temp_a0, s32 *, 0x44));
            return;
        }
    }
}
