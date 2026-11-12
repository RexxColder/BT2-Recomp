#include "common.h"

void func_003070D0(const char *msg);
extern s32 D_003A00E0[] __attribute__((section(".data")));
extern char D_0037FB88[] __attribute__((section(".data")));
extern char D_0037FBB0[] __attribute__((section(".data")));
extern char D_0037FBB8[] __attribute__((section(".data")));

/* 0x003073E0: registra un manejador {fn, arg, nombre} en el primer hueco libre (fn == 0) de los 6 del grupo
 * arg0 (0..7) de D_003A00E0 (grupos de 0x48 bytes = 6 x 12). nombre NULL -> D_0037FBB0. Devuelve el índice
 * del hueco. arg0 >= 8 (sin signo) -> func_003070D0(D_0037FB88), -1; grupo lleno -> func_003070D0(D_0037FBB8),
 * -1. */
s32 func_003073E0(u32 arg0, s32 fn, s32 arg, s32 name) {
    s32 *slot;
    s32 i;

    if (arg0 >= 8) {
        func_003070D0(D_0037FB88);
        return -1;
    }
    slot = D_003A00E0 + arg0 * 18;
    for (i = 0; i < 6; i++, slot += 3) {
        if (slot[0] == 0) {
            slot[0] = fn;
            slot[1] = arg;
            slot[2] = (name != 0) ? name : (s32)D_0037FBB0;
            return i;
        }
    }
    func_003070D0(D_0037FBB8);
    return -1;
}
