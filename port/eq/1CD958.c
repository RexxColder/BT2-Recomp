#include "common.h"

s32 func_001CDA08(void *arg0);
void func_001CDA68(void *arg0, void *arg1, void *arg2);
void *func_001CDB00(void);

s32 func_001CD958(u8 *arg0) {
    u8 *s0;
    u8 *v1;
    s32 s1;

    s0 = *(u8 **)(arg0 + 0x38);
    s1 = -1;
    if (*(s32 *)(s0 + 0x118) < 4) {
        do {
            s1 = func_001CDA08(s0);
            if (s1 >= 0) {
                v1 = func_001CDB00();
                if (v1 == NULL) {
                    return -1;
                }
                *(s32 *)(v1 + 8) = 0;
                *(s32 *)(v1 + 0xC) = 0;
                *(s32 *)(v1 + 0) = s1;
                *(s16 *)(v1 + 4) = 1;
                func_001CDA68(s0 + 0x124, s0 + 0x128, v1);
                *(s32 *)(s0 + 0x118) = *(s32 *)(s0 + 0x118) + 1;
            }
        } while (*(s32 *)(s0 + 0x118) < 4);
    }
    return s1;
}
