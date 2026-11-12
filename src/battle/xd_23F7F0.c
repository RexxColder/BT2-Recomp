/*
 * BtlParam_IsType2to4 (BT3 btl_tech_a.c, same code).
 */
#include "common.h"
#include "battle/btl_tech_a.h"
#include "battle/battle.h"
#include "sys/math3d.h"

extern void func_0028BB60(void *p);
extern void func_003126C8(Vec4 *dst, Vec4 *src);
extern void func_00312680(Vec4 *dst, Vec4 *src, f32 scale);
extern BattleResult *func_0023EA20(void);

/* The search type is 2..4 (the search action then plays animation 0x17F instead of 0x17E). */
extern s32 func_0023F558(BtlTechChr *chr);

s32 BtlParam_IsType2to4(BtlTechChr *chr) {
    switch (func_0023F558(chr)) {
        case 2:
        case 3:
        case 4:
            return 1;
    }
    return 0;
}
