/*
 * BtlKiBlast getter (reaction S4000 of a kind), BT3 btl_tech_b.c, same code. Its callee is the BT2 BtlKiBlast_Get target of this function.
 */
#include "common.h"
#include "battle/btl_tech_b.h"
#include "battle/battle.h"
#include "sys/math3d.h"

extern void func_0028BB60(void *p);
extern void func_003126C8(Vec4 *dst, Vec4 *src);
extern void func_00312680(Vec4 *dst, Vec4 *src, f32 scale);
extern BattleResult *func_0023EA20(void);

/* The same for a kind. */
extern BtlKiBlastData *func_0023FFD8(BtlTechBChr *chr, u32 kind);

s32 BtlKiBlast_GetReactS4000Of_240880(BtlTechBChr *chr, u32 kind) {
    BtlKiBlastData *rec = func_0023FFD8(chr, kind);

    return rec->reactS4000 != 0 ? rec->reactS4000 : rec->react;
}
