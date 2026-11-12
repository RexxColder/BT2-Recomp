#include "common.h"

extern u8 D_0035B820[] __attribute__((section(".data")));

/* 0x00300DD0: devuelve &D_0035B820 (el lw de D_0035B810 en el delay slot va a $a0 y no se usa). 2F3408 pasa esta
 * función como callback a func_002F9468. */
void *func_00300DD0(void) {
    return D_0035B820;
}
