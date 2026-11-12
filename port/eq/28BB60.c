#include "common.h"

void free(void *p);
extern s32 D_00387D4C;
extern s32 D_00387D50;
extern u8 *D_00387D54;

void func_0028BB60(s32 arg0) {
    u8 *var_a1;
    u8 *temp_v1;
    u8 *temp_v1_2;
    u8 *temp_v1_3;

    if ((D_00387D54 != NULL) && (arg0 != 0)) {
        var_a1 = D_00387D54;
loop_3:
        if (arg0 != *(s32 *)(var_a1 + 4)) {
            var_a1 = *(u8 **)(var_a1 + 8);
            if (var_a1 != NULL) {
                goto loop_3;
            }
        } else {
            temp_v1 = *(u8 **)(var_a1 + 8);
            if (temp_v1 != NULL) {
                *(u8 **)(temp_v1 + 0xC) = *(u8 **)(var_a1 + 0xC);
            }
            temp_v1_2 = *(u8 **)(var_a1 + 0xC);
            if (temp_v1_2 != NULL) {
                *(u8 **)(temp_v1_2 + 8) = *(u8 **)(var_a1 + 8);
            }
            if (D_00387D54 == var_a1) {
                temp_v1_3 = *(u8 **)(var_a1 + 8);
                D_00387D54 = temp_v1_3;
                D_00387D50 = (temp_v1_3 == NULL) ? 0 : D_00387D50;
            }
            D_00387D4C -= *(s32 *)var_a1;
            free(var_a1);
        }
    }
}
