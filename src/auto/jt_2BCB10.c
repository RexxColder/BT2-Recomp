#include "m2c_macros.h"

M2C_UNK func_002B7C30(void *);                      /* extern */
M2C_UNK func_002BC710(void *);                      /* extern */
M2C_UNK func_002BCA68(void *);                      /* extern */
M2C_UNK func_002BCB88(void *);                      /* extern */

s32 func_002BCB10(void *arg0) {
    u32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u32 *, 4);
    switch (temp_v1) {
    case 0:
    case 3:
    case 4:
        break;
    case 1:
        func_002BC710(arg0);
        break;
    case 2:
        func_002BCA68(arg0);
        break;
    }
    func_002BCB88(arg0);
    func_002B7C30(arg0);
    return 0;
}
