#include "common.h"

s32 func_00211288(s32 arg0);
s32 func_00200EF8(s32 arg0, s32 arg1);
s32 func_00201250(s32 arg0, s32 arg1);
s32 func_00201D90(s32 arg0, s32 arg1);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 *D_00387930;

/* 0x00202AA8: hit handler. arg0 is resolved through func_00211288 into r; the state byte at
 * r+0xB48 selects a case (0..30 minus 9 offset); the default path picks a sub-handler by the
 * kind at arg1+0x64 and then sets bit 2 of the global flags word once. Returns the hit result. */
void bt2_fightlog_note(const char *fmt, ...);
static s32 BtlColl_Hit_real(s32 arg0, u8 *arg1);
/* logging: todo impacto que el juego evalua, con quien llama y el tipo de golpe (arg1+0x64 -> +4) */
s32 BtlColl_Hit(s32 arg0, u8 *arg1) {
    u8 *w = *(s32 *)(arg1 + 0x64) ? (u8 *)(s32)*(s32 *)(arg1 + 0x64) : NULL;
    s32 r = BtlColl_Hit_real(arg0, arg1);
    bt2_fightlog_note("COLL-HIT victima J%d atacante J%d tipo %d C %08X B48 %d -> %d (desde %p)", arg0 + 1, *(s32 *)arg1 + 1,
                      w ? *(s32 *)(w + 4) : -99, *(s32 *)(arg1 + 0xC), *(s32 *)((u8 *)(s32)func_00211288(arg0) + 0xB48), r,
                      __builtin_return_address(0));
    return r;
}

static s32 BtlColl_Hit_real(s32 arg0, u8 *arg1) {
    s32 s1 = 0;
    u8 *r = (u8 *)(s32)func_00211288(arg0);
    s32 v1 = *(s32 *)(r + 0xB48) - 9;
    s32 v0;

    switch (v1) {
        case 0: case 1: case 2: case 3: case 7: case 8: case 9: case 10: case 11:
        case 18: case 19: case 23: case 26: case 28: case 29: case 30:
            return 1;
        default:
            break;
    }

    v0 = *(s32 *)(arg1 + 0xC);
    if (v0 != 0) {
        u8 *w = (u8 *)(s32)*(s32 *)(arg1 + 0x64);

        if (w != NULL && *(s32 *)(w + 4) >= 0) {
            s32 v3 = *(s32 *)(w + 4);

            if (v3 < 2) {
                s1 = func_00201250((s32)r, (s32)arg1);
            } else if (v3 < 5) {
                s1 = func_00201D90((s32)r, (s32)arg1);
            }
        }
    } else {
        s1 = func_00200EF8((s32)r, (s32)arg1);
    }

    if (s1 != 0) {
        u8 *g = D_00387930;
        s32 f = *(s32 *)(g + 8);

        if ((f & 4) == 0) {
            *(s32 *)(g + 8) = f | 4;
            v0 = func_00211288(*(s32 *)arg1);
            func_002113C0(v0, 0x10, 0x4000000, 1);
        }
    }
    return s1;
}
