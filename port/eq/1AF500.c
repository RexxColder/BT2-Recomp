#include "common.h"

s32 func_001AF5E8(void *arg0);
extern u8 *D_003876A0;
extern u8 *D_00387858;

void func_001AF500(void **arg0, void **arg1) {
    u8 *temp_v1_2;
    u8 *temp_s0;
    void *var_s1;
    void *n;
    void *v0;

    if (*(s32 *)(D_00387858 + 4) != 0) {
        var_s1 = *arg0;
        if (var_s1 != NULL) {
            do {
                temp_s0 = (u8 *)var_s1;
                var_s1 = *(void **)(temp_s0 + 0x60);
                if (!((*(s64 *)(D_003876A0 + 0x4D8) & 0x100)) && (func_001AF5E8(temp_s0) != 0)) {
                    temp_v1_2 = *(u8 **)(temp_s0 + 0x5C);
                    temp_s0[0x57] = 0;
                    temp_s0[0x58] = 0;
                    if (temp_v1_2 == NULL) {
                        *arg0 = *(void **)(temp_s0 + 0x60);
                    } else {
                        *(void **)(temp_v1_2 + 0x60) = *(void **)(temp_s0 + 0x60);
                    }
                    n = *(void **)(temp_s0 + 0x60);
                    v0 = *(void **)(temp_s0 + 0x5C);
                    if (n == NULL) {
                        *arg1 = v0;
                    } else {
                        *(void **)((u8 *)n + 0x5C) = v0;
                    }
                    *(void **)(temp_s0 + 0x60) = NULL;
                    *(void **)(temp_s0 + 0x5C) = NULL;
                    *(s32 *)(D_00387858 + 4) = *(s32 *)(D_00387858 + 4) - 1;
                }
            } while (var_s1 != NULL);
        }
    }
}
