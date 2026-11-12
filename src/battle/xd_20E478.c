/*
 * Vec3_DiffToEuler (BT3 vu0_b_c.c, same code); the callee at 0x312680 is named by address (BT2 symbol files lack it).
 */
#include "common.h"
#include "sys/math3d.h"
#include "sys/mathf.h"
#include "sys/randf.h"
#include "battle/battle.h"

extern void func_0028BB60(void *p);
extern void func_003126C8(Vec4 *dst, Vec4 *src);
extern void func_00312680(Vec4 *dst, Vec4 *src, f32 scale);
extern BattleResult *func_0023EA20(void);

/* 0x1222D8: Vec3_DirToEuler of dir * scale (0x312680 is ScaleVector; scale is the f12 incoming param, passed through;
   the name is historic). */
void Vec3_DiffToEuler_20E478(Vec4 *out, Vec4 *dir, f32 scale) {
    Vec4 d;

    func_00312680(&d, dir, scale);
    func_0020E440(out, &d);
}
