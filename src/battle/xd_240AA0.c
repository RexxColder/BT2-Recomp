/*
 * BtlKiBlast getter (unk28 of a kind), BT3 btl_tech_b.c, same code. Its callee is the BT2 BtlKiBlast_Get target of this function.
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
extern BtlKiBlastData *func_0023FF80(BtlTechBChr *chr, u32 kind);

f32 BtlKiBlast_GetUnk28Of_240AA0(BtlTechBChr *chr, u32 kind) {
    return func_0023FF80(chr, kind)->unk28;
}
