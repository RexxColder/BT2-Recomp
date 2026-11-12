/*
 * BattleResult_GetFlags (BT3 battle_load.c, same code). The call goes to 0x23EA20 (named func_0023EA20 here).
 */
#include "common.h"
#include "battle/battle_work.h"
#include "battle/battle_setup.h"
#include "battle/btl_seq.h"
#include "sys/common.h"
#include "sys/file.h"
#include "sys/heap.h"
#include "sys/job.h"
#include "sys/loading.h"
#include "sys/save.h"
#include "battle/battle.h"
#include "sys/math3d.h"

extern void func_0028BB60(void *p);
extern void func_003126C8(Vec4 *dst, Vec4 *src);
extern void func_00312680(Vec4 *dst, Vec4 *src, f32 scale);
extern BattleResult *func_0023EA20(void);

/* Returns result.flags (winner / draw / abort bits). */
s32 BattleResult_GetFlags(void) {
    return func_0023EA20()->winner;
}
