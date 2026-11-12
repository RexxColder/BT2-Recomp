#include "common.h"
#include "cri/xf_mwply.h"

extern char D_00379458[]; /* "E309101 : Timer channel is only -1, 0, 1." */
extern char D_00379488[]; /* "E5060801: mwPlySetUpdateTimeAuto: handle is invalid." */

s32 func_002B8280(XfMwPly *ply);
void func_002D04A8(void *sfd, s32 id, s32 val);
void func_002D0710(void *sfd, s32 id, s32 *val);
void func_002D68F0(void);
void func_002D6A10(void *fn, s32 arg);
void func_002B93A0(s32 unused, const char *msg);

/* mwPlySetTimerCh: validates ch in {-1, 0, 1} and stores it as global SFD parameter 0x3D. */
void func_002B92B0(s32 ch) {
    if ((u32)(ch + 1) >= 3) {
        Rand_Range(D_00379458);
        return;
    }
    func_002D04A8(NULL, 0x3D, ch);
}

/* mwPlyGetTimerCh: reads global SFD parameter 0x3D. */
s32 func_002B92F0(void) {
    s32 ch;
    func_002D0710(NULL, 0x3D, &ch);
    return ch;
}

/* mwPlySetUpdateTimeAuto: sets SFD parameter 0x47 of the player's handle. */
void func_002B9318(XfMwPly *ply, s32 sw) {
    if (func_002B8280(ply) != 1) {
        Rand_Range(D_00379488);
        return;
    }
    func_002D04A8(ply->sfd, 0x47, sw);
}

/* Middleware init step: calls 0x2D68F0 and installs func_002B93A0 as the error callback. */
void func_002B9378(void) {
    func_002D68F0();
    func_002D6A10(func_002B93A0, 0);
}

/* Error callback: forwards the message to the Sofdec error reporter. */
void func_002B93A0(s32 unused, const char *msg) {
    Rand_Range(msg);
}
