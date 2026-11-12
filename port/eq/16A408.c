#include "common.h"

s32 func_001EDB20(s32 arg0, s32 arg1);
void func_001EDBD8(s32 arg0, s32 arg1);
void func_001EDC20(s32 arg0, s32 arg1);
u8 *func_001F3758(s32 arg0);

void func_0016A408(u8 *arg0) {
    u8 *s0;
    u8 *v;
    s32 r;

    v = func_001F3758((s32)arg0);
    s0 = *(u8 **)(arg0 + 0x38) + 0xAB0;
    r = func_001EDB20((s32)s0, *(s32 *)(*(u8 **)(v + 0x38) + 0x1E80));
    *(s32 *)(s0 + 0x30) = r;
    func_001EDBD8(r, 0);
    func_001EDC20(*(s32 *)(s0 + 0x30), 0);
}
