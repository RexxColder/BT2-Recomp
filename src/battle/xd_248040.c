#define gLipSync D_003889E8  /* fix_targets */ /* the original uses 0x3889e8 here */
/*
 * LipSync_Clear (BT3 view_b_c.c, same code).
 */
#include "common.h"
#include "battle/view_b.h"
#include "battle/battle_setup.h"
#include "battle/battle_work.h"
#include "sys/adx.h"
#include "sys/common.h"
#include "sys/mem_read.h"
#include "sys/rand.h"
#include "sys/save.h"
#include "sys/snd.h"
#include "battle/battle.h"
#include "sys/math3d.h"

extern void *memset(void *dst, s32 c, u32 n);
extern LipSync gLipSync;

extern void func_0028BB60(void *p);
extern void func_003126C8(Vec4 *dst, Vec4 *src);
extern void func_00312680(Vec4 *dst, Vec4 *src, f32 scale);
extern BattleResult *func_0023EA20(void);

/* Stops the mouth movement. */
void LipSync_Clear(void) {
    memset(&gLipSync, 0, sizeof(LipSync));
}
