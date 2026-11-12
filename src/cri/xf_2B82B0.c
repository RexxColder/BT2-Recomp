#include "common.h"
#include "cri/xf_mwply.h"

extern char D_00379068[]; /* "E1122625: mwPlySetLimitTime: handle is invalid." */
extern char D_00379098[]; /* "W2004 mwPlyGetStat: handle is invalid" */
extern char D_003790C0[]; /* "E1122626: mwPlySetSyncMode: handle is invalid." */
extern char D_003790F0[]; /* "E2010802: mwPlyGetSyncMode: handle is invalid." */
extern char D_00379120[]; /* "E2010803: mwPlyGetSyncMode: mode is invalid." */
extern char D_00379150[]; /* "E1122621: mwPlyGetNumDecPool: handle is invalid." */
extern char D_00379188[]; /* "E1121601 mwPlyGetNumDecPool" */
extern char D_003791A8[]; /* "E1122620: mwPlyGetNumTotalDec: handle is invalid." */
extern char D_003791E0[]; /* "E1122603 mwPlyGetTime; handle is invalid." */
extern char D_00379210[]; /* "E2006 mwPlyGetTime; can't get time" */
extern char D_00379238[]; /* "E1122605 mwPlySetOutVol: handle is invalid." */
extern char D_00379268[]; /* "E1122606 mwPlyGetOutVol: handle is invalid." */
extern char D_00379298[]; /* "E1122607 mwPlySetOutPan: handle is invalid." */
extern char D_003792C8[]; /* "E1122608 mwPlyGetOutPan: handle is invalid." */
extern char D_003792F8[]; /* "E1122623: mwPlyGetNumSkipEmptyB: handle is invalid." */
extern char D_00379330[]; /* "E1122627: mwPlySetEmptyBpicSkip: handle is invalid." */
extern char D_00379368[]; /* "E1122624: mwPlyGetInputSj: handle is invalid." */
extern char D_00379398[]; /* "E202191: mwPlyGetPlyInf: handle is invalid." */
extern char D_003793C8[]; /* "E1122643: mwPlyGetFlowInf: handle is invalid." */
extern char D_003793F8[]; /* "E302251: mwPlySetSpeed: handle is invalid." */
extern char D_00379428[]; /* "E211051: mwPlySetFloatSpeed: handle is invalid." */

typedef struct XfPlyInf {
    s32 numDropFrm;
    s32 numSkipDec;
    s32 numSkipDisp;
    s32 numSkipEmptyB;
    s32 unk10;
    f32 unk14;
} XfPlyInf;

typedef struct XfFlowInf {
    s64 w[12];
} XfFlowInf;

s32 func_002B8280(XfMwPly *ply);
void func_002B8178(XfMwPly *ply, s32 id, s32 val);
void func_002B6700(s32 code);
s32 func_002D0468(void *sfd);
void func_002D04A8(void *sfd, s32 id, s32 val);
void func_002D0710(void *sfd, s32 id, s32 *val);
s32 func_002C5960(void *sfd, s32 *n);
void func_002B8110(XfMwPly *ply, s32 *inf);
void func_002CEC20(void *sfd, s32 *buf);
s32 func_002D1358(void *sfd, s32 *time, s32 *tunit);
void func_002C57A8(void *sfd, s32 id, s32 val);
void func_002E0C60(XfMwPly *ply, s32 vol);
s32 func_002E0C78(XfMwPly *ply);
void func_002BBD88(void *p, s32 vol);
s32 func_002BBDE8(void *p);
void func_002E0C90(XfMwPly *ply, s32 ch, s32 pan);
s32 func_002E0CA8(XfMwPly *ply, s32 ch);
void *func_002B7CB8(XfMwPly *ply);
s32 func_002B7D58(XfMwPly *ply);
s32 func_002B7DC0(XfMwPly *ply);
s32 func_002B5AF8(XfMwPly *ply);
s32 func_002B8BC0(XfMwPly *ply);
void func_002D0898(void *sfd, void *inf);
void func_002D0938(void *sfd, void *inf);
void *memset(void *dst, int c, unsigned int n);
void func_002B81D8(void *p, s32 n, s32 max);
void func_002BD5F0(void *p, s32 *out);
s32 func_002BD618(void *p);
void func_002CCC80(void *sfd, s32 speed);
s32 func_002B8398(XfMwPly *ply);

/* mwPlySetLimitTime: sets SFD parameter 0x36 to the limit in 1/1000 units (n * 1000). */
void func_002B82B0(XfMwPly *ply, s32 n) {
    if (func_002B8280(ply) != 1) {
        Rand_Range(D_00379068);
        return;
    }
    func_002B8178(ply, 0x36, n * 1000);
}

/* Player state with the SFD state folded in; reports "playing" while a loop restart is pending. */
s32 func_002B8328(XfMwPly *ply) {
    s32 st = func_002B8398(ply);
    if (ply->unk2D8 == 1 && ply->unk2DC == 1 && (u32)(ply->unk2E8 - 2) < 2 && (st == 1 || st == 3)) {
        st = 2;
    }
    return st;
}

/* mwPlyGetStat: player state (2 while the SFD decodes, 4 on an SFD error, 1 otherwise). */
s32 func_002B8398(XfMwPly *ply) {
    s32 ok = func_002B8280(ply);
    s32 st;
    s32 s;
    if (ok != 1) {
        func_002B6700(-12);
        Rand_Range(D_00379098);
        return 0;
    }
    st = ply->stat;
    if (st != 2) { return st; }
    s = func_002D0468(ply->sfd);
    if (s == 4 || s == 6) { return 2; }
    if (s < 0) { return 4; }
    return ok;
}

/* Applies a sync mode to the SFD (0 off, else 2 or 1 depending on unk008). */
void func_002B8430(XfMwPly *ply, s32 mode) {
    void *sfd = ply->sfd;
    if (mode == 0) {
        func_002D04A8(sfd, 15, 0);
        return;
    }
    if (ply->unk008 == 1) {
        func_002D04A8(sfd, 15, 2);
        return;
    }
    func_002D04A8(sfd, 15, 1);
}

/* mwPlySetSyncMode. */
void func_002B8488(XfMwPly *ply, s32 mode) {
    s32 ok = func_002B8280(ply);
    void *sfd;
    if (ok != 1) {
        Rand_Range(D_003790C0);
        return;
    }
    sfd = ply->sfd;
    if (mode == 0) {
        func_002D04A8(sfd, 15, 0);
        return;
    }
    if (mode == ok) {
        func_002D04A8(sfd, 15, 1);
        return;
    }
    if (mode == 2) {
        if (ply->unk008 == ok) {
            func_002D04A8(sfd, 15, 2);
            return;
        }
        func_002D04A8(sfd, 15, 1);
        return;
    }
    if (mode != 3) {
        return;
    }
    func_002D04A8(sfd, 15, 5);
    func_002D04A8(sfd, 0x47, 1);
}

/* mwPlyGetSyncMode. */
s32 func_002B85E8(XfMwPly *ply) {
    s32 v;
    s32 r;
    if (func_002B8280(ply) != 1) {
        Rand_Range(D_003790F0);
        return -1;
    }
    if (ply->sfd == NULL) {
        return 0;
    }
    func_002D0710(ply->sfd, 15, &v);
    switch (v) {
    case 0:
        r = 0;
        break;
    case 1:
        r = 1;
        break;
    case 2:
        r = 2;
        break;
    default:
        Rand_Range(D_00379120);
        r = -1;
        break;
    }
    return r;
}

/* mwPlyGetNumDecPool. */
s32 func_002B8690(XfMwPly *ply) {
    s32 n;
    if (func_002B8280(ply) != 1) {
        Rand_Range(D_00379150);
        return 0;
    }
    if (ply->sfd == NULL) {
        return 0;
    }
    if (func_002C5960(ply->sfd, &n) != 0) {
        Rand_Range(D_00379188);
    }
    return n;
}

/* mwPlyGetNumTotalDec. */
s32 func_002B8708(XfMwPly *ply) {
    s32 inf[42];
    if (func_002B8280(ply) != 1) {
        Rand_Range(D_003791A8);
        return 0;
    }
    func_002B8110(ply, inf);
    return inf[0];
}

/* Sum of two counters of the SFD buffer information. */
s32 func_002B8760(XfMwPly *ply) {
    s32 buf[8];
    func_002CEC20(ply->sfd, buf);
    return buf[1] + buf[3];
}

/* mwPlyGetTime: playback time as time / tunit (0 / 1 when unknown). */
void func_002B8790(XfMwPly *ply, s32 *time, s32 *tunit) {
    s32 ok;
    *time = 0;
    *tunit = 1;
    ok = func_002B8280(ply);
    if (ok != 1) {
        Rand_Range(D_003791E0);
        return;
    }
    if (ply->sfd == NULL) {
        return;
    }
    if (func_002D1358(ply->sfd, time, tunit) != 0) {
        func_002B6700(-0x135);
        Rand_Range(D_00379210);
    }
    if (*time < 0) {
        *time = 0;
        *tunit = ok;
    }
}

/* Sets SFD audio parameter 3. */
void func_002B8860(XfMwPly *ply, s32 val) {
    void *sfd = NULL;
    if (ply != NULL) {
        sfd = ply->sfd;
    }
    func_002C57A8(sfd, 3, val);
}

/* Sets SFD audio parameter 5. */
void func_002B8890(XfMwPly *ply, s32 val) {
    void *sfd = NULL;
    if (ply != NULL) {
        sfd = ply->sfd;
    }
    func_002C57A8(sfd, 5, val);
}

/* mwPlySetOutVol. */
void func_002B88C0(XfMwPly *ply, s32 vol) {
    if (func_002B8280(ply) != 1) {
        Rand_Range(D_00379238);
        return;
    }
    func_002E0C60(ply, vol);
    func_002BBD88(ply->unk284, vol);
    func_002BBD88(ply->unk2A4, vol);
}
