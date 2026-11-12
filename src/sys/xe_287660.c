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


/* Reads text into the bit buffer, 6 bits per character; characters outside the set are skipped. */
void OldPass_TextToBits(char *text) {
    char *charset[PASS_CHARSET] = { OLDPASS_CHARSET };
    char *p = text;
    s32 pos = 0;
    s32 i;

    while (*p != 0) {
        for (i = 0; i < PASS_CHARSET; i++) {
            if (*p == *charset[i]) {
                OldPass_PutBits(i, pos, 6);
                pos += 6;
                break;
            }
        }
        p++;
    }
}
