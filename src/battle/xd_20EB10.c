/*
 * Stage/fighter snapshot movement: BtlChar_GetSnapDelta, BtlChar_GetMoveSince (BT3 btl_char_ctl_d.c, same code).
 */
#include "common.h"
#include "battle/btl_char_ctl.h"
#include "sys/mathf.h"
#include "battle/battle.h"
#include "sys/math3d.h"

extern void func_00312650(Vec4 *out, Vec4 *a, Vec4 *b);
extern BtlCtlPose *BtlChar_GetPos(BtlCtlChr *chr);

extern void func_0028BB60(void *p);
extern void func_003126C8(Vec4 *dst, Vec4 *src);
extern void func_00312680(Vec4 *dst, Vec4 *src, f32 scale);
extern BattleResult *func_0023EA20(void);

/* Gives the movement between two snapshots. */
extern void func_00312650(Vec4 *dst, Vec4 *a, Vec4 *b);

void BtlChar_GetSnapDelta(BtlCtlChr *chr, Vec4 *out, s32 from, s32 to) {
    Vec4 a;
    Vec4 b;

    BtlChar_GetSnapPos(chr, &a, from);
    BtlChar_GetSnapPos(chr, &b, to);
    func_00312650(out, &b, &a);
}
/* Gives the movement since snapshot n. */
void BtlChar_GetMoveSince(BtlCtlChr *chr, Vec4 *out, s32 n) {
    Vec4 a;

    BtlChar_GetSnapPos(chr, &a, n);
    func_00312650(out, &BtlChar_GetPos(chr)->pos, &a);
}
