#include "m2c_macros.h"

void func_00300DA0();                            /* extern */
void func_00300DB8();                            /* extern */
M2C_UNK func_00300DE8(void *, void *);                   /* extern */
extern M2C_UNK D_0037EE28 __attribute__((section(".data")));

void func_00301438(void *arg0) {
    if (arg0 == NULL) {
        func_00300DE8(arg0, &D_0037EE28);
        return;
    }
    func_00300DA0(arg0);
    M2C_FIELD(arg0, s8 *, 1) = 0;
    func_00300DB8();
}
