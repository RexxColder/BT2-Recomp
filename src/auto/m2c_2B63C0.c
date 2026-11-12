#include "m2c_macros.h"

M2C_UNK func_002BC2D0(M2C_UNK, M2C_UNK *, M2C_UNK, M2C_UNK *); /* extern */
M2C_UNK func_002BC338(M2C_UNK *, M2C_UNK, M2C_UNK *); /* extern */
M2C_UNK func_002BC390(M2C_UNK *, M2C_UNK, M2C_UNK *); /* extern */
M2C_UNK func_002BC3E8();                            /* extern */
extern M2C_UNK D_003787A0 __attribute__((section(".data")));
extern M2C_UNK D_003787B8 __attribute__((section(".data")));
extern M2C_UNK D_003787D0 __attribute__((section(".data")));
extern M2C_UNK func_002BCBF0 __attribute__((section(".data")));
extern M2C_UNK func_002BCC08 __attribute__((section(".data")));
extern M2C_UNK func_002BCC58 __attribute__((section(".data")));

void func_002B63C0(void) {
    func_002BC2D0(2, &func_002BCBF0, 0, &D_003787A0);
    func_002BC390(&func_002BCC08, 0, &D_003787B8);
    func_002BC338(&func_002BCC58, 0, &D_003787D0);
    func_002BC3E8();
}
