#include "common.h"

typedef struct EftInit {
    f32 scale[2];   /* 0x00: farg0, farg1 */
    u8 unk08[8];    /* 0x08: never written by the asm */
    f32 pos[4];     /* 0x10: copy of arg7 (func_00129C28) */
    f32 dir[4];     /* 0x20: copy of arg11, xyz negated when cfg[6] == 1 */
    s32 kind;       /* 0x30: cfg[3] */
    s32 base;       /* 0x34: ctx + 0x408 */
    s32 arg2;       /* 0x38 */
    s32 arg3;       /* 0x3C */
    s32 arg6;       /* 0x40 */
} __attribute__((aligned(16))) EftInit;

void func_00129C28(s32 arg0, s32 arg1);
void func_00129BD0(s32 arg0, s32 arg1, f32 farg0);
s32 EftPtcl4_Create(s32 arg0);
void EftPtcl4_SetStartDelay(s32 arg0, f32 farg0);
void EftPtcl4_SetStopDelay(s32 arg0, f32 farg0);
void EftPtcl4_SetViewObj(s32 arg0, s32 arg1);
void EftPtcl4_SetType(s32 arg0, s32 arg1);
void EftPtcl4_SetPos(s32 arg0, s32 arg1);
void EftPtcl4_SetSize(s32 arg0, f32 farg0);
void EftPtcl4_SetDir(s32 arg0, s32 arg1);
s32 EftPtcl4_Kill(s32 arg0);
void EftPtcl4_Stop(s32 arg0);

/* 0x0014FF78: effect-particle request. flags bit 0 creates the particle when *handle is
 * empty (from cfg and the two vectors), bit 3 sets the position, bit 5 the size, bit 6
 * the direction, bit 2 kills it (clears *handle), bit 1 stops it. Returns flags & 8 when
 * no particle exists; otherwise the Kill result for bit 2, else flags & 2. */
s32 func_0014FF78(u8 *ctx, u8 *cfg, s32 arg2, s32 arg3, s32 *handle, s32 flags,
                  s32 arg6, s32 arg7, f32 farg0, f32 farg1, s32 arg11)
{
    EftInit init;
    s32 result;

    if ((flags & 1) != 0 && *handle == 0) {
        init.scale[0] = farg0;
        init.scale[1] = farg1;
        init.kind = cfg[3];
        init.base = (s32)(ctx + 0x408);
        init.arg2 = arg2;
        init.arg3 = arg3;
        init.arg6 = arg6;

        func_00129C28((s32)init.pos, arg7);
        func_00129C28((s32)init.dir, arg11);
        if (cfg[6] == 1) {
            func_00129BD0((s32)init.dir, (s32)init.dir, -1.0f);
        }

        *handle = EftPtcl4_Create((s32)&init);
        EftPtcl4_SetStartDelay(*handle, (f32)cfg[0x15]);
        EftPtcl4_SetStopDelay(*handle, (f32)cfg[4]);
        if ((cfg[7] & 0x20) != 0) {
            EftPtcl4_SetViewObj(*handle, arg6);
        }
        EftPtcl4_SetType(*handle, 1);
    }

    if (*handle == 0) {
        return flags & 8;
    }

    result = flags & 8;
    if (result != 0) {
        EftPtcl4_SetPos(*handle, arg7);
    }
    if ((flags & 0x20) != 0) {
        EftPtcl4_SetSize(*handle, farg1);
    }
    if ((flags & 0x40) != 0) {
        EftPtcl4_SetDir(*handle, arg11);
    }
    if ((flags & 4) != 0) {
        result = EftPtcl4_Kill(*handle);
        *handle = 0;
    } else {
        result = flags & 2;
        if (result != 0) {
            EftPtcl4_Stop(*handle);
        }
    }
    return result;
}
