#include "common.h"
#include "cri/xf_mwply.h"

extern char D_00378E18[]; /* "E1122617 mwPlySetAudioSw: handle is invalid." */
s32 func_002B8280(XfMwPly *ply);
void func_002D04A8(void *sfd, s32 id, s32 val);

/* mwPlySetAudioSw: switches the audio output on or off. */
void func_002B7C38(XfMwPly *ply, s32 sw) {
    if (func_002B8280(ply) != 1) {
        Rand_Range(D_00378E18);
        return;
    }
    func_002D04A8(ply->sfd, 6, sw);
}
