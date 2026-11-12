#include "m2c_macros.h"

M2C_UNK func_001EC460(void *);                      /* extern */

void func_001AFCA8(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x162) != 0) {
        func_001EC460(arg0 + 0xC0);
    }
}
