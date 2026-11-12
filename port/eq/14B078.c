#include "common.h"

s32 func_0014EFA8(s32 a0, u8 *a1, u8 *a2, s32 a3, s32 t0, s32 t1, s32 t2);
s32 func_0014F2B8(u8 *a0, u8 *a1, s32 a2, s32 a3);
void func_001513D0(s32 a0, u8 *a1, u8 *a2, u8 *a3, u8 *t0, u8 *t1, s32 t2, s32 t3, s32 st0, s32 st1, f32 farg0);

void func_0014B078(s32 a0, u8 *a1, u8 *a2, u8 a3) {
    u8 *s1;
    s32 p0;
    s32 k;
    s32 i;
    s32 off;
    s32 count;
    s32 flags;
    s32 v1;
    s32 sel;
    s32 type;
    u8 *s4;
    u8 *s2;

    s1 = *(u8 **)(a1 + 0x38);
    p0 = *(s32 *)(s1 + 0xB0);
    off = 0;
    for (k = 0; k < 16; k++) {
        s4 = *(u8 **)a2 + off;
        count = s4[0];
        for (i = 0, s2 = s4 + 0x10; i < count; i++, s2 += 0x20) {
            type = s2[1];
            if (type == 2 && (u8)(s2[0] - 1) < 2) {
                continue;
            }
            sel = a3; /* asm: `lw v0,20(sp)` sits in the delay slot of `bne v0,s8`, so it always runs: the path is chosen
                         by a3, never by the trigger byte (was (type == 2) ? a3 : type: shot-event rows such as the
                         beam, type 12, never reached 0x14EFA8 and were never created, B14) */
            if (sel != 0) {
                v1 = func_0014F2B8(a2, s1 + 0xB4, k, i);
            } else {
                flags = *(s32 *)s1;
                v1 = func_0014EFA8(a0, a2, s1 + 0xB4, k, i, flags & 1, flags & 4);
            }
            flags = *(s32 *)s1;
            if (flags & 0x100) {
                v1 = 2;
            }
            if (v1 != 0) {
                func_001513D0(p0, a2, s1 + 0xB4, s1 + 0x860, s1 + 0x80, s1 + 0x30, k, i, i, v1,
                              *(f32 *)(s1 + 0x1C));
            }
        }
        off += 0x110;
    }
}
