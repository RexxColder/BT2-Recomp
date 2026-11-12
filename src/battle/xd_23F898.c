/*
 * BtlParam_IsTypeSetB (BT3 btl_tech_a.c, same code).
 */
#include "common.h"
#include "battle/btl_tech_a.h"
#include "battle/battle.h"
#include "sys/math3d.h"

extern void func_0028BB60(void *p);
extern void func_003126C8(Vec4 *dst, Vec4 *src);
extern void func_00312680(Vec4 *dst, Vec4 *src, f32 scale);
extern BattleResult *func_0023EA20(void);

/* The search type is 0..4, 6 or 9 (no caller found). */
extern s32 func_0023F558(BtlTechChr *chr);

s32 BtlParam_IsTypeSetB(BtlTechChr *chr) {
    switch (func_0023F558(chr)) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 6:
        case 9:
            return 1;
    }
    return 0;
}
