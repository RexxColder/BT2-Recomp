#include "common.h"

void EftTechEvt_RequestExpire(s32 arg0);
s32 func_00126560(s32 arg0, s32 arg1);
void func_0019F8D0(s32 arg0, s64 arg1, s64 arg2, s64 arg3);
extern void EftStruggle_Update(void);
extern s64 D_0036EA80[] __attribute__((section(".data")));
extern u8 *gEftStruggle;

void func_001A7AC8(void) {
    s64 sp[4];
    u8 *obj;
    u8 *temp_a1;
    u8 *temp_v1;
    s32 temp_v0;
    s32 temp_a0;
    s32 k;

    if (gEftStruggle != 0) {
        obj = *(u8 **)gEftStruggle;
        temp_a1 = *(u8 **)(obj + 4);
        if ((temp_a1 != 0) && !(*(u8 *)temp_a1 & 1) &&
            (*(s32 *)(*(u8 **)(temp_a1 + 0x28)) == (s32)0x001A7FA0u)) { /* PS2 address of EftStruggle_Update */
            temp_v1 = *(u8 **)(temp_a1 + 0x38);
            temp_v0 = *(s32 *)(temp_v1 + 0x28);
            temp_a0 = temp_v0 | 1;
            if (!(temp_v0 & 1)) {
                *(s32 *)(temp_v1 + 0x28) = temp_a0;
                if (func_00126560(temp_a0, (s32)temp_a1) == 0) {
                    EftTechEvt_RequestExpire(0);
                    EftTechEvt_RequestExpire(1);
                    for (k = 0; k < 4; k++) {
                        sp[k] = D_0036EA80[k];
                    }
                    func_0019F8D0((s32)sp, D_0036EA80[1], D_0036EA80[2], D_0036EA80[3]);
                }
            }
        }
    }
}
