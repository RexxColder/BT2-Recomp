#include "common.h"

s32 func_00140258(u8 *arg0);
extern u8 *D_003876A0;
extern u8 *gEftDust;

void EftWaterMist_UpdateList(u8 **arg0, u8 **arg1) {
    u8 *s0;
    u8 *s1;
    u8 *a0;
    u8 *v0;
    u8 *v1;

    if (*(s32 *)(gEftDust + 0x38) != 0 && !(*(s64 *)(D_003876A0 + 0x4D8) & 0x100)) {
        s1 = *arg0;
        if (s1 != NULL) {
            a0 = s1;
            do {
                s0 = s1;
                s1 = *(u8 **)(s0 + 0x9C);
                if (func_00140258(a0) != 0) {
                    v1 = *(u8 **)(s0 + 0x98);
                    *(s8 *)(s0 + 0x93) = 0;
                    *(s8 *)(s0 + 0x94) = 0;
                    if (v1 == NULL) {
                        *arg0 = s1;
                    } else {
                        *(u8 **)(v1 + 0x9C) = *(u8 **)(s0 + 0x9C);
                    }
                    v1 = *(u8 **)(s0 + 0x9C);
                    v0 = *(u8 **)(s0 + 0x98);
                    if (v1 == NULL) {
                        *arg1 = v0;
                    } else {
                        *(u8 **)(v1 + 0x98) = v0;
                    }
                    *(u8 **)(s0 + 0x9C) = NULL;
                    *(u8 **)(s0 + 0x98) = NULL;
                    *(s32 *)(gEftDust + 0x38) = *(s32 *)(gEftDust + 0x38) - 1;
                }
                a0 = s1;
            } while (s1 != NULL);
        }
    }
}
