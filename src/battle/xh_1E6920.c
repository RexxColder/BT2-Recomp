#include "m2c_macros.h"

M2C_UNK func_003126C8(void *, M2C_UNK);                      /* extern */

// If arg0 non-null and its field 0x38 record has flag bits (&5)==1, calls func_003126C8 on the record at +0x180.
void func_001E6920(void *arg0) {
    s64 *temp_a0;

    if (arg0 != NULL) {
        temp_a0 = M2C_FIELD(arg0, s64 **, 0x38);
        if ((*temp_a0 & 5) == 1) {
            func_003126C8((void *) ((s32) temp_a0 + 0x30));
        }
    }
}
