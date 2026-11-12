#include "common.h"

/* Stage hook slots: D_00347B5C is a table of callbacks that the stage code installs (the installer at
   0x2E12E0 is not in this file). Each thunk calls its slot if one is set; the names use the slot number
   (slot n = D_00347B5C + 4 * n). One array extern: a per-slot scalar extern would be reached through $gp. */
extern void (*D_00347B5C[])(void);

/* Calls stage hook slot 16 if set. */
void StgSlot_Call16(void) {
    if (D_00347B5C[16] != NULL) {
        D_00347B5C[16]();
    }
}

/* Calls stage hook slot 17 if set. */
void StgSlot_Call17(void) {
    if (D_00347B5C[17] != NULL) {
        D_00347B5C[17]();
    }
}

/* Calls stage hook slot 18 if set. */
void StgSlot_Call18(void) {
    if (D_00347B5C[18] != NULL) {
        D_00347B5C[18]();
    }
}

/* Calls stage hook slot 19 if set. */
void StgSlot_Call19(void) {
    if (D_00347B5C[19] != NULL) {
        D_00347B5C[19]();
    }
}

/* Calls stage hook slot 20 if set. */
void StgSlot_Call20(void) {
    if (D_00347B5C[20] != NULL) {
        D_00347B5C[20]();
    }
}
