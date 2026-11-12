/*
 * BtlUtil_WrapAngle (BT3 btl_char_get.c, same code). The floats are the data labels D_00385A1C..A28.
 */
#include "common.h"
#include "battle/btl_char_get.h"
#include "battle/battle.h"
#include "sys/math3d.h"

extern void func_0028BB60(void *p);
extern void func_003126C8(Vec4 *dst, Vec4 *src);
extern void func_00312680(Vec4 *dst, Vec4 *src, f32 scale);
extern BattleResult *func_0023EA20(void);

/* A .lit4 constant that stays in the assembly data: an opaque lwc1 %gp_rel load, so the delay-slot filler
   does not move it (the same code the original compiler wrote). The value is checked against the data file. */
#ifdef __mips__
#define LIT4(sym) ({ f32 _lit4; __asm__("lwc1 %0,%%gp_rel(" #sym ")($28)" : "=f"(_lit4)); _lit4; })
#else
#define LIT4(sym) (sym) /* PC: just the constant (the asm only keeps the PS2 build matching) */
#endif
extern const f32 D_00385A1C;
extern const f32 D_00385A20;
extern const f32 D_00385A24;
extern const f32 D_00385A28;

/* Brings an angle back into -pi..pi (one turn at most). */
f32 BtlUtil_WrapAngle(f32 a) {
    if (a < LIT4(D_00385A1C)) {
        a += LIT4(D_00385A20);
    }
    if (a > LIT4(D_00385A24)) {
        a -= LIT4(D_00385A28);
    }
    return a;
}
