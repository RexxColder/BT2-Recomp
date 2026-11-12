#include "m2c_macros.h"

M2C_UNK func_002FD518(s32);                         /* extern */
M2C_UNK strcat(s32, s8 *);                          /* extern */
s32 strcmp(s32, s8 *);                              /* extern */
M2C_UNK strcpy(s32, M2C_UNK *);                     /* extern */
s32 strlen(s32);                                    /* extern */
extern M2C_UNK D_00356D10 __attribute__((section(".data")));
extern s8 D_0037E4B0 __attribute__((section(".data")));
extern s8 D_0037E4B8 __attribute__((section(".data")));

void func_002FDF58(s8 *arg0, s32 arg1) {
    s8 temp_v1;

    strcpy(arg1, &D_00356D10);
    temp_v1 = *arg0;
    if ((temp_v1 != 0x2F) && (temp_v1 != 0x5C)) {
        strcat(arg1, &D_0037E4B0);
    }
    strcat(arg1, arg0);
    if (strcmp((arg1 + strlen(arg1)) - 2, &D_0037E4B8) != 0) {
        strcat(arg1, &D_0037E4B8);
    }
    func_002FD518(arg1);
}
