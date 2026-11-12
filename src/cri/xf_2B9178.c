#include "common.h"
#include "cri/xf_mwply.h"

void func_002D04A8(void *sfd, s32 id, s32 val);

/* Sets SFD parameters 0x5D/0x5E of the player's SFD handle. */
void func_002B9178(XfMwPly *ply, s32 a, s32 b) {
    func_002D04A8(ply->sfd, 0x5D, a);
    func_002D04A8(ply->sfd, 0x5E, b);
}

/* Sets SFD parameters 0x4E (= b) and 0x4D (= a). */
void func_002B91C0(XfMwPly *ply, s32 a, s32 b) {
    func_002D04A8(ply->sfd, 0x4E, b);
    func_002D04A8(ply->sfd, 0x4D, a);
}

/* Sets SFD parameters 0x5C (= b) and 0x5B (= a). */
void func_002B9208(XfMwPly *ply, s32 a, s32 b) {
    s32 i;
    func_002D04A8(ply->sfd, 0x5C, b);
    for (i = 0; i < 1; i++) { /* one-iteration loop: keeps the jal (no tail call) */
        func_002D04A8(ply->sfd, 0x5B, a);
    }
}

/* Sets SFD parameter 0x5F to b, then to a. */
void func_002B9250(XfMwPly *ply, s32 a, s32 b) {
    func_002D04A8(ply->sfd, 0x5F, b);
    func_002D04A8(ply->sfd, 0x5F, a);
}
