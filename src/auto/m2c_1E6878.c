#include "m2c_macros.h"

void func_001E0B30(s32, f32);                         /* extern */
void func_001E1A68(s32, f32);                         /* extern */

/* f12 (farg0) passes through to the tail-called helpers. */
void func_001E6878(void *arg0, f32 farg0) {
    s32 temp_v1;
    void *temp_a0;

    if ((arg0 != NULL) && (temp_a0 = M2C_FIELD(arg0, void **, 0x38), ((M2C_FIELD(temp_a0, s64 *, 0) & 5) == 1))) {
        temp_v1 = M2C_FIELD(temp_a0, s32 *, 8);
        switch (temp_v1) {                          /* irregular */
        case 0:
            func_001E1A68(M2C_FIELD(temp_a0, s32 *, 0x40), farg0);
            return;
        case 1:
            func_001E0B30(M2C_FIELD(temp_a0, s32 *, 0x44), farg0);
            return;
        }
    }
}
