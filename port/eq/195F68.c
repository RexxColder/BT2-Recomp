#include "common.h"

s32 func_0020B3D0(s32 arg0, void *arg1, s32 *arg2);
void func_00197030(void *arg0, s32 arg1, s32 arg2);

void func_00195F68(u8 *arg0) {
    u8 *s1;
    s32 *a2;
    s32 v0;

    s1 = *(u8 **)(arg0 + 0x38);
    a2 = *(s32 **)(s1 + 0xAF0);
    if (*(s32 *)(arg0 + 4) & 0x3F) {
        *(f32 *)(s1 + 0xB30) = *(f32 *)(arg0 + 0x10);
        *(f32 *)(s1 + 0xB34) = *(f32 *)(arg0 + 0x14);
        *(s32 *)(s1 + 0xB00) = 0;
        *(f32 *)(s1 + 0xB38) = *(f32 *)(arg0 + 0x18);
        v0 = *(s32 *)(s1 + 0xB70);
        if ((*(s64 *)arg0 & ((s64)0xC000 << 18)) == ((s64)0x8000 << 17)) {
            if (!(v0 & 0x200)) {
                *(s32 *)(s1 + 0xB70) = v0 | 0x800;
                func_00197030(s1 + 0xB30, func_0020B3D0(*a2, arg0, a2), *(s32 *)(s1 + 0xB04));
            }
        } else {
            *(s32 *)(s1 + 0xB70) = v0 | 8;
        }
    }
}
