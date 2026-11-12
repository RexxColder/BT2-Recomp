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

/* Fills the twister state from one word (MT19937 init_genrand) and leaves the read index at 1. */
void OldPass_MtSeed(u32 seed) {
    s32 i;

    gOldPassMtState[0] = seed;
    for (i = 1; i < PASS_MT_N; i++) {
        gOldPassMtState[i] = 1812433253 * (gOldPassMtState[i - 1] ^ (gOldPassMtState[i - 1] >> 30)) + i;
    }
    gOldPassMtIndex = 1;
}

/* Fills the twister state from an array of words (MT19937 init_by_array). */
void OldPass_MtSeedByArray(u32 *key, s32 keyLen) {
    s32 i = 1;
    s32 j = 0;
    s32 k = PASS_MT_N > keyLen ? PASS_MT_N : keyLen;

    OldPass_MtSeed(19650218);
    for (; k; k--) {
        gOldPassMtState[i] =
            (gOldPassMtState[i] ^ ((gOldPassMtState[i - 1] ^ (gOldPassMtState[i - 1] >> 30)) * 1664525)) + key[j] + j;
        i++;
        j++;
        if (i >= PASS_MT_N) {
            gOldPassMtState[0] = gOldPassMtState[PASS_MT_N - 1];
            i = 1;
        }
        if (j >= keyLen) {
            j = 0;
        }
    }
    for (k = PASS_MT_N - 1; k; k--) {
        gOldPassMtState[i] =
            (gOldPassMtState[i] ^ ((gOldPassMtState[i - 1] ^ (gOldPassMtState[i - 1] >> 30)) * 1566083941ULL)) - i;
        i++;
        if (i >= PASS_MT_N) {
            gOldPassMtState[0] = gOldPassMtState[PASS_MT_N - 1];
            i = 1;
        }
    }
}

/* Returns the next state word, tempered as MT19937 does. There is no refill: the state is never twisted. */
u32 OldPass_MtNext(void) {
    u32 y;

    y = gOldPassMtState[gOldPassMtIndex++];
    y ^= y >> 11;
    y ^= (y << 7) & 0x9D2C5680;
    y ^= (y << 15) & 0xEFC60000;
    y ^= y >> 18;
    return y;
}

/* Zeroes the bit buffer. */
void OldPass_ClearBits(void) {
    s32 i;

    for (i = 0; i < PASS_BUF_SIZE; i++) {
        gOldPassBits[i] = 0;
    }
}

/* Writes the low `count` bits of `value` at bit position `pos` (least significant bit first). */
void OldPass_PutBits(u32 value, s32 pos, s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        s32 bit = (value >> i) & 1;
        s32 p = i + pos;

        if (bit) {
            gOldPassBits[p / 8] |= 1 << (p % 8);
        } else {
            gOldPassBits[p / 8] &= ~(1 << (p % 8));
        }
    }
}

/* Returns the bit at position `pos`. */
s32 OldPass_GetBit(s32 pos) {
    return (gOldPassBits[pos / 8] >> (pos % 8)) & 1;
}

/* Reads `count` bits at bit position `pos` (least significant bit first). */
u32 OldPass_GetBits(s32 pos, s32 count) {
    u32 value;
    s32 i;

    value = 0;
    for (i = 0; i < count; i++) {
        value |= OldPass_GetBit(i + pos) << i;
    }
    return value;
}

/* The divisor reaches the division as a variable: the original divides by a register holding 6. */
static inline s32 OldPass_Div(s32 a, s32 b);

/* Writes the first `bitCount` bits of the buffer as text, 6 bits per character. */
void OldPass_BitsToText(s32 bitCount);

/* Reads text into the bit buffer, 6 bits per character; characters outside the set are skipped. */
void OldPass_TextToBits(char *text);

/* Empty (stripped debug output). */
void OldPass_Nop(void);

/* Seeds the key stream from a password's 32-bit seed. */
static inline void OldPass_SetKey(u32 seed);

/* Decodes a 32-character password. Returns 1 when the length, bit count and parity all check. */
s32 OldPass_DecodeChar(OldPassChar *out, char *text);

/* Decodes a 20-character password. Returns 1 when the length, bit count and parity all check. */
s32 OldPass_DecodeShort(OldPassShort *out, char *text);

/* Encodes `in` as a 32-character password in the text buffer, with a seed from two rand() draws. */
s32 OldPass_EncodeChar(OldPassChar *in);

/* Encodes `in` as a 20-character password in the text buffer, with a seed from two rand() draws. */
s32 OldPass_EncodeShort(OldPassShort *in);

/* Returns the text buffer the encoders write. */
char *OldPass_GetText(void);

/* Fills `out` with random content from rand() (debug helper; no caller). */
void OldPass_RandomChar(OldPassChar *out);

/* Fills `out` with random content from rand() (debug helper; no caller). */
void OldPass_RandomShort(OldPassShort *out);

/* Stripped debug text. */
char *OldPass_GetDebugTextA(void);

/* Stripped debug text. */
char *OldPass_GetDebugTextB(void);
