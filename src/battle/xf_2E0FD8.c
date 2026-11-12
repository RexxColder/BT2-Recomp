#include "common.h"

/* Stage hook slots: D_00347B5C is a table of callbacks that the stage code installs (the installer at
   0x2E12E0 is not in this file). Each thunk calls its slot if one is set; the names use the slot number
   (slot n = D_00347B5C + 4 * n). One array extern: a per-slot scalar extern would be reached through $gp. */
extern void (*D_00347B5C[])(void);

/* Calls stage hook slot 2 if set. */
void StgSlot_Call02(void) {
    if (D_00347B5C[2] != NULL) {
        D_00347B5C[2]();
    }
}

/* Calls stage hook slot 3 if set. */
void StgSlot_Call03(void) {
    if (D_00347B5C[3] != NULL) {
        D_00347B5C[3]();
    }
}
