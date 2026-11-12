#include "common.h"

s32 File_IsBusy(void);

/* 0x0030A9B0: devuelve arg0, salvo arg0 == -1: entonces 2 si File_IsBusy() == 1 y 1 en otro caso
 * (xor con 1 + movn). */
s32 func_0030A9B0(s32 arg0) {
    if (arg0 == -1) {
        arg0 = (File_IsBusy() != 1) ? 1 : 2;
    }
    return arg0;
}
