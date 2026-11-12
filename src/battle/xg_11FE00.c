#include "m2c_macros.h"

void *func_00126040(void *);                        /* extern */
extern void *D_003876A0;

/* Battle object: caches a pointer (+0x11D0) and +0x11D4 = +0x11D0 + 0x10 when the flag at D+0x4D8 bit 1 is clear. */
void func_0011FE00(void *arg0) {
    void *temp_v1;

    if (!(M2C_FIELD(D_003876A0, s64 *, 0x4D8) & 2)) {
        if (M2C_FIELD(D_003876A0, s32 *, 0xB8) == 4) {
            temp_v1 = M2C_FIELD(D_003876A0, void **, 0);
            M2C_FIELD(arg0, void **, 0x11D0) = (void *) (temp_v1 + (((u32) M2C_FIELD(temp_v1, u32 *, 0x1C) >> 2) * 4));
        } else {
            M2C_FIELD(arg0, void **, 0x11D0) = (void *) M2C_FIELD(M2C_FIELD(func_00126040(arg0), void **, 0x1530), void **, 0x990);
        }
        M2C_FIELD(arg0, void **, 0x11D4) = (void *) (M2C_FIELD(arg0, void **, 0x11D0) + 0x10);
    }
}
