#include "m2c_macros.h"

M2C_UNK func_002113C0(void *, M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_00237088(void *);                      /* extern */

// Sets flag 0x100 on arg0 via func_002113C0; if field 0x8DC bit 1 is clear, calls func_00237088.
void func_00237DD0(void *arg0) {
    func_002113C0(arg0, 2, 0x100, 1);
    if (!(M2C_FIELD(arg0, s32 *, 0x8DC) & 1)) {
        func_00237088(arg0);
    }
}
