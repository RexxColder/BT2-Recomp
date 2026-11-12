#include "common.h"

u8 *func_00269A40(u8 *arg0, s32 arg1);
void func_0026A478(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3);

void func_0026AF60(u8 *arg0) {
    u8 sp[0x200];
    u8 *base = arg0 + 0x12E0;
    u8 *s1 = arg0 + 0x1300;
    s32 i;

    for (i = 0; i < *(s32 *)(arg0 + 0x14E0); i++) {
        s32 slot = *(s8 *)(s1 + 0);
        s32 depth = *(s8 *)(s1 + 3);
        s32 id = *(s8 *)(s1 + 1);

        s1 += 0x40;
        if (slot >= 0) {
            if (depth > 0) {
                u8 *d = sp + (depth << 6);

                func_0026A478(arg0, base, d - 0x40, d);
            } else {
                u8 *v0 = func_00269A40(arg0, id);

                if (v0 != NULL) {
                    func_0026A478(arg0, base, v0 + 0x40, sp);
                }
            }
        }
        base += 0x40;
    }
}
