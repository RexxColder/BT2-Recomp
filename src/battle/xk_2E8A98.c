#include "m2c_macros.h"

s32 memcmp(void *, void *, s32);                     /* extern */
extern M2C_UNK D_0037BA88 __attribute__((section(".data")));

s32 func_002E8A98(void *arg0) {
    return memcmp(arg0, &D_0037BA88, 4) == 0;
}
