#include "common.h"
#include "cri/xf_mwply.h"

extern char D_00378E48[]; /* "E1122640: mwPlyGetSfdHn: handle is invalid." */
extern char D_00378E78[]; /* "E1122639: mwPlyGetAdxtHn: handle is invalid." */
extern char D_00378EA8[]; /* "E202232: mwPlyGetNumDropFrm: handle is invalid." */
extern char D_00378ED8[]; /* "E1122619: mwPlyGetNumSkipDec: handle is invalid." */
s32 func_002B8280(XfMwPly *ply);
void *func_002B82A0(XfMwPly *ply);
s32 func_002B5AF8(XfMwPly *ply);
void func_002D0898(void *sfd, s32 *inf);
s32 func_002B7DC0(XfMwPly *ply);

/* mwPlyGetSfdHn: the SFD handle of the player. */
void *func_002B7CB8(XfMwPly *ply) {
    if (func_002B8280(ply) != 1) {
        Rand_Range(D_00378E48);
        return NULL;
    }
    return ply->sfd;
}

/* mwPlyGetAdxtHn: the ADXT handle the player streams audio through. */
void *func_002B7D08(XfMwPly *ply) {
    if (func_002B8280(ply) != 1) {
        Rand_Range(D_00378E78);
        return NULL;
    }
    return func_002B82A0(ply);
}

/* mwPlyGetNumDropFrm: skipped decodes plus dropped display frames. */
s32 func_002B7D58(XfMwPly *ply) {
    s32 n;
    if (func_002B8280(ply) != 1) {
        Rand_Range(D_00378EA8);
        return 0;
    }
    n = func_002B7DC0(ply);
    return n + func_002B5AF8(ply);
}

/* mwPlyGetNumSkipDec: number of decodes skipped (from the SFD play information). */
s32 func_002B7DC0(XfMwPly *ply) {
    s32 inf[42];
    void *sfd;
    if (func_002B8280(ply) != 1) {
        Rand_Range(D_00378ED8);
        return 0;
    }
    sfd = func_002B7CB8(ply);
    if (sfd == NULL) {
        return 0;
    }
    func_002D0898(sfd, inf);
    return inf[1] - inf[4];
}
