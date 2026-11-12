#include "common.h"

/* Stage hook slots: D_00347B5C is a table of callbacks that the stage code installs (the installer at
   0x2E12E0 is not in this file). Each thunk calls its slot if one is set; the names use the slot number
   (slot n = D_00347B5C + 4 * n). One array extern: a per-slot scalar extern would be reached through $gp. */
extern void (*D_00347B5C[])(void);

/* Calls stage hook slot 5 if set. */
void StgSlot_Call05(void) {
    if (D_00347B5C[5] != NULL) {
        D_00347B5C[5]();
    }
}

/* Calls stage hook slot 7 if set. */
void StgSlot_Call07(void) {
    if (D_00347B5C[7] != NULL) {
        D_00347B5C[7]();
    }
}

/* Calls stage hook slot 6 if set. */
void StgSlot_Call06(void) {
    if (D_00347B5C[6] != NULL) {
        D_00347B5C[6]();
    }
}

/* Calls stage hook slot 8 if set. */
void StgSlot_Call08(void) {
    if (D_00347B5C[8] != NULL) {
        D_00347B5C[8]();
    }
}

/* Calls stage hook slot 9 if set. */
void StgSlot_Call09(void) {
    if (D_00347B5C[9] != NULL) {
        D_00347B5C[9]();
    }
}

/* Calls stage hook slot 10 if set. */
void StgSlot_Call10(void) {
    if (D_00347B5C[10] != NULL) {
        D_00347B5C[10]();
    }
}

/* Calls stage hook slot 11 if set. */
void StgSlot_Call11(void) {
    if (D_00347B5C[11] != NULL) {
        D_00347B5C[11]();
    }
}

/* Calls stage hook slot 12 if set. */
void StgSlot_Call12(void) {
    if (D_00347B5C[12] != NULL) {
        D_00347B5C[12]();
    }
}

/* Calls stage hook slot 13 if set. */
void StgSlot_Call13(void) {
    if (D_00347B5C[13] != NULL) {
        D_00347B5C[13]();
    }
}

/* Calls stage hook slot 14 if set. */
void StgSlot_Call14(void) {
    if (D_00347B5C[14] != NULL) {
        D_00347B5C[14]();
    }
}
