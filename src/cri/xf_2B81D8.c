#include "common.h"
#include "cri/xf_mwply.h"

void eh_context_free(void *p);
void func_002BB3B8(XfMwPly *ply, s32 n);
void func_002BD5D8(void *p);

/* Frees the player's sub-object at +0x40 then calls the 0x2BB3B8 cleanup. */
void func_002B81D8(XfMwPly *ply, s32 n) {
    eh_context_free(ply->unk040);
    func_002BB3B8(ply, n);
}

/* Forwards the player's +0x40 object to 0x2BD5D8. */
void func_002B8218(XfMwPly *ply) {
    func_002BD5D8(ply->unk040);
}
