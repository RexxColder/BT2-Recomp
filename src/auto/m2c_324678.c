#include "m2c_macros.h"

M2C_UNK __malloc_lock(s32);                         /* extern */
M2C_UNK __malloc_unlock(s32);                       /* extern */
s32 _malloc_r(s32, s32);                            /* extern */
extern s32 D_0036A600 __attribute__((section(".data")));

s32 malloc(s32 arg0) {
    s32 temp_s1;

    __malloc_lock(D_0036A600);
    temp_s1 = _malloc_r(D_0036A600, arg0);
    __malloc_unlock(D_0036A600);
    return temp_s1;
}
