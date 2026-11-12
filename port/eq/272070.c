#include "common.h"

extern u8 *D_003876A0;
void func_00272010(u8 *arg0, u8 *arg1);

void func_00272070(void) {
    u8 *v1 = *(u8 **)(D_003876A0 + 4);
    u8 *t;

    if (*(s64 *)(D_003876A0 + 0x4D8) & ((s64)0x8000 << 47)) {
        v1 += 0x40;
    }
    t = v1 + ((*(u32 *)(v1 + 4) >> 2) << 2);
    func_00272010(t, t);
}
