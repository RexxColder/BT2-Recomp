#include "common.h"

void func_003070D0(const char *msg);
extern s32 D_003A00E0[] __attribute__((section(".data")));
extern char D_0037FBB0[] __attribute__((section(".data")));
extern char D_0037FC30[] __attribute__((section(".data")));
extern char D_0037FC58[] __attribute__((section(".data")));
extern char D_0037FC80[] __attribute__((section(".data")));

/* 0x00307600: fija el hueco arg1 (0..5) del grupo arg0 (0..7) de D_003A00E0 = {fn, arg, nombre (NULL ->
 * D_0037FBB0)}. arg1 >= 6 -> func_003070D0(D_0037FC30); arg0 >= 8 -> func_003070D0(D_0037FC58) (en ese orden,
 * comparaciones sin signo). Si el hueco ya tenía fn avisa con func_003070D0(D_0037FC80) y lo pisa igual.
 * 5 argumentos: el quinto llega en $t0. */
void func_00307600(u32 arg0, u32 arg1, s32 fn, s32 arg, s32 name) {
    s32 *slot;

    if (arg1 >= 6) {
        func_003070D0(D_0037FC30);
        return;
    }
    if (arg0 >= 8) {
        func_003070D0(D_0037FC58);
        return;
    }
    slot = D_003A00E0 + arg0 * 18 + arg1 * 3;
    if (slot[0] != 0) {
        func_003070D0(D_0037FC80);
    }
    slot[0] = fn;
    slot[1] = arg;
    slot[2] = (name != 0) ? name : (s32)D_0037FBB0;
}
