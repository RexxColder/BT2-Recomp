#include "m2c_macros.h"

M2C_UNK func_002EA050(M2C_UNK *);                   /* extern */
M2C_UNK func_002F1338(s32);                         /* extern */
extern M2C_UNK D_0037CE40 __attribute__((section(".data")));

void func_002F6A88(void *arg0) {
    if (arg0 == NULL) {
        func_002EA050(&D_0037CE40);
        return;
    }
    func_002F1338(M2C_FIELD(arg0, s32 *, 4));
}
