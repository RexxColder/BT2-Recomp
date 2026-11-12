#include "common.h"
#include "sys/misc_a.h"

/* Character passwords, older format: 0x252F68-0x253ED8. Only OldPass_DecodeChar is called (menu overlay 0x3ABD8C);
 * the encoders, the 20-character format and the random fillers have no caller. */

extern u32 strlen(const char *s);
extern s32 rand(void);

extern u32 gOldPassMtState[PASS_MT_N];
extern u8 gOldPassBits[PASS_BUF_SIZE];
extern char gOldPassText[0x30];

s32 gOldPassMtIndex = 0;

/* The 64 characters of the older format, in value order. */
#define OLDPASS_CHARSET                                                                                              \
    "Q", "R", "S", "T", "U", "V", "W", "X", "I", "J", "K", "L", "M", "N", "O", "P", "A", "B", "C", "D", "E", "F",    \
    "G", "H", "Y", "Z", "a", "b", "c", "d", "e", "f", "w", "x", "y", "z", "!", "#", "$", "%", "o", "p", "q", "r",    \
    "s", "t", "u", "v", "g", "h", "i", "j", "k", "l", "m", "n", "&", "@", "-", "+", "*", "(", ")", "?"


/* Fills `out` with random content from rand() (debug helper; no caller). */
void OldPass_RandomChar(OldPassChar *out) {
    s32 i;

    out->charId = rand() % 129;
    for (i = 0; i < 7; i++) {
        out->item[i] = rand() % 566;
    }
    out->unk20 = rand() % 3;
    out->unk28 = rand() % 7;
    out->unk24 = rand() % 2;
}

/* Fills `out` with random content from rand() (debug helper; no caller). */
void OldPass_RandomShort(OldPassShort *out) {
    out->charId = rand() % 129;
    out->unk04 = rand() % 129;
    out->unk0C = rand() % 3;
    out->amount = (rand() % 0xFFFFF) * 100;
    out->unk14 = rand() % 7;
    out->unk10 = rand() % 2;
}
