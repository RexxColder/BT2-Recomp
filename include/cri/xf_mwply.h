#ifndef CRI_XF_MWPLY_H
#define CRI_XF_MWPLY_H

/* Partial view of the Sofdec player handle (MWPLY), agent F. Offsets from the matching accessors. */
typedef struct XfMwPly {
    /* 0x000 */ s32 used;        /* 1 while the handle is valid (checked by every mwPly API) */
    /* 0x004 */ s32 stat;        /* player state (2 = playing) */
    /* 0x008 */ s32 unk008;      /* 1: sync mode 2 maps to SFD sync 2, else 1 */
    /* 0x00C */ s32 unk00C;
    /* 0x010 */ u8 unk010[0x2C];
    /* 0x03C */ void *sfd;       /* SFD handle (mwPlyGetSfdHn) */
    /* 0x040 */ void *unk040;
    /* 0x044 */ s32 unk044;
    /* 0x048 */ struct { u8 unk00[0x28]; void *unk28; } *unk048;
    /* 0x04C */ u8 unk04C[0x174];
    /* 0x1C0 */ void *inputSj;   /* mwPlyGetInputSj */
    /* 0x1C4 */ s32 unk1C4;
    /* 0x1C8 */ s32 unk1C8;
    /* 0x1CC */ u8 unk1CC[0xB8];
    /* 0x284 */ u8 unk284[0x20]; /* volume object (left?) */
    /* 0x2A4 */ u8 unk2A4[0x34]; /* volume object (right?) */
    /* 0x2D8 */ s32 unk2D8;
    /* 0x2DC */ s32 unk2DC;
    /* 0x2E0 */ s32 unk2E0;
    /* 0x2E4 */ s32 unk2E4;
    /* 0x2E8 */ s32 unk2E8;
} XfMwPly;

/* Sofdec error report: printf-style message to the error callback. Named Rand_Range by the BT3 transfer (wrong). */
void Rand_Range(const char *fmt, ...);

#endif
