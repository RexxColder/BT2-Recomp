/*
 * CamShake_Add (BT3 btl_cam.c, same code). CamShake_Tick (0x25C298) is left in asm: its step constant is loaded in another register order.
 */
#include "common.h"
#include "main.h"
#include "battle/battle.h"
#include "battle/btl_cam.h"
#include "battle/btl_demo_cam.h"
#include "sys/heap.h"
#include "sys/pad.h"
#include "sys/math3d.h"

extern void func_0028BB60(void *p);
extern void func_003126C8(Vec4 *dst, Vec4 *src);
extern void func_00312680(Vec4 *dst, Vec4 *src, f32 scale);
extern BattleResult *func_0023EA20(void);

/* Registers a shake request in the first slot it dominates, unless a slot already dominates it. */
void CamShake_Add(CamShake *shake, f32 strength, f32 time) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (shake->time[i] <= time && shake->strength[i] <= strength) {
            shake->time[i] = time;
            shake->strength[i] = strength;
            return;
        }
        if (time <= shake->time[i] && strength <= shake->strength[i]) {
            break;
        }
    }
}
