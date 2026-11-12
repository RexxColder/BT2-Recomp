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

/* mwPlySetOutPan. */
void func_002B89D8(XfMwPly *ply, s32 ch, s32 pan) {
    if (func_002B8280(ply) != 1) {
        Rand_Range(D_00379298);
        return;
    }
    func_002E0C90(ply, ch, pan);
}

/* mwPlyGetOutPan. */
s32 func_002B8A48(XfMwPly *ply, s32 ch) {
    if (func_002B8280(ply) != 1) {
        Rand_Range(D_003792C8);
        return 0;
    }
    if (ply->sfd == NULL) {
        return 0;
    }
    return func_002E0CA8(ply, ch);
}

/* Sets SFD audio parameter 4 to (sw == 1). */
void func_002B8AC8(XfMwPly *ply, s32 sw) {
    void *sfd = NULL;
    if (ply != NULL) {
        sfd = ply->sfd;
    }
    if (sw == 1) {
        func_002C57A8(sfd, 4, 1);
    } else {
        func_002C57A8(sfd, 4, 0);
    }
}

/* Sets SFD parameter 0x27 to (sw == 1). */
void func_002B8B10(XfMwPly *ply, s32 sw) {
    void *sfd = ply->sfd;
    if (sw == 1) {
        func_002D04A8(sfd, 0x27, 1);
        return;
    }
    func_002D04A8(sfd, 0x27, 0);
}

/* Sets SFD parameter 0x24. */
void func_002B8B50(XfMwPly *ply, s32 val) {
    void *sfd = ply->sfd;
    if (ply != NULL) {
        func_002D04A8(sfd, 0x24, val);
    }
}

/* Sets SFD parameter 0x25. */
void func_002B8B88(XfMwPly *ply, s32 val) {
    void *sfd = ply->sfd;
    if (ply != NULL) {
        func_002D04A8(sfd, 0x25, val);
    }
}

/* mwPlyGetNumSkipEmptyB. */
s32 func_002B8BC0(XfMwPly *ply) {
    s32 inf[42];
    if (func_002B8280(ply) != 1) {
        Rand_Range(D_003792F8);
        return 0;
    }
    func_002B8110(ply, inf);
    return inf[4];
}

/* mwPlySetEmptyBpicSkip. */
void func_002B8C18(XfMwPly *ply, s32 sw) {
    s32 ok = func_002B8280(ply);
    if (ok != 1) {
        Rand_Range(D_00379330);
        return;
    }
    func_002D04A8(func_002B7CB8(ply), 7, sw != ok);
}

/* mwPlyGetInputSj: the input stream joint of the player. */
void *func_002B8C98(XfMwPly *ply) {
    if (func_002B8280(ply) != 1) {
        Rand_Range(D_00379368);
        return NULL;
    }
    return ply->inputSj;
}

/* mwPlyGetPlyInf: drop / skip counters and play information. */
void func_002B8CE8(XfMwPly *ply, XfPlyInf *inf) {
    s32 buf[44];
    s32 hdr[56];
    void *sfd;
    if (func_002B8280(ply) != 1) {
        Rand_Range(D_00379398);
        memset(inf, 0, sizeof(XfPlyInf));
        return;
    }
    sfd = func_002B7CB8(ply);
    if (sfd == NULL) {
        memset(inf, 0, sizeof(XfPlyInf));
        return;
    }
    func_002D0898(sfd, buf);
    inf->numDropFrm = func_002B7D58(ply);
    inf->numSkipDec = func_002B7DC0(ply);
    inf->numSkipDisp = func_002B5AF8(ply);
    inf->numSkipEmptyB = func_002B8BC0(ply);
    inf->unk10 = buf[9];
    func_002D0938(sfd, hdr);
    inf->unk14 = *(f32 *)&hdr[55];
}

typedef struct XfSfdPlyInf {
    s32 head[14];
    XfFlowInf flow;
    s32 tail[4];
} XfSfdPlyInf;

/* mwPlyGetFlowInf: copies the data-flow counters of the SFD play information. */
void func_002B8DD8(XfMwPly *ply, XfFlowInf *inf) {
    XfSfdPlyInf buf;
    void *sfd;
    if (func_002B8280(ply) != 1) {
        memset(inf, 0, sizeof(XfFlowInf));
        Rand_Range(D_003793C8);
        return;
    }
    sfd = func_002B7CB8(ply);
    if (sfd == NULL) {
        memset(inf, 0, sizeof(XfFlowInf));
        return;
    }
    func_002D0898(sfd, &buf);
    inf->w[0] = buf.flow.w[0];
    inf->w[1] = buf.flow.w[1];
    inf->w[2] = buf.flow.w[2];
    inf->w[3] = buf.flow.w[3];
    inf->w[4] = buf.flow.w[4];
    inf->w[5] = buf.flow.w[5];
    inf->w[6] = buf.flow.w[6];
    inf->w[7] = buf.flow.w[7];
    inf->w[8] = buf.flow.w[8];
    inf->w[9] = buf.flow.w[9];
    inf->w[10] = buf.flow.w[10];
    inf->w[11] = buf.flow.w[11];
}

/* Scales the stream position by `rate` (in 2 KB sectors) and passes it on, clamped to unk1C8. */
void func_002B8ED0(XfMwPly *ply, f32 rate) {
    s32 max = ply->unk1C8;
    s32 n = (s32)((f32)((ply->unk00C / 16384) << 11) * rate);
    if (max < n) {
        n = max;
    }
    func_002B81D8(ply, n, max);
}

/* First word of the unk040 object's state, 0 without one. */
s32 func_002B8F28(XfMwPly *ply) {
    s32 buf[4];
    if (ply->unk040 == NULL) {
        return 0;
    }
    func_002BD5F0(ply->unk040, buf);
    return buf[0];
}

/* Queries func_002BD618 on unk040, else on unk048->unk28. */
s32 func_002B8F58(XfMwPly *ply) {
    void *a;
    struct { u8 unk00[0x28]; void *unk28; } *b;
    if (ply == NULL) {
        return 0;
    }
    a = ply->unk040;
    b = (void *)ply->unk048;
    if (a == NULL) {
        if (b == NULL) {
            return 0;
        }
        if (b->unk28 != NULL) {
            return func_002BD618(b->unk28);
        }
        return 0;
    }
    return func_002BD618(a);
}

/* mwPlySetSpeed: speed in 1/1000. */
void func_002B8FC0(XfMwPly *ply, s32 speed) {
    if (func_002B8280(ply) != 1) {
        Rand_Range(D_003793F8);
        return;
    }
    func_002CCC80(func_002B7CB8(ply), speed);
}

/* mwPlySetFloatSpeed: speed as a float, rounded to 1/1000. */
void func_002B9030(XfMwPly *ply, f32 speed) {
    f32 x;
    s32 i;
    void *sfd;
    if (func_002B8280(ply) != 1) {
        Rand_Range(D_00379428);
        return;
    }
    sfd = func_002B7CB8(ply);
    x = speed * 1000.0f + 0.5f;
    i = (s32)x;
    func_002CCC80(sfd, i - (x < (f32)i));
}
