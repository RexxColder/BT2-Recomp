#include "common.h"
#include "cri/xf_mwply.h"

extern char D_00378F10[]; /* "E1122628: mwPlySetBpicSkip mwPlySetPpicSkip: handle is invalid." */
extern char D_00378F50[]; /* "E1122616 mwPlySetAudioCh: handle is invalid." */
extern char D_00378F80[]; /* "E10911A mwPlySetAudioCh: Invalid ch no." */
extern char D_00378FA8[]; /* "E2080801 mwPlyGetNumAudioCh: handle is invalid." */
extern char D_00378FD8[]; /* "E2080601 mwPlySetVideoCh: handle is invalid." */
extern char D_00379008[]; /* "E2080602 mwPlySetVideoCh: Invalid ch no." */
extern char D_00379038[]; /* "E2080802 mwPlyGetNumVideoCh: handle is invalid." */
s32 func_002B8280(XfMwPly *ply);
void func_002D04A8(void *sfd, s32 id, s32 val);
s32 func_002CCCF0(void *sfd, s32 ch);
s32 func_002CCD60(void *sfd, s32 ch);
s32 func_002C34A0(void *sfd);
s32 func_002C3488(void *sfd);
void func_002D0898(void *sfd, s32 *inf);
void func_002D07C0(void *sfd, s32 *inf);
void func_002D0710(void *sfd);
void *memset(void *dst, int c, unsigned int n);
void func_002B8148(XfMwPly *ply, s32 *inf);

/* mwPlySetBpicSkip / mwPlySetPpicSkip: sets SFD parameter `id` to (sw != 1). */
void func_002B7E68(XfMwPly *ply, s32 sw, s32 id) {
    s32 ok = func_002B8280(ply);
    if (ok != 1) {
        Rand_Range(D_00378F10);
        return;
    }
    /* sw != ok (ok is 1 here): the original compares with the check result's register */
    func_002D04A8(ply->sfd, id, sw != ok);
}

/* mwPlySetAudioCh: selects the audio channel to play. */
void func_002B7EE0(XfMwPly *ply, s32 ch) {
    if (func_002B8280(ply) != 1) {
        Rand_Range(D_00378F50);
        return;
    }
    if (func_002CCCF0(ply->sfd, ch) != 0) {
        Rand_Range(D_00378F80);
        return;
    }
}

/* Audio channel in use, -1 without an SFD handle. */
s32 func_002B7F68(XfMwPly *ply) {
    if (ply->sfd == NULL) {
        return -1;
    }
    return func_002C34A0(ply->sfd);
}

/* mwPlyGetNumAudioCh: number of audio channels in the stream. */
s32 func_002B7FA0(XfMwPly *ply) {
    s32 inf[16];
    if (func_002B8280(ply) != 1) {
        Rand_Range(D_00378FA8);
        return -1;
    }
    func_002B8148(ply, inf);
    return inf[9];
}

/* mwPlySetVideoCh: selects the video channel to play. */
void func_002B7FF8(XfMwPly *ply, s32 ch) {
    if (func_002B8280(ply) != 1) {
        Rand_Range(D_00378FD8);
        return;
    }
    if (func_002CCD60(ply->sfd, ch) != 0) {
        Rand_Range(D_00379008);
        return;
    }
}

/* Video channel in use, -1 without an SFD handle. */
s32 func_002B8080(XfMwPly *ply) {
    if (ply->sfd == NULL) {
        return -1;
    }
    return func_002C3488(ply->sfd);
}

/* mwPlyGetNumVideoCh: number of video channels in the stream. */
s32 func_002B80B8(XfMwPly *ply) {
    s32 inf[16];
    if (func_002B8280(ply) != 1) {
        Rand_Range(D_00379038);
        return -1;
    }
    func_002B8148(ply, inf);
    return inf[10];
}

/* Copies the SFD play information (0xA8 bytes), zeroes it without an SFD handle. */
void func_002B8110(XfMwPly *ply, s32 *inf) {
    if (ply->sfd == NULL) {
        memset(inf, 0, 0xA8);
        return;
    }
    func_002D0898(ply->sfd, inf);
}

/* Copies the SFD header information when there is an SFD handle. */
void func_002B8148(XfMwPly *ply, s32 *inf) {
    if (ply->sfd != NULL) {
        func_002D07C0(ply->sfd, inf);
    }
}

/* Sets SFD parameter `id` (NULL handle tolerated). */
void func_002B8178(XfMwPly *ply, s32 id, s32 val) {
    void *sfd = NULL;
    if (ply != NULL) {
        sfd = ply->sfd;
    }
    func_002D04A8(sfd, id, val);
}

/* Forwards to func_002D0710 with the SFD handle (NULL handle tolerated). */
void func_002B81A0(XfMwPly *ply) {
    void *sfd = NULL;
    if (ply != NULL) {
        sfd = ply->sfd;
    }
    func_002D0710(sfd);
}
