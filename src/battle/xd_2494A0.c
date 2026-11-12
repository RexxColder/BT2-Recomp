/*
 * EftShotFx_Update (BT3 eft_t_c.c, same code).
 */
#include "common.h"
#include "battle/eft_t.h"
#include "battle/eft_u.h"
#include "sys/gfx_ot.h"
#include "battle/battle.h"
#include "sys/math3d.h"

extern void func_0028BB60(void *p);
extern void func_003126C8(Vec4 *dst, Vec4 *src);
extern void func_00312680(Vec4 *dst, Vec4 *src, f32 scale);
extern BattleResult *func_0023EA20(void);

/* Task update: the request slots, then the lines. */
extern void func_001018D0(void);

void EftShotFx_Update_2494A0(void) {
    func_001018D0();
    LipSync_Clear();
}
