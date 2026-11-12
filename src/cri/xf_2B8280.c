#include "common.h"
#include "cri/xf_mwply.h"

/* mwPly handle check: returns ply->used, or 0 for a NULL handle. */
s32 func_002B8280(XfMwPly *ply) {
    if (ply == NULL) {
        return 0;
    }
    return ply->used;
}
