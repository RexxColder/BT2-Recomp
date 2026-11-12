#include "common.h"
#include "cri/xf_mwply.h"

void func_002BD4B8(void *p);

/* Forwards the player's +0x40 object to 0x2BD4B8. */
void func_002B8248(XfMwPly *ply) {
    func_002BD4B8(ply->unk040);
}
