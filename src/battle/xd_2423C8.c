/*
 * ScrWarp_Term (BT3 stg_b.c, same code).
 */
#include "common.h"
#include "battle/battle.h"
#include "battle/battle_work.h"
#include "battle/stg_b.h"
#include "battle/btl_cam.h"
#include "sys/adx.h"
#include "sys/common.h"
#include "sys/debug.h"
#include "sys/dma.h"
#include "sys/gfx.h"
#include "sys/heap.h"
#include "sys/mathf.h"
#include "battle/btl_scene.h"
#include "sys/randf.h"
#include "sys/snd.h"
#include "sys/math3d.h"

extern void func_0028BB60(void *p);
extern void func_003126C8(Vec4 *dst, Vec4 *src);
extern void func_00312680(Vec4 *dst, Vec4 *src, f32 scale);
extern BattleResult *func_0023EA20(void);

/* Frees the objects and the manager. */
void ScrWarp_Term(void) {
    if (gScrWarp != NULL) {
        func_0028BB60(gScrWarp->objs);
        func_0028BB60(gScrWarp);
        gScrWarp = NULL;
    }
}
